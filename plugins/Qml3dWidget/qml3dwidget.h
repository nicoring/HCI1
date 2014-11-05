#ifndef QML3DWIDGET_H
#define QML3DWIDGET_H

#include <QtQuick/QQuickItem>
#include <mtq/core/PluginRegistry.h>

namespace mtq{
    class MTQ_EXPORT_PLUGIN Qml3dWidget : public QQuickItem
    {
        Q_OBJECT
        MTQ_QML_PLUGIN_REGISTRATION(Qml3dWidget, "qml3d")

    public:
        explicit Qml3dWidget(QQuickItem *parent = 0);
        void paint(QPainter *painter);
    protected:
        void itemChange(ItemChange change, const ItemChangeData &);
    signals:

    public slots:
        void paint();
        void cleanup();
        void sync();
        void itemAtResult(QObject* obj, int identifier);
    private:
        qreal m_t;
        qreal m_thread_t;
    };
}

#endif // QML3DWIDGET_H
