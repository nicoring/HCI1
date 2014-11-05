#ifndef TEXTDRAWER_H
#define TEXTDRAWER_H

#include <mtq/core/PluginRegistry.h>
#include <QQuickPaintedItem>
#include <QString>
#include <QImage>

class MTQ_EXPORT_PLUGIN TextDrawer : public QQuickPaintedItem
{
    Q_OBJECT
    MTQ_QML_PLUGIN_REGISTRATION(TextDrawer, "qml3d")
public:
    explicit TextDrawer(QQuickItem *parent = 0);

    Q_PROPERTY(QString text READ text WRITE setText)
    QString text(){ return m_text;} void setText(QString value){m_text = value; updateImage();}

    Q_PROPERTY(QImage paintedImage READ paintedImage NOTIFY imageUpdated)
    QImage paintedImage() {return m_paintedImage;}

    Q_PROPERTY(int imageWidth READ imageWidth WRITE setImageWidth)
    int imageWidth(){return m_paintedImage.width();} void setImageWidth(int value){m_paintedImage = QImage(value,m_paintedImage.height(),QImage::Format_ARGB32); updateImage();}
    Q_PROPERTY(int imageHeight READ imageHeight WRITE setImageHeight)
    int imageHeight(){return m_paintedImage.height();} void setImageHeight(int value){m_paintedImage = QImage(m_paintedImage.width(),value,QImage::Format_ARGB32); updateImage();}

    Q_PROPERTY(QString fontFamily READ fontFamily WRITE setFontFamily)
    QString fontFamily(){return m_fontFamily;} void setFontFamily(QString value){m_fontFamily = value; updateImage();}
    Q_PROPERTY(int fontSize READ fontSize WRITE setFontSize)
    int fontSize(){return m_fontSize;} void setFontSize(int value){m_fontSize = value; updateImage();}
    Q_PROPERTY(QColor fontColor READ fontColor WRITE setFontColor)
    QColor fontColor(){return m_fontColor;} void setFontColor(QColor value){m_fontColor = value; updateImage();}

    void paint(QPainter *painter);
signals:
    void imageUpdated();
public slots:

private:
    QString m_text;
    QString m_fontFamily;
    int m_fontSize;
    QColor m_fontColor;

    QImage m_paintedImage;

    void updateImage();
};

#endif // TEXTDRAWER_H
