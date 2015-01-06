#include "mtqintegratorwidget.h"
using namespace mtq;

#include <QQuickWindow>
#include <QPen>
#include <QPainter>
#include <qmath.h>

MTQ_QML_REGISTER_PLUGIN(MtqIntegratorWidget)

MtqIntegratorWidget::MtqIntegratorWidget(QQuickItem *parent) :
	QQuickPaintedItem(parent)
{
    m_parentItem = 0;
    m_floorExtents = QSizeF(3.5f, 2.05f);
	m_tiltingMultiplicator = 100;
    m_smoothCamera = true;
	m_oldDepth = 0.0f;
    m_moveCamera = true;
    m_printDebug = false;
    m_fuzzyInput = true;
}

void MtqIntegratorWidget::paint(QPainter *painter){
    //paint debug layer
    if (m_paintDebugInfo){
        paintDebugLayer(painter);
    }

    //update window size
    if (m_validParentItem)
        m_screenSize = QSize(m_parentItem->width(), m_parentItem->height());

    this->setWidth(this->parentItem()->width());
    this->setHeight(this->parentItem()->height());

    //update smooth camera
    updateCamera();
}

void MtqIntegratorWidget::paintDebugLayer(QPainter *p){
    //Paint all contacts
	QList<int> contactIDs = m_contacts.keys();

    for (int i=0; i< contactIDs.size(); i++){
		ContactStruct contact = m_contacts.value(contactIDs.at(i));

        p->setPen(Qt::green);
		p->drawEllipse(contact.position,150,150);
        p->drawText(contact.position.x()+50,contact.position.y()+12,contact.position.x()+100,contact.position.y()+62,0,QString("Age: ") + QString::number(contact.age));
        p->drawText(contact.position.x()+50,contact.position.y()+24,contact.position.x()+100,contact.position.y()+84,0,QString("User: ") + contact.userName);

        if (contact.tiltingDirection != QVector2D(0,0)){
            p->drawLine(contact.position, contact.position + (contact.tiltingDirection*100*QVector2D(-1,1)).toPointF() );
        }

        p->setPen(Qt::blue);
		p->drawLine(contact.position,m_userPosition);
    }

    //paint average position
    p->setPen(Qt::cyan);
	p->drawEllipse(m_userPosition,75,75);
	p->drawEllipse(m_userPosition,85,85);

	p->drawText(m_userPosition.x(), m_userPosition.y(), m_userPosition.x()+200, m_userPosition.y() + 200,0, QString("Depth: ") + QString::number(depthAtUserPosition()));
}

void MtqIntegratorWidget::itemChange(ItemChange change, const ItemChangeData &d){
    //remove warnings by touching unused items (we want to react to all changes)
    change;
    d;

    //Only initialize once
    if (m_validParentItem){
        //updateCamera();
        return;
    }

    //Get Parent item and check whether it is the right one
    QQuickItem* parent = this->parentItem();

    //Check whether it has all needed methods
    int i0 = parent->metaObject()->indexOfMethod("getItemAt(QPoint,int)");
    int i1 = parent->metaObject()->indexOfSignal("getItemAtResult(QObject*,int)");

    if (i0 == -1 || i1 == -1){
        m_validParentItem = false;
        qWarning() << "MtqIntegratorWidget Error: unable to find all needed Methods of parent item. \n"
                 << "Please make sure that you have the modified QtQuick3d Version installed and placed this \n"
                 << "Widget as a child of a QtQuick3d 'View'-Item";
        return;
    }

    qDebug() << "MtqIntegratorWidget initialisation successful";

    m_validParentItem = true;
    initializeParentBindings(parent);
}

void MtqIntegratorWidget::initializeParentBindings(QQuickItem *parent){
    m_parentItem = parent;

    connect(m_parentItem,SIGNAL(getItemAtResult(QObject*,int)),SLOT(itemAtResult(QObject*,int)));

    int i = m_parentItem->metaObject()->indexOfMethod("getItemAt(QPoint,int)");
    m_itemAtMethod = m_parentItem->metaObject()->method(i);

    int j = m_parentItem->metaObject()->indexOfMethod("depthAt(float,float)");
    m_depthAtMethod = m_parentItem->metaObject()->method(j);

    int camindex = m_parentItem->metaObject()->indexOfProperty("camera");
    QMetaProperty metaCam = m_parentItem->metaObject()->property(camindex);
    QVariant camvalue = metaCam.read(m_parentItem);
    m_camera = qvariant_cast<QGLCamera *>(camvalue);
    m_camera->setUpVector(QVector3D(0.0,1.0,0.0));
}

bool MtqIntegratorWidget::dispatch(PositionEvent::Ptr event){
    FloorEvent::Ptr floorEvent = event.dynamicCast<const FloorEvent>();
    QString className = floorEvent->metaObject()->className();

    if (m_printDebug){
        qDebug() << "FloorEvent '" << className << "' for user '" << floorEvent->user().username << "' (id: " << floorEvent->id() << ")";
    }

	QPoint floorPosition = QPoint(floorEvent->position().x(),floorEvent->position().y());
	QString user = floorEvent->user().username;
    int id = floorEvent->id();
    QVector2D tiltDirection = floorEvent->tiltDirection();

    if (className == ContactDownEvent::staticMetaObject.className()){
        processContactDown(floorPosition, id, user, tiltDirection, false);
        return true;
    } else if (className == ContactUpEvent::staticMetaObject.className()){
        processContactUp(floorPosition, id);
        return true;
    } else if (className == ContactMoveEvent::staticMetaObject.className()){
		processContactMove(floorPosition, id, user, floorEvent->tiltDirection());
        return true;
    } else if (className == TapEvent::staticMetaObject.className()){
        processTap(floorPosition, id, user);
        return true;
    } else if (className == DoubleTapEvent::staticMetaObject.className()){
        processDoubleTap(floorPosition, id, user);
        return true;
    } else {
     return false;
    }
}

/**
 * @brief MtqIntegratorWidget::mapScreenToQml Maps a point on the screen to the OffCenter Grid (= the cameras viewSize with (0|0) in the middle)
 * @param screen
 * @return
 */
QPointF MtqIntegratorWidget::mapScreenToQml(QPoint screen){
    QPointF ndcPos = QPointF(screen.x() / (double)m_screenSize.width(),
                             screen.y() / (double)m_screenSize.height());

    ndcPos.setX(ndcPos.x() - 0.5);
    ndcPos.setY(ndcPos.y() - 0.5);
    ndcPos.setY(ndcPos.y() * -1.0);

    if (m_camera->projectionType() == QGLCamera::OffCenterProjection){
        //Adjust coordinates, since the off center projection is a bit larger than the specified viewport
        ndcPos.setX(ndcPos.x() * 1.11f);
        ndcPos.setY(ndcPos.y() * 1.16f);
    }

    QPointF qmlPos = QPointF(m_camera->viewSize().width() * ndcPos.x(),
                             m_camera->viewSize().height() * ndcPos.y());

    return qmlPos;
}

bool MtqIntegratorWidget::itemAt(QPoint screenPosition, int customIdentifier){
    if (!m_validParentItem)
        return false;

    return m_itemAtMethod.invoke(m_parentItem,Qt::DirectConnection,Q_ARG(QPoint,screenPosition),Q_ARG(int,customIdentifier));
}

void MtqIntegratorWidget::mouseDoubleClickEvent(QMouseEvent *event){
    mouseDoubleClick(event->pos());
}

void MtqIntegratorWidget::mouseMoveEvent(QMouseEvent *event){
    mouseMove(event->pos());
}

void MtqIntegratorWidget::mousePressEvent(QMouseEvent *event){
    mousePress(event->pos());
}

void MtqIntegratorWidget::mouseReleaseEvent(QMouseEvent *event){
    mousePress(event->pos());
}

void MtqIntegratorWidget::mouseClickEvent(QMouseEvent *event){
    mouseClicked(event->pos());
}

void MtqIntegratorWidget::mouseClicked(QPoint eventPoint){
    if (m_fuzzyInput)
        processTap(randomize(eventPoint), 1337);
    else
        processTap(eventPoint, 1337);
}

void MtqIntegratorWidget::mouseDoubleClick(QPoint eventPoint){
    if (m_fuzzyInput)
        processDoubleTap(randomize(eventPoint), 1337, QLatin1String("Mouse"));
    else
        processDoubleTap(eventPoint, 1337, QLatin1String("Mouse"));
}

void MtqIntegratorWidget::mouseMove(QPoint eventPoint){
    if (m_fuzzyInput)
		processContactMove(randomize(eventPoint),1337, QLatin1String("Mouse"));
    else
        processContactMove(eventPoint, 1337);
}

void MtqIntegratorWidget::mouseRelease(QPoint eventPoint){
    if (m_fuzzyInput)
        processContactUp(randomize(eventPoint), 1337);
    else
        processContactUp(eventPoint, 1337);
}

void MtqIntegratorWidget::mousePress(QPoint eventPoint){
    if (m_fuzzyInput)
        processContactDown(randomize(eventPoint), 1337, QLatin1String("Mouse"));
    else
        processContactDown(eventPoint, 1337, QLatin1String("Mouse"));
}

QPoint MtqIntegratorWidget::randomize(QPoint position, float percentage){
    //get float 0.0 to 1.0
    float randx = qrand() / (float)RAND_MAX;
    float randy = qrand() / (float)RAND_MAX;

    //map to -1 to 1
    randx = randx * 2.0f - 1.0f;
    randy = randy * 2.0f - 1.0f;

    //error calculated on hd screen
    float maxError = 1900 * percentage;

    int newX = (int) qRound(position.x() + randx * maxError);
    int newY = (int) qRound(position.y() + randy * maxError);

    return QPoint(newX, newY);
}

void MtqIntegratorWidget::setDebugContactDown(int contactId, QPointF position, QString user){
    QPoint p = QPoint((int)qRound(position.x()),(int)qRound(position.y()));

    if (m_fuzzyInput)
        processContactDown(randomize(p),contactId, user, QVector2D(0,0), true);
    else
        processContactDown(p,contactId, user, QVector2D(0,0), true);
}

void MtqIntegratorWidget::setDebugContactMove(int contactId, QPointF position, QString userName){
    QPoint p = QPoint((int)qRound(position.x()),(int)qRound(position.y()));

    if (m_fuzzyInput)
		processContactMove(randomize(p),contactId, userName, QVector2D(0,0));
    else
		processContactMove(p,contactId, userName, QVector2D(0,0));
}

void MtqIntegratorWidget::setDebugContactUp(int contactId, QPointF position){
    QPoint p = QPoint((int)qRound(position.x()),(int)qRound(position.y()));

    if (m_fuzzyInput)
        processContactUp(randomize(p),contactId);
    else
        processContactUp(p,contactId);
}


void MtqIntegratorWidget::setDebugContactTap(int contactId, QPointF position, QString user){
    QPoint p = QPoint((int)qRound(position.x()),(int)qRound(position.y()));

    if (m_fuzzyInput)
        processTap(randomize(p),contactId, user);
    else
        processTap(p,contactId, user);
}


void MtqIntegratorWidget::processTap(QPoint position, int contactId, QString userName){
    if (m_printDebug){
        qDebug() << "MtqIntegrator: processing Tap #" << contactId << " at " << position;
    }

	ContactStruct c;
	c.position = position;
	c.isDebugContact = false;
	c.age = 0;
	c.userName = userName.mid(0); //copy string

	m_contacts.remove(contactId);
	m_contacts.insert(contactId, c);

    int resVal = EVENT_TAP | contactId;
    itemAt(position, resVal);
}


void MtqIntegratorWidget::processDoubleTap(QPoint position, int contactId, QString userName){
    if (m_printDebug){
        qDebug() << "MtqIntegrator: processing DoubleTap #" << contactId << " at " << position;
    }

	ContactStruct c;
	c.position = position;
	c.age = 0;
	c.isDebugContact = false;
	c.userName = userName.mid(0); //copy string

	m_contacts.remove(contactId);
	m_contacts.insert(contactId, c);

    int resVal = EVENT_DOUBLETAP | contactId;
    itemAt(position, resVal);
}

void MtqIntegratorWidget::processContactDown(QPoint position, int contactId, QString userName, QVector2D tiltDirection, bool IsDebugContact){
    if (m_printDebug){
        qDebug() << "MtqIntegrator: processing ContactDown #" << contactId << " at " << position;
    }

    int resVal = EVENT_CONTACTDOWN | contactId;
    itemAt(position,resVal);    

	ContactStruct c;
	c.position = position;
	c.age = 0;
	c.userName = userName.mid(0); //copy string
	c.tiltingDirection = tiltDirection;
    c.isDebugContact = IsDebugContact;

	m_contacts.remove(contactId);
	m_contacts.insert(contactId, c);

    emit mtqContactDown(contactId, position);

    calculateAveragePosition();
    updateCamera();
}

void MtqIntegratorWidget::processContactMove(QPoint position, int contactId, QString userName, QVector2D tiltDirection){
	ContactStruct c;
	if (m_contacts.contains(contactId)){
		c = m_contacts.value(contactId);
		m_contacts.remove(contactId);
	} else {
		//this contact was removed because it did not move enough and was too old. do not process further
		return;
	}

	if (m_printDebug){
        qDebug() << "MtqIntegrator: processing ContactMove #" << contactId << " at " << position;
    }

    itemAt(position,EVENT_CONTACTMOVE | contactId);

    float movedDistance = qSqrt((position.x()-c.position.x())*(position.x()-c.position.x()) +
                                (position.y()-c.position.y())*(position.y()-c.position.y()));
    //only reset contact age if contact moved noticeable
    if (movedDistance > 4){
        c.age = 0;
    }

	c.position = position;
	c.tiltingDirection = tiltDirection;
	c.userName = userName.mid(0); //copy string
	m_contacts.insert(contactId, c);

    emit mtqContactMove(contactId, position);

    calculateAveragePosition();
    updateCamera();
}

void MtqIntegratorWidget::processContactUp(QPoint position, int contactId){
    if (m_printDebug){
        qDebug() << "MtqIntegrator: processing ContactUp #" << contactId << " at " << position;
    }

    itemAt(position,EVENT_CONTACTUP | contactId);
    emit mtqContactUp(contactId, position);

	m_contacts.remove(contactId);

    calculateAveragePosition();
    updateCamera();
}

void MtqIntegratorWidget::itemAtResult(QObject *object, int identifier){    
    if (object == 0)
        return;

    int flag = identifier & EVENT_ONLYFLAG;
    int id = identifier & EVENT_CLEARFLAGS;

    QVariant idVar = QVariant(id);

    ContactStruct contact = m_contacts.value(id);
    QPoint pos = contact.position;
    QVector2D tilting = contact.tiltingDirection;
    //Calculate coordinates in QML-CoordSpace
    QPointF qmlPos = mapScreenToQml(pos);
    QVariant eventPos = QVariant(qmlPos);
    QString user = contact.userName;

    switch(flag){
        case EVENT_TAP:
            if (object->metaObject()->indexOfMethod("mtqTap(QVariant,QVariant)") >= 0){
                if (m_printDebug){ qDebug() << "MtqIntegrator: calling Tap #" << id; }
                QMetaObject::invokeMethod(object,"mtqTap",Q_ARG(QVariant,idVar),Q_ARG(QVariant,eventPos));
            } else {
                if (m_printDebug){ qDebug() << "MtqIntegrator: No object to call Tap #" << id; }
            }
            break;
        case EVENT_DOUBLETAP:
            if (object->metaObject()->indexOfMethod("mtqDoubleTap(QVariant,QVariant)") >= 0){
                    if (m_printDebug){ qDebug() << "MtqIntegrator: calling DoubleTap #" << id; }
                    QMetaObject::invokeMethod(object,"mtqDoubleTap",Q_ARG(QVariant,idVar),Q_ARG(QVariant,eventPos));
            } else {
                if (m_printDebug){ qDebug() << "MtqIntegrator: No object to call DoubleTap #" << id; }
            }
            break;
        case EVENT_CONTACTDOWN:
            if (object->metaObject()->indexOfMethod("mtqContactDown(QVariant,QVariant)") >= 0){
                if (m_printDebug){ qDebug() << "MtqIntegrator: calling ContactDown #" << id; }
                QMetaObject::invokeMethod(object,"mtqContactDown",Q_ARG(QVariant,idVar),Q_ARG(QVariant,eventPos));
            } else {
                if (m_printDebug){ qDebug() << "MtqIntegrator: No object to call ContactDown #" << id; }
            }
            break;
        case EVENT_CONTACTMOVE:
            if (object->metaObject()->indexOfMethod("mtqContactMove(QVariant,QVariant)") >= 0){
                if (m_printDebug){ qDebug() << "MtqIntegrator: calling ContactMove #" << id; }
                QMetaObject::invokeMethod(object,"mtqContactMove",Q_ARG(QVariant,idVar),Q_ARG(QVariant,eventPos));
            } else {
                if (m_printDebug){ qDebug() << "MtqIntegrator: No object to call ContactMove #" << id; }
            }
            break;
        case EVENT_CONTACTUP:
            if (object->metaObject()->indexOfMethod("mtqContactUp(QVariant,QVariant)") >= 0){
                if (m_printDebug){ qDebug() << "MtqIntegrator: calling ContactUp #" << id; }
                QMetaObject::invokeMethod(object,"mtqContactUp",Q_ARG(QVariant,idVar),Q_ARG(QVariant,eventPos));
            } else {
                if (m_printDebug){ qDebug() << "MtqIntegrator: No object to call ContactUp #" << id; }
            }
            break;
    }

    //Remove contacts after Tap
    switch(flag){
        case EVENT_TAP:
        case EVENT_DOUBLETAP:
            m_contacts.remove(id);
            break;
    }
}

void MtqIntegratorWidget::calculateAveragePosition(){
    double avgX = 0.0;
    double avgY = 0.0;

	QVector2D avgTilt = QVector2D(0,0);
	int tiltCount = 0;

    int valueCount = 0;
    int contactMaxAge = 60;

    //Make every contact older and remove contacts that are unchanged since X frames (removes dead contacts)
	for (int i=0; i < m_contacts.keys().size(); i++){
		int contactId = m_contacts.keys().at(i);
		ContactStruct contact = m_contacts.value(contactId);

        if (!contact.isDebugContact){
            contact.age++;
        }

		if (contact.age > contactMaxAge){
			m_contacts.remove(contactId);
			qDebug() << "MtqIntegrator removed Contact #" << contactId << " (too old)";
			continue;
		} else {
			m_contacts.remove(contactId);
			m_contacts.insert(contactId, contact);
		}

		avgX += contact.position.x();
		avgY += contact.position.y();
		valueCount++;

		if (contact.tiltingDirection != QVector2D(0,0)){
			avgTilt += contact.tiltingDirection;
			tiltCount++;
		}

	}

    if (valueCount > 0){
        avgX = avgX / (double)valueCount;
        avgY = avgY / (double)valueCount;

		if (tiltCount > 0){
			avgTilt = avgTilt / (float) tiltCount;
			avgTilt = avgTilt * QVector2D(-1,1);
			avgTilt = avgTilt * m_tiltingMultiplicator;
		} else {
			avgTilt = QVector2D(0,0);
		}

		m_userPosition = QPoint(avgX + avgTilt.x(), avgY + avgTilt.y());
    } else {
        //Let camera stay at last position
    }

    emit userPositionChanged(mapScreenToQml(m_userPosition));

    //update debug view if enabled
    if(m_paintDebugInfo){
        update();
    }
}

float MtqIntegratorWidget::depthAtUserPosition(){
    float retVal = 0.0f;
    QPointF scenePos = mapScreenToQml(m_userPosition);
    m_depthAtMethod.invoke(m_parentItem,Qt::DirectConnection,Q_RETURN_ARG(float,retVal),Q_ARG(float,scenePos.x()),Q_ARG(float,scenePos.y()));
    return retVal;
}

void MtqIntegratorWidget::updateCamera(){
    //Don't do anything if camera movement is disabled (e.g. for othorgaphic projection)
    if (!m_moveCamera)
        return;

    //set eye to user position
    m_goalEye = m_camera->eye();
    m_goalEye.setX(m_userPosition.x());
    m_goalEye.setY(m_userPosition.y());

    //scale down values from screen coordinates to camspace
    float viewWidth = m_camera->viewSize().width();
    float viewHeight = m_camera->viewSize().height();

    float scaleX = viewWidth / m_screenSize.width();
    float scaleY = viewHeight / m_screenSize.height();

    m_goalEye.setX( m_goalEye.x() * scaleX - (viewWidth * 0.5));
    m_goalEye.setY( m_goalEye.y() * scaleY - (viewHeight * 0.5));
    m_goalEye.setY( m_goalEye.y() * -1.0);

    //setCenter
    m_goalCenter = m_goalEye;
    m_goalCenter.setZ(0.0);

    updateCameraValues();
}

void MtqIntegratorWidget::updateCameraValues(){
    bool needsUpdateAgain = false;

    if (m_smoothCamera){
        float minimalMovementDistance = 0.025f;
        QVector3D eyeMovingDirection = (m_goalEye - m_camera->eye());
        float moveLength = eyeMovingDirection.length();


        if (moveLength > minimalMovementDistance){
            eyeMovingDirection.normalize();
            QVector3D newEye = m_camera->eye() + eyeMovingDirection * (minimalMovementDistance + moveLength*0.05);
            m_camera->setEye(newEye);
            needsUpdateAgain = true;
        }
    } else {
        m_camera->setEye(m_goalEye);
        m_camera->setCenter(m_goalCenter);
	}

    if (m_adjustHeight){
		float depthTolerance = 0.001f;
        float depth = depthAtUserPosition();

		//don't do anything if depth hasn't changed since last camera adjustment (no new frame)
		if (m_oldDepth != depth){
			m_oldDepth = depth;

			float currentHeightAdjustment = m_camera->offCenterHeightAdjustment();

			if (abs(depth) > depthTolerance){
				//qDebug() << "Depth is " << depth << ", height adjustment " << currentHeightAdjustment;

				float newHeightAdjustment = currentHeightAdjustment ;
				if (depth > 0.0f){
                    newHeightAdjustment -= 0.02f;
				} else {
                    newHeightAdjustment += 0.02f;
				}

				if (abs(newHeightAdjustment) < 1.5){
					m_camera->setOffCenterHeightAdjustment(newHeightAdjustment);
				}
				needsUpdateAgain = true;
			}
		}
    }

    if (needsUpdateAgain)
		QTimer::singleShot(20,this,SLOT(updateCameraSmoothing()));
}

void MtqIntegratorWidget::updateCameraSmoothing(){
    updateCameraValues();
}

QVector2D MtqIntegratorWidget::getContactTilting(int contactId){
    if (m_contacts.contains(contactId)){
        ContactStruct c = m_contacts.value(contactId);
        return c.tiltingDirection;
    } else {
        return QVector2D(0.0f,0.0f);
    }
}

QString MtqIntegratorWidget::getContactUser(int contactId){
    if (m_contacts.contains(contactId)){
        ContactStruct c = m_contacts.value(contactId);
		QString name = c.userName.mid(0);
		if (name.length() > 0)
			return name;
		else
			return QLatin1String("unknown");
    } else {
        return QLatin1String("unknown");
    }
}
