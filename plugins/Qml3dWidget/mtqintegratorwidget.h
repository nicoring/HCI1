#ifndef MTQINTEGRATORWIDGET_H
#define MTQINTEGRATORWIDGET_H

#include <QQuickPaintedItem>
#include <mtq/core/PluginRegistry.h>
#include <PositionEvents/PositionEventDispatcher.h>
#include <types/PositionEvents/PositionEvents.h>
#include <types/PositionEvents/FloorEvents.h>
#include <QHash>
#include <QGLCamera>

namespace mtq{
    class MTQ_EXPORT_PLUGIN MtqIntegratorWidget : public QQuickPaintedItem, public PositionEventDispatcher
    {
        Q_OBJECT
        MTQ_QML_PLUGIN_REGISTRATION(MtqIntegratorWidget, "qml3d")

        Q_PROPERTY(bool smoothCamera READ smoothCamera WRITE setSmoothCamera)
        Q_PROPERTY(bool paintDebugInfo READ paintDebugInfo WRITE setPaintDebugInfo)
        Q_PROPERTY(bool adjustCameraHeightToScene READ adjustCameraHeightToScene WRITE setAdjustCameraHeightToScene NOTIFY adjustCameraHeightToSceneChanged)
        Q_PROPERTY(int tiltingMultiplicator READ tiltingMultiplicator WRITE setTiltingMultiplicator)
        Q_PROPERTY(bool moveCamera READ moveCamera WRITE setMoveCamera)
        Q_PROPERTY(bool printDebugOutput READ printDebugOutput WRITE setPrintDebugOutput)
        Q_PROPERTY(bool fuzzyInput READ fuzzyInput WRITE setFuzzyInput NOTIFY fuzzyInputChanged)
    public:
        explicit MtqIntegratorWidget(QQuickItem *parent = 0);
        void itemChange(ItemChange change, const ItemChangeData &d);
        virtual void paint(QPainter* painter);

        bool smoothCamera() { return m_smoothCamera; }
        void setSmoothCamera(bool value){ m_smoothCamera = value; }

        bool paintDebugInfo() { return m_paintDebugInfo; }
        void setPaintDebugInfo(bool value){ m_paintDebugInfo = value;}

        bool adjustCameraHeightToScene() { return m_adjustHeight; }
        void setAdjustCameraHeightToScene(bool value) { m_adjustHeight = value; emit adjustCameraHeightToSceneChanged(value);}

		int tiltingMultiplicator(){ return m_tiltingMultiplicator; } void setTiltingMultiplicator(int value){ m_tiltingMultiplicator = value;}

        bool moveCamera(){ return m_moveCamera; } void setMoveCamera(bool value){ m_moveCamera = value; }

        bool printDebugOutput() {return m_printDebug;}
        void setPrintDebugOutput(bool value) {m_printDebug = value;}

        bool fuzzyInput() {return m_fuzzyInput;}
        void setFuzzyInput(bool value) {m_fuzzyInput = value; emit fuzzyInputChanged();}

        Q_INVOKABLE void setDebugContactDown(int contactId, QPointF position, QString user = QLatin1String(""), qreal direction = std::numeric_limits<qreal>::quiet_NaN());
        Q_INVOKABLE void setDebugContactMove(int contactId, QPointF position, QString user = QLatin1String(""), qreal direction = std::numeric_limits<qreal>::quiet_NaN());
        Q_INVOKABLE void setDebugContactUp(int contactId, QPointF position);
        Q_INVOKABLE void setDebugContactTap(int contactId, QPointF position, QString user = QLatin1String(""));

        Q_INVOKABLE QVector2D getContactTilting(int contactId);
        Q_INVOKABLE QString getContactUser(int contactId);
        Q_INVOKABLE qreal getContactDirection(int contactId);
    signals:
        void userPositionChanged(QPointF qmlUserPosition);
        void adjustCameraHeightToSceneChanged(bool value);
        void fuzzyInputChanged();

        void mtqTap(int contactId, QPointF position);
        void mtqDoubleTap(int contactId, QPointF position);
        void mtqContactDown(int contactId, QPointF position);
        void mtqContactMove(int contactId, QPointF position);
        void mtqContactUp(int contactId, QPointF position);
    public slots:
        virtual bool dispatch(PositionEvent::Ptr);
        void itemAtResult(QObject* object, int identifier);

        //Slots to input mouse events that aren't fetched by this widget
        void mouseDoubleClick(QPoint eventPoint);
        void mouseMove(QPoint eventPoint);
        void mousePress(QPoint eventPoint);
        void mouseRelease(QPoint eventPoint);
        void mouseClicked(QPoint eventPoint);

        //Slots to be used by internal timer
        void updateCameraSmoothing();
    protected:
        enum EEventType{
            EVENT_TAP =         0x0A000000,
            EVENT_CONTACTDOWN = 0x0B000000,
            EVENT_CONTACTUP =   0x0C000000,
            EVENT_CONTACTMOVE = 0x0D000000,
            EVENT_DOUBLETAP =   0x0E000000,
            EVENT_CLEARFLAGS =  0xF0FFFFFF,
            EVENT_ONLYFLAG =    0x0F000000,
        };

		struct ContactStruct{
            QString userName;
            bool isDebugContact;
			int age;
			QPoint position;
			QVector2D tiltingDirection;
            double direction;
		};

        virtual void mouseDoubleClickEvent(QMouseEvent *event);
        virtual void mouseClickEvent(QMouseEvent *event);
        virtual void mouseMoveEvent(QMouseEvent *event);
        virtual void mousePressEvent(QMouseEvent *event);
        virtual void mouseReleaseEvent (QMouseEvent *event);

        //Processing MTQ Events
        void processTap(QPoint position, int contactId, QString userName = QLatin1String(""));
        void processDoubleTap(QPoint position, int contactId, QString userName = QLatin1String(""));
        void processContactDown(QPoint position, int contactId, QString userName = QLatin1String(""), QVector2D tiltDirection = QVector2D(0,0), bool isDebugContact = false, qreal direction = std::numeric_limits<qreal>::quiet_NaN());
        void processContactMove(QPoint position, int contactId, QString userName = QLatin1String(""),QVector2D tiltDirection = QVector2D(0,0), qreal direction = std::numeric_limits<qreal>::quiet_NaN());
        void processContactUp(QPoint position, int contactId);

        QPoint randomize(QPoint position, float percentage = 0.005);

        //Item interaction
        bool itemAt(QPoint screenPosition, int customIdentifier);

        //Camera control
        void calculateAveragePosition();
        void updateCamera();

        //etc
        void initializeParentBindings(QQuickItem* parent);
        QPointF mapScreenToQml(QPoint screen);
        void paintDebugLayer(QPainter* p);
    private:
        void updateCameraValues();
        float depthAtUserPosition();

        bool m_moveCamera;
        bool m_validParentItem;
        bool m_printDebug;
        QQuickItem* m_parentItem;
        QMetaMethod m_depthAtMethod;
        QMetaMethod m_itemAtMethod;
        QGLCamera* m_camera;
        bool m_smoothCamera;
        bool m_adjustHeight;
        QPoint m_userPosition;
        bool m_paintDebugInfo;
        bool m_fuzzyInput;

		int m_tiltingMultiplicator;

        QVector3D m_goalEye;
        QVector3D m_goalCenter;

		QHash<int,ContactStruct> m_contacts;

        //Config values
        QSizeF m_floorExtents;
        QSize m_screenSize;

		float m_oldDepth;
    };
}

#endif // MTQINTEGRATORWIDGET_H
