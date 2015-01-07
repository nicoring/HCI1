#ifndef MIDIINTERFACE_H
#define MIDIINTERFACE_H


#include <QObject>
#include <QDebug>
#include <QQuickPaintedItem>

#include <mtq/core/PluginRegistry.h>
namespace mtq {
class MTQ_EXPORT_PLUGIN MidiInterface : public QQuickPaintedItem
{
    Q_OBJECT
    // TODO: does not seem to register correctly. please check.
    MTQ_QML_PLUGIN_REGISTRATION(MidiInterface, "qml3d")

public:
    explicit MidiInterface(QQuickItem *parent = 0);
    virtual void paint(QPainter* painter);

    // triggered by user interaction
    // signal the midi transmission class from Alex
    Q_INVOKABLE void buttonTapped(int player_id, int button_id);

signals:
    // player tapped a button and requests the linked midi sound
    // connect this signal to a slot in midi transmission class
    void playerRequestsMidiForButton(int player_id, int button_id);

public slots:

};
}
#endif // MIDIINTERFACE_H
