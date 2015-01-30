#include "midiinterface.h"
#include <QDebug>
using namespace mtq;

MTQ_QML_REGISTER_PLUGIN(MidiInterface)

int beatCounter;
MidiInterface *instance;

/**
 * Callback function passed to RtMidiIn held by Interface-Class. Receives messages
 * confirm to 24 ppqn - pulses per quarter note. So counting starts after receiving
 * DAWs start message, encoded by first byte = 250. Stop resets counter, encoded
 * by first byte = 252. Beat Clocks first byte is = 248. 251 is 'continue' (track mode)
 *
 * @brief MidiInterface::myCallback
 * @param deltaTime
 * @param message   Midi-Triple - In our use case usually only first byte (midi-clock)
 */
void MidiInterface::tunnelCallBack(double deltaTime, std::vector<unsigned char> *message, void *userData){
    unsigned int size = message->size();
    if(size == 0) return;

    unsigned char byte = (unsigned char) message->at(0);
    switch (byte) {
    case 248:
        if(beatCounter == 0){
            instance->clockBeat(deltaTime);
            qDebug() << "**************BEAT************** DELTA: " << deltaTime;
        }
        else if(beatCounter == 23){
            beatCounter = -1;
        }
        beatCounter++;
        break;
    case 250:
    case 251:
        //TODO: do something here (green light for start? prbly)
        qDebug() << "**************START/CONTINUE**************";
        beatCounter = 0;
        break;
    case 252:
        //TODO: do something here (red light for stop? prbly)
        qDebug() << "**************STOP**************";
        beatCounter = 0;
        break;
    }
    // useless compiler warning >.<
    return;
}

MidiInterface::MidiInterface(QQuickItem *parent) :
    QQuickPaintedItem(parent)
{

    /************Ports used*************/
    unsigned char outPort = 1;
    unsigned char inPort = 0;
    /***********************************/

    //****************MIDI OUT*******
    try{
        midiOut = new RtMidiOut();
    }
    catch(RtMidiError &error){
        error.printMessage();
    }

    // Check available ports
    if (midiOut->getPortCount() == 0) {
        qDebug() << "No more Out-Ports available!";
        delete midiOut;
    }
    else {
        // try to open defined port
        try {
            midiOut->openPort(outPort);
            qDebug() << "Found ports:" << "\n";
            qDebug() << "1." << midiOut->getPortName(0).c_str();
            qDebug() << "2." << midiOut->getPortName(1).c_str();
        }
        catch(RtMidiError &error) {
            error.printMessage();
        }
    }

    //******************************

    //****************MIDI IN*******
    try{
        midiIn = new RtMidiIn();
    }
    catch(RtMidiError &error){
        error.printMessage();
    }

    // Check available ports
    if (midiIn->getPortCount() == 0) {
        qDebug() << "No more In-Ports available";
        delete midiIn;
    }
    else {
        try {
            qDebug() << midiIn->getPortName(0).c_str();
            midiIn->openPort(inPort);
        }
        catch(RtMidiError &error) {
            error.printMessage();
        }
        // Set callback function
        midiIn->setCallback( &tunnelCallBack );
        // Don't ignore sysex, timing, or active sensing messages.
        midiIn->ignoreTypes( false, false, false );
    }


    //******************************


    // allocate the Midi-Messenger-Triple and init scheduler
    messenger.push_back(0);
    messenger.push_back(0);
    messenger.push_back(0);

    beatCounter = 0;

    sendStartMessage();

    instance = this;
}

// inherited from abstract method, but unused
void MidiInterface::paint(QPainter *painter){
    painter; // hacky -- but removes a compiler warning
}

/**
 * Triggered when button was tapped by player.
 * This should notify the ableton project to start midi signal transmission.
 *
 * @brief MidiInterface::buttonTapped
 * @param player_id
 * @param button_id
 */
void MidiInterface::buttonTapped(int player_id, int button_id, int offset)
{
    qDebug() << "Player " << player_id << " tapped button " << button_id;
}

/**
 * Triggered when player is on button.
 * This should notify the ableton project to start midi signal transmission.
 *
 * @brief MidiInterface::buttonTapped
 * @param player_id
 * @param button_id
 */
void MidiInterface::buttonDown(int player_id, int button_id, int instrument_id)
{
    qDebug() << "Player " << player_id << " on button " << button_id;
    unsigned char note = (unsigned int) ((player_id - 1) % 2) * 16 + ((instrument_id - 1) * 4 + (button_id - 1));
    unsigned char velocity = 127;

    messenger[0] = 144;
    // set and send given Note
    messenger[1] = note;
    messenger[2] = velocity;
    if (midiOut != NULL) {
        midiOut->sendMessage(&messenger);
    }
    qDebug() << "sent note " << note << "with velocity" << velocity;
}

/**
 * Triggered when player releases button.
 * This should notify the ableton project to start midi signal transmission.
 *
 * @brief MidiInterface::buttonTapped
 * @param player_id
 * @param button_id
 */
void MidiInterface::buttonUp(int player_id, int button_id, int instrument_id)
{
    qDebug() << "Player " << player_id << " released button " << button_id;
    unsigned char note = (unsigned int) ((player_id - 1) % 2) * 16 + ((instrument_id - 1) * 4 + (button_id - 1));
    unsigned char velocity = 127;

    messenger[0] = 128;
    // set and send given Note
    messenger[1] = note;
    messenger[2] = velocity;
    if (midiOut != NULL) {
        midiOut->sendMessage(&messenger);
    }
    qDebug() << "stop note " << note << "with velocity" << velocity;
}

void MidiInterface::sendStartMessage(){
    // Specified start message
    messenger[0] = 145;
    messenger[1] = 100;
    messenger[2] = 100;
    if (midiOut){
        midiOut->sendMessage(&messenger);
    }
}

void MidiInterface::sendStopMessage(){
    messenger[0] = 145;
    messenger[1] = 102;
    messenger[2] = 100;
    if (midiOut) {
        midiOut->sendMessage(&messenger);
    }
}

void MidiInterface::clockBeat(double time){
    QMetaObject::invokeMethod(this, "showBeat");
}

void MidiInterface::triggerMetronome(){
    messenger[0] = 145;
    messenger[1] = 104;
    messenger[2] = 100;
    if (midiOut) {
        midiOut->sendMessage(&messenger);
    }
}

MidiInterface::~MidiInterface(void){
    sendStopMessage();
}

