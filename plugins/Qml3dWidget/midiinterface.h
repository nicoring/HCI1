#ifndef MIDIINTERFACE_H
#define MIDIINTERFACE_H


#include <QObject>
#include <QDebug>
#include <mtq/core/PluginRegistry.h>

class MidiInterface : public QObject
{
    Q_OBJECT
    // TODO: does not seem to register correctly. please check.
    MTQ_QML_PLUGIN_REGISTRATION(MidiInterface, "qml3d")

public:
    explicit MidiInterface(QObject *parent = 0);

    // triggered by user interaction
    // signal the midi transmission class from Alex
    Q_INVOKABLE void buttonTapped(int player_id, int button_id);

signals:
    // player tapped a button and requests the linked midi sound
    // connect this signal to a slot in midi transmission class
    void playerRequestsMidiForButton(int player_id, int button_id);

public slots:

};

#endif // MIDIINTERFACE_H
