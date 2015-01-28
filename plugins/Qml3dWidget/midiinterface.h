#ifndef MIDIINTERFACE_H
#define MIDIINTERFACE_H

#include <QtQuick/QQuickItem>
#include <QObject>
#include <QDebug>
#include <QQuickPaintedItem>
#include <mtq/core/PluginRegistry.h>

#define __WINDOWS_MM__
#include <iostream>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#include "Rtmidi.h"
using namespace std;

namespace mtq {

class MTQ_EXPORT_PLUGIN MidiInterface : public QQuickPaintedItem
{
    Q_OBJECT
    // TODO: does not seem to register correctly. please check.
    MTQ_QML_PLUGIN_REGISTRATION(MidiInterface, "qml3d")

public:
    explicit MidiInterface(QQuickItem *parent = 0);
    virtual void paint(QPainter* painter);
    virtual ~MidiInterface(void);

    // triggered by user interaction
    // signal the midi transmission class from Alex
    Q_INVOKABLE void buttonTapped(int player_id, int button_id, int offset);
    Q_INVOKABLE void buttonUp(int player_id, int button_id, int offset);
    Q_INVOKABLE void buttonDown(int player_id, int button_id, int offset);
    void sendStartMessage();
    void sendStopMessage();
    void triggerMetronome();
    void clockBeat(double time);

    static void tunnelCallBack(double deltaTime, std::vector<unsigned char> *message, void *userData);

signals:
    // player tapped a button and requests the linked midi sound
    // connect this signal to a slot in midi transmission class
    void playerRequestsMidiForButton(int player_id, int button_id);

public slots:

private:
    RtMidiOut *midiOut;
    RtMidiIn *midiIn;
    vector<unsigned char> messenger;
};

}
#endif // MIDIINTERFACE_H
