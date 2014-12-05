#include "simplepainter.h"

MTQ_QML_REGISTER_PLUGIN(SimplePainter)

SimplePainter::SimplePainter(QQuickItem *parent) :
    QQuickPaintedItem(parent),
    m_image(100,100,QImage::Format_ARGB32),
    m_penWidth(1),
    m_brushColor("black"),
    m_penColor("black")
{
    m_image.fill(Qt::white);
}

void SimplePainter::paint(QPainter *painter){
    painter;
}

void SimplePainter::clear(QColor clearColor){
    m_image.fill(clearColor);
    emit paintedImageChanged();
}

QImage SimplePainter::paintedImage(){
    return m_image;
}

int SimplePainter::imageWidth(){
    return m_image.width();
}

int SimplePainter::imageHeight(){
    return m_image.height();
}

void SimplePainter::setImageWidth(int value){
    if (value != m_image.width()){
        m_image = QImage(value, m_image.height(), QImage::Format_ARGB32);
        m_image.fill(Qt::white);
        emit imageWidthChanged();
    }
}

void SimplePainter::setImageHeight(int value){
    if (value != m_image.height()){
        m_image = QImage(m_image.width(), value, QImage::Format_ARGB32);
        m_image.fill(Qt::white);
        emit imageHeightChanged();
    }
}

QColor SimplePainter::penColor(){
    return m_penColor;
}

QColor SimplePainter::brushColor(){
    return m_brushColor;
}

void SimplePainter::setPenColor(QColor value){
    m_penColor = value;
    emit penColorChanged();
}

void SimplePainter::setBrushColor(QColor value){
    m_brushColor = value;
    emit brushColorChanged();
}

int SimplePainter::penWidth(){
    return m_penWidth;
}

void SimplePainter::setPenWidth(int value){
    m_penWidth = value;
    emit penWidthChanged();
}

QPainter* SimplePainter::getPainter(){
    QPainter* painter = new QPainter(&m_image);

    QPen p;
    p.setColor(m_penColor);
    p.setWidth(m_penWidth);
    painter->setPen(p);

    QBrush b;
    b.setColor(m_brushColor);
    painter->setBrush(b);

    return painter;
}

void SimplePainter::paintDot(int x, int y){
    QPainter* painter = getPainter();
    painter->drawPoint(x,y);
    delete painter;

    emit paintedImageChanged();
}

void SimplePainter::paintLine(int x1, int y1, int x2, int y2){
    QPainter* painter = getPainter();
    painter->drawLine(x1,y1,x2,y2);
    delete painter;

    emit paintedImageChanged();
}

void SimplePainter::paintEllipse(int cx, int cy, int rx, int ry){
    QPainter* painter = getPainter();
    painter->drawEllipse(QPoint(cx,cy),rx,ry);
    delete painter;

    emit paintedImageChanged();
}
