#ifndef CIRCLECONTROLLER_H
#define CIRCLECONTROLLER_H

#include <QtQuick/QQuickItem>
#include <QObject>
#include <QDebug>
#include <QQuickPaintedItem>
#include <mtq/core/PluginRegistry.h>
#include <stdlib.h>

namespace mtq {

class MTQ_EXPORT_PLUGIN CircleController : public QQuickItem
{
    Q_OBJECT
    MTQ_QML_PLUGIN_REGISTRATION(CircleController, "qml3d")

public:
    explicit CircleController(QQuickItem *parent = 0);
    virtual void paint(QPainter* painter);
    void beat();
    void rotateToPlayer(int num);
    void chooseRandomSoloPlayer();

signals:
    void doBeat();
    void doRotateToPlayer(int playerNum);

public slots:

};

}

#endif // CIRCLECONTROLLER_H
