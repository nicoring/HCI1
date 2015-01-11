#include "flooreventwidget.h"
using namespace mtq;

MTQ_QML_REGISTER_PLUGIN(FloorEventWidget)

MtqIntegratorWidget* FloorEventWidget::m_mtqIntegrator = 0;

FloorEventWidget::FloorEventWidget(QQuickItem *parent) :
    QQuickItem(parent)
{
    //Bind slots to forward events
    if (!m_mtqIntegrator){
        qDebug() << "FloorEventWidget: Error: MtqIntegratorWidget instance is not defined";
        return;
    }

    connect(m_mtqIntegrator, SIGNAL(mtqTap(int,QPointF)), SLOT(onMtqTap(int,QPointF)));
    connect(m_mtqIntegrator, SIGNAL(mtqDoubleTap(int, QPointF)), SLOT(onMtqDoubleTap(int,QPointF)));
    connect(m_mtqIntegrator, SIGNAL(mtqContactDown(int,QPointF)), SLOT(onMtqContactDown(int,QPointF)));
    connect(m_mtqIntegrator, SIGNAL(mtqContactUp(int,QPointF)), SLOT(onMtqContactUp(int,QPointF)));
    connect(m_mtqIntegrator, SIGNAL(mtqContactMove(int,QPointF)), SLOT(onMtqContactMove(int,QPointF)));
}

void FloorEventWidget::setMtqIntegratorInstance(MtqIntegratorWidget *mtqIntegrator){
    m_mtqIntegrator = mtqIntegrator;
}

void FloorEventWidget::onMtqTap(int contactId, QPointF position){
    emit mtqTap(contactId, position);
}

void FloorEventWidget::onMtqDoubleTap(int contactId, QPointF position){
    emit mtqDoubleTap(contactId, position);
}

void FloorEventWidget::onMtqContactDown(int contactId, QPointF position){
    emit mtqContactDown(contactId, position);
}

void FloorEventWidget::onMtqContactUp(int contactId, QPointF position){
    emit mtqContactUp(contactId, position);
}

void FloorEventWidget::onMtqContactMove(int contactId, QPointF position){
    emit mtqContactMove(contactId, position);
}

QVector2D FloorEventWidget::getContactTilting(int contactId){
    return m_mtqIntegrator->getContactTilting(contactId);
}

QString FloorEventWidget::getContactUser(int contactId){
    return m_mtqIntegrator->getContactUser(contactId);
}

qreal FloorEventWidget::getContactDirection(int contactId){
    return m_mtqIntegrator->getContactDirection(contactId);
}
