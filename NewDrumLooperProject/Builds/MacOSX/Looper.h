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
#include "Metronome.h"

/**

 */
class Looper :  public Component,
                public LooperGUI::Listener
{
public:
    
    class Listener
    {
    public:
        virtual ~Listener(){}
        virtual void looperReady(bool isReady) = 0;
        
    };
    
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
    void deleteLayer(int layerIndex);
    void deleteAllLayers();
    
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
    
    void setCountInState (const bool newState);
    
    void trigger();
    
    void startLoop();
    
    void endLoop();
    
    void setMode(int newModeIndex);
    
    
    //mode 2 stuff
    void tempoValueChanged(const float newTempo);
    void numberOfBeatsChanged(const int newNumberOfBeats);
    void countInChanged(const int newNumberOfBeats);
    void metroToggled(bool shouldBeOn);
    
    /**
     Processes the audio sample by sample.
     */
    float processSample (float input, int channel);
    
    //set sample rate in order to calculate correct tempos
    void setSampleRate(const int newSampleRate);
    
    void setListener(Listener* newListener);
    
    
    void tick();
    
    
    
private:
    
    
    //state data
    Atomic<int> recordState;
    Atomic<int> playState;
    Atomic<int> countInState;
    
    CriticalSection sharedMemory;
    
    //Audio/loop data
    int bufferSize;
    int bufferPosition;
    int sampleRate;
    int modeIndex;
    int beats;
    float tempo;
    
    bool metroOn;
    int countInLength;
    int countInCount;
    int countInBeats;
    
    int guiUpdateCount;
    
    bool ready;
    Listener* listener;
    
    
    //layers
    OwnedArray<Layer> layers;
    int currentLayer;
    
    //gui
    //ScopedPointer<LooperGUI> looperGUI;
    LooperGUI looperGUI;
    
    //metro
    Metronome metronome;
};

#endif /* defined(__DrumLooper__Looper__) */
