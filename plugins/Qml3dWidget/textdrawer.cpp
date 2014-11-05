#include "textdrawer.h"
#include <QPainter>

MTQ_QML_REGISTER_PLUGIN(TextDrawer)

TextDrawer::TextDrawer(QQuickItem *parent) :
    QQuickPaintedItem(parent),
    m_paintedImage(300,300,QImage::Format_ARGB32),
    m_text("abc"),
    m_fontFamily("Helvetica"),
    m_fontSize(20),
    m_fontColor(Qt::black)
{
    updateImage();
}

void TextDrawer::updateImage(){
    m_paintedImage.fill((uint)0x00FFFFFF);

    QPainter* p = new QPainter(&m_paintedImage);
    p->setPen(m_fontColor);
    QFont f = QFont(QString(m_fontFamily),m_fontSize);
    p->setFont(f);
    p->drawText(0,0,m_paintedImage.width(),m_paintedImage.height(),0,m_text);

    delete p;

    emit imageUpdated();
}

void TextDrawer::paint(QPainter *painter){

}
