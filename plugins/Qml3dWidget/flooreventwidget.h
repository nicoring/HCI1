#ifndef FLOOREVENTWIDGET_H
#define FLOOREVENTWIDGET_H

#include <QQuickItem>
#include <mtq/core/PluginRegistry.h>
#include "mtqintegratorwidget.h"

namespace mtq{
    class MTQ_EXPORT_PLUGIN FloorEventWidget : public QQuickItem
    {
        Q_OBJECT
        MTQ_QML_PLUGIN_REGISTRATION(FloorEventWidget, "qml3d")
    public:
        explicit FloorEventWidget(QQuickItem *parent = 0);
        static void setMtqIntegratorInstance(MtqIntegratorWidget* mtqIntegrator);

        Q_INVOKABLE QVector2D getContactTilting(int contactId);
        Q_INVOKABLE QString getContactUser(int contactId);
        Q_INVOKABLE qreal getContactDirection(int contactId);
    signals:
        void mtqTap(int contactId, QPointF position);
        void mtqDoubleTap(int contactId, QPointF position);
        void mtqContactDown(int contactId, QPointF position);
        void mtqContactMove(int contactId, QPointF position);
        void mtqContactUp(int contactId, QPointF position);
    public slots:
        void onMtqTap(int contactId, QPointF position);
        void onMtqDoubleTap(int contactId, QPointF position);
        void onMtqContactDown(int contactId, QPointF position);
        void onMtqContactMove(int contactId, QPointF position);
        void onMtqContactUp(int contactId, QPointF position);
    private:
        static MtqIntegratorWidget* m_mtqIntegrator;

    };
}

#endif // FLOOREVENTWIDGET_H
