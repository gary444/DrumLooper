//
//  Looper.h
//  DrumLooper
//
//  Created by Gareth Rendle on 05/11/2013.
//
//

#ifndef __DrumLooper__Looper__
#define __DrumLooper__Looper__

#include <iostream>
#include "../JuceLibraryCode/JuceHeader.h"
#include "Layer.h"
#include "LooperGUI.h"
//#include "Metronome.h"

//forward declaration of looperGUI
class LooperGUI;

/**
 Simple audio looper class - loops an audio buffer and records its input into the buffer.
 Also produces a click 4 times each loop.
 */
class Looper :  public Component,
                public LooperGUI::Listener
{
public:
    
    /**
     Constructor - initialise everything
     */
    Looper();
    
    /**
     Destructor
     */
    ~Looper();
    
    //ComponentCallbacks============================================================
	void resized();
	void paint (Graphics &g);
    
    
    //looperGUI listener callbacks
    void playButtonToggled();
    void recordButtonToggled();
    void layerGainChanged(const int layerIndex, float newGain);
    void layerMuteToggled(const int layerIndexToggled, bool shouldBeMuted);
    
    /**
     Starts or stops playback of the looper
     */
    void setPlayState (const bool newState);
    
    /**
     Gets the current playback state of the looper
     */
    bool getPlayState () const;
    
    /**
     Sets the record state of the looper
     */
    void setRecordState (const bool newState);
    
    /**
     Gets the current record state of the looper
     */
    bool getRecordState () const;
    
    /**
     Returns reader position as a number between 0 and 1
     */
    float getReaderPosition ();
    
    void trigger();
    
    void startLoop();
    
    void endLoop();
    
    void setMode(int newModeIndex);
    
    
    //mode 2 stuff
    void tempoValueChanged(const float newTempo);
    void numberOfBeatsChanged(const int newNumberOfBeats);
    
    /**
     Processes the audio sample by sample.
     */
    float processSample (float input, int channel);
    
    //set sample rate in order to calculate correct tempos
    void setSampleRate(const int newSampleRate);
    
    
    
    
    
private:
    
    
    //Shared data
    Atomic<int> recordState;        //these are atomics which means they can be read/written
    Atomic<int> playState;          //in different threads without a CriticalSection
    
    CriticalSection sharedMemory;
    
    //Audio/loop data
    int bufferSize;
    unsigned int bufferPosition;
    int test;
    int sampleRate;
    int modeIndex;
    int beats;
    float tempo;
    
    
    //layers
    OwnedArray<Layer> layers;
    
    int currentLayer;
    
    //gui
    //ScopedPointer<LooperGUI> looperGUI;
    LooperGUI looperGUI;
    
    //metro
    //Metronome metronome;
};

#endif /* defined(__DrumLooper__Looper__) */
