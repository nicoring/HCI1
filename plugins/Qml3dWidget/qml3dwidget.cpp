#include "qml3dwidget.h"
using namespace mtq;

#include <QtQuick/qquickwindow.h>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLContext>
#include <QGLWidget>

#include <Qt3DQuick/QQuickViewport>
#include <Qt3D/QGLView>

MTQ_QML_REGISTER_PLUGIN(Qml3dWidget)

Qml3dWidget::Qml3dWidget(QQuickItem *parent) :
    QQuickItem(parent)
{
}

void Qml3dWidget::itemChange(ItemChange change, const ItemChangeData &){
    // The ItemSceneChange event is sent when we are first attached to a window.
    if (change == ItemSceneChange) {
        QQuickWindow *win = window();
        if (!win)
            return;

        // Connect the beforeRendering signal to our paint function.
        // Since this call is executed on the rendering thread it must be
        // a Qt::DirectConnection
        connect(win, SIGNAL(beforeRendering()), this, SLOT(paint()), Qt::DirectConnection);
        //connect(win,SIGNAL(afterRendering()),this,SLOT(paint()),Qt::DirectConnection); //<-- if this is enabled, the waves are visible. however, not the rest
        connect(win, SIGNAL(beforeSynchronizing()), this, SLOT(sync()), Qt::DirectConnection);

        // If we allow QML to do the clearing, they would clear what we paint
        // and nothing would show.
        win->setClearBeforeRendering(false);
    }
}

void Qml3dWidget::sync(){
    m_thread_t = m_t;
}

void Qml3dWidget::cleanup(){

}

void Qml3dWidget::paint(){
    //qDebug() << "Qml3dWidget is painting";

    //As a demo, just clearing the Viewport with green color

    glViewport(0, 0, window()->width(), window()->height());

    glDisable(GL_DEPTH_TEST);

    glClearColor(0, 1, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    //Check my surroundings
    //qDebug() << "Parent of Qml3dWidget: " << this->parentItem()->metaObject()->className();


    /*QList<QQuickItem*> childs = this->parentItem()->childItems();
    qDebug() << "Number of Parent Childs: " << childs.size();
    for (int i=0; i < childs.size(); i++){
        qDebug() << "[" << i << "] " << childs.at(i)->metaObject()->className();
        QMetaObject::invokeMethod(childs.at(i),"scaleUp");
    }*/

    //QQuickViewport* viewport = (QQuickViewport*)(this->parentItem());
    //QObject* middleObject = viewport->getItemAt(QPoint(900,500));

    QObject* obj = this->parentItem();

    //Connect signal
    connect(obj,SIGNAL(getItemAtResult(QObject*,int)),SLOT(itemAtResult(QObject*,int)));

    //Invoke method
    int i = obj->metaObject()->indexOfMethod("getItemAt(QPoint,int)");
    qDebug() << "index of desired method is " << i;
    QMetaMethod m = obj->metaObject()->method(i);
    bool invokeSuccess = m.invoke(obj,Qt::DirectConnection,Q_ARG(QPoint,QPoint(900,500)),Q_ARG(int,1337));
    qDebug() << "Invoke was " << invokeSuccess;
}

void Qml3dWidget::itemAtResult(QObject *obj, int identifier){
    if (obj != 0){
        qDebug() << "Item at Result for" << identifier;
        qDebug() << "-> object:" <<obj;
        qDebug() << "-> " << obj->metaObject()->className();
    }
}
