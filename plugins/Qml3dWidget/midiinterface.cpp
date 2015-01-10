#include "midiinterface.h"
using namespace mtq;

MTQ_QML_REGISTER_PLUGIN(MidiInterface)

void MidiInterface::tunnelCallBack(double deltaTime, std::vector<unsigned char> *message, void *userData){
    qDebug() << "**BEAT**";
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

    beatScheduler = 0;
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
void MidiInterface::buttonTapped(int player_id, int button_id)
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
void MidiInterface::buttonDown(int player_id, int button_id)
{
    qDebug() << "Player " << player_id << " on button " << button_id;
    unsigned char note = (unsigned int) ((player_id - 1) * 4 + (button_id - 1));
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
void MidiInterface::buttonUp(int player_id, int button_id)
{
    qDebug() << "Player " << player_id << " released button " << button_id;
    unsigned char note = (unsigned int) ((player_id - 1) * 4 + (button_id - 1));
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
void MidiInterface::myCallback(double deltaTime, std::vector<unsigned char> *message){
    unsigned int size = message->size();
    if(size == 0) return;

    unsigned char byte = (unsigned char) message->at(0);
    switch (byte) {
    case 248:
        if(beatScheduler == 0){
            //TODO: do something here to represent the beat
            qDebug() << "**************BEAT************** DELTA: " << deltaTime;
        }
        else if(beatScheduler == 23){
            beatScheduler = -1;
        }
        beatScheduler++;
        break;
    case 250:
    case 251:
        //TODO: do something here (green light for start? prbly)
        qDebug() << "**************START/CONTINUE**************";
        beatScheduler = 0;
        break;
    case 252:
        //TODO: do something here (red light for stop? prbly)
        qDebug() << "**************STOP**************";
        beatScheduler = 0;
        break;
    }
    // useless compiler warning >.<
}
