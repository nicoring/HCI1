#ifndef SIMPLEPAINTER_H
#define SIMPLEPAINTER_H

#include <mtq/core/PluginRegistry.h>

#include <QQuickPaintedItem>
#include <QImage>
#include <QPainter>

class MTQ_EXPORT_PLUGIN SimplePainter : public QQuickPaintedItem
{
    Q_OBJECT
    MTQ_QML_PLUGIN_REGISTRATION(SimplePainter, "qml3d")
public:
    explicit SimplePainter(QQuickItem *parent = 0);

    Q_PROPERTY(QImage paintedImage READ paintedImage NOTIFY paintedImageChanged)
    QImage paintedImage();

    Q_PROPERTY(int imageWidth READ imageWidth WRITE setImageWidth NOTIFY imageWidthChanged)
    int imageWidth();
    void setImageWidth(int value);

    Q_PROPERTY(int imageHeight READ imageHeight WRITE setImageHeight NOTIFY imageHeightChanged)
    int imageHeight();
    void setImageHeight(int value);

    Q_PROPERTY(QColor penColor READ penColor WRITE setPenColor NOTIFY penColorChanged)
    QColor penColor();
    void setPenColor(QColor value);

    Q_PROPERTY(QColor brushColor READ brushColor WRITE setBrushColor NOTIFY brushColorChanged)
    QColor brushColor();
    void setBrushColor(QColor value);

    Q_PROPERTY(int penWidth READ penWidth WRITE setPenWidth NOTIFY penWidthChanged)
    int penWidth();
    void setPenWidth(int value);

    Q_INVOKABLE void clear(QColor clearColor);
    Q_INVOKABLE void paintDot(int x, int y);
    Q_INVOKABLE void paintLine(int x1, int y1, int x2, int y2);
    Q_INVOKABLE void paintEllipse(int cx, int cy, int rx, int ry);

    void paint(QPainter *painter);
signals:    
    void paintedImageChanged();
    void imageWidthChanged();
    void imageHeightChanged();
    void penColorChanged();
    void brushColorChanged();
    void penWidthChanged();
protected:
    QPainter* getPainter();
private:
    QImage m_image;
    QColor m_brushColor;
    QColor m_penColor;
    int m_penWidth;
};

#endif // SIMPLEPAINTER_H
