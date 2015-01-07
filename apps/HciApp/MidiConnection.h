#ifndef MIDICONNECTION_H
#define MIDICONNECTION_H

#pragma once
#include <iostream>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#include "Rtmidi.h"
#include <signal.h>
#include <conio.h>
#include <cstdlib>
using namespace std;

class MidiOutput
{
public:
    MidiOutput(unsigned char port);
    virtual ~MidiOutput(void);
    void sendNote(unsigned char note, unsigned char velocity);
    void stopNote(unsigned char note, unsigned char velocity);
    //void sendConrolChange(unsigned char control, unsigned char value);
    void sendStatement(unsigned char status, unsigned char note, unsigned char velocity);
    void printOutPortNames();
    unsigned int amountOfOutPorts();
private:
    RtMidiOut *midiOut;
    vector<unsigned char> messenger;
};

class MidiInput
{
public:
    typedef void (*MidiCallback)();
    MidiInput(unsigned char port);
    virtual ~MidiInput(void);
    void printInPortNames();
    unsigned int amountOfInPorts();
    void setBeatCallback(MidiCallback callback, void *userData = 0);
private:
    RtMidiIn *midiIn;
    MidiCallback beatCallback;
    void callbackMidiIn(double deltatime, vector<unsigned char> *message, void *userData);
};

#endif // MIDICONNECTION_H
