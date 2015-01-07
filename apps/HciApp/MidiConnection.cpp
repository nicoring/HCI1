#include "MidiConnection.h"
#include "RtMidi.h"

/**********************************************************************/
/*  MidiOutput is used to establish a Midi-Connection via RtMidi on a
    Windows-System and to hold that connection until the object is deleted.
    It provides several functions to control the output of midi-signals.
    Mainly the signals are dedicated to trigger events in a DAW as in
    our case Ableton Live. Further control features as midi-signals
    over time are possible but not yet implemented.
*/
/**********************************************************************/
//*************** CONSTRUCTOR ****************
MidiOutput::MidiOutput(unsigned char port)
{
    // initialize RtMidiOut object
    try{
        midiOut = new RtMidiOut();
    }
    catch(RtMidiError &error){
        error.printMessage();
    }

    // scan for ports. If one is available, connect.
    // Otherwise delete MidiOut and the object just created.
    unsigned int availablOutPorts = midiOut->getPortCount();
    if (availablOutPorts == 0) {
        std::cout << "No more ports available!" << std::endl;
        delete midiOut;
        delete this;
    }

    // try to open given Port
    try {
        midiOut->openPort(port);
    }
    catch(RtMidiError &error) {
        error.printMessage();
    }

    // allocate the Midi-Messenger-Triple
    messenger.push_back(0);
    messenger.push_back(0);
    messenger.push_back(0);
}

//*************** DESTRUCTOR ****************
MidiOutput::~MidiOutput(void)
{
    delete midiOut;
    delete this;
}

// Send note with the given MidiOutput-Object by passing a tuple
// of note and velocity. Status byte is set to note-on.
void MidiOutput::sendNote(unsigned char note, unsigned char velocity){
    // Note On: 144-159 depending on the channels -> 16 channels possible
    messenger[0] = 144;

    // set and send given Notes
    messenger[1] = note;
    messenger[2] = velocity;
    midiOut->sendMessage(&messenger);
}

void MidiOutput::stopNote(unsigned char note, unsigned char velocity){
    messenger[0] = 128;
    messenger[1] = note;
    messenger[2] = velocity;
    midiOut->sendMessage(&messenger);
}

// send given control statement, anything possible
void MidiOutput::sendStatement(unsigned char status, unsigned  char note, unsigned char velocity){
    messenger[0] = status;
    messenger[1] = note;
    messenger[2] = velocity;
}

// print out all midiout port names
void MidiOutput::printOutPortNames(){
    unsigned int count = amountOfOutPorts();
    for(unsigned int i=0; i < count; i++){
        cout << "Port (Out) " << i << ": " << midiOut->getPortName(i) << endl;
    }
}

unsigned int MidiOutput::amountOfOutPorts(){
    return midiOut->getPortCount();
}



/**********************************************************************/
/*	MidiInput is used to establish a Midi-connection via RtMidi on a
    Windows-System and to hold that connection until the object is deleted.
    It is meant to trigger events when a signal comes in. For example
    the midi-beat. Provided with a reference to a function, it can
    trigger the given function everytime the beat-signal is triggered.
*/
/**********************************************************************/
MidiInput::MidiInput(unsigned char port)
{
    // initialize RtMidiIn object
    try{
        midiIn = new RtMidiIn();
    }
    catch(RtMidiError &error){
        error.printMessage();
    }


    // scan for ports. If one is available, connect.
    // Otherwise delete midiIn and the object just created.
    unsigned int availablOutPorts = midiIn->getPortCount();
    if (availablOutPorts == 0) {
        std::cout << "No more ports available!" << std::endl;
        delete midiIn;
        delete this;
    }

    try{
        midiIn->openPort(port);
    }
    catch(RtMidiError &error){
        error.printMessage();
        cout << "not instantiated Midi-Input" << endl;
        delete midiIn;
        delete this;
    }

}

MidiInput::~MidiInput(void)
{
    delete midiIn;
    delete this;
}

void MidiInput::printInPortNames(){
    unsigned int count = amountOfInPorts();
    for(unsigned int i=0; i < count; i++){
        cout << "Port (In) " << i << ": " << midiIn->getPortName(i) << endl;
    }
}

unsigned int MidiInput::amountOfInPorts(){
    return midiIn->getPortCount();
}

void MidiInput::setBeatCallback(MidiCallback callback, void *userData = 0){
    beatCallback = callback;
}

// Private Midicallback Function passed to RtMidiIn
void MidiInput::callbackMidiIn(double deltatime, vector<unsigned char> *message, void *userData){
    if(message->at(0) == 232){
        beatCallback();
    }
}


