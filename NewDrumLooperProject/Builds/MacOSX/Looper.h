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
#include "CustomAudioThumbnail.h"
#include "BeatDetector.h"
#include "BeatDetectorB.h"

//forward declaration
//class BeatDetector;

/**

 */
class Looper :  public Component,
                public LooperGUI::Listener,
public BeatDetector::Listener,
public BeatDetectorB::Listener,
public KeyListener
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
    void layerPanChanged(const int layerIndex, const float newPanPosition);
    void layerMuteToggled(const int layerIndexToggled, bool shouldBeMuted);
    void deleteLayer(int layerIndex);
    void deleteAllLayers();
    void setReaderToZero();
    void setAlternateLoopRec(bool shouldBeOn);
    
    
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
    
    //void startLoop();
    
    void endLoop();
    
    void setMode(int newModeIndex);
    
    
    //mode 2 stuff
    void tempoValueChanged(const float newTempo);
    void numberOfBeatsChanged(const int newNumberOfBeats);
    void countInChanged(const int newNumberOfBeats);
    void metroToggled(bool shouldBeOn);
    void endLoopOnHitToggled(const bool shouldBeOn);
    
    /**
     Processes the audio sample by sample.
     */
    float processSample (float input, int channel);
    
    //set sample rate in order to calculate correct tempos
    void setSampleRate(const int newSampleRate);
    
    void setListener(Listener* newListener);
    
    //void tick();
    
    //beat detector callbacks
    void tempoUpdated(float newTempo);
    void setLoopStartPoint();
    void setLoopEndPoint();
    
    bool keyPressed (const KeyPress &key, Component *originatingComponent);
    
    
private:
    
    void updateTriggerFunction();
    
    
    //state data
    Atomic<int> recordState;
    Atomic<int> playState;
    Atomic<int> countInState;
    Atomic<int> mode1loopSet;
    Atomic<int> mode3waiting;
    Atomic<int> detectingBeat;
    Atomic<int> alternateLoopRec;
    //bool alternateLoopRecState;
    
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
    LooperGUI looperGUI;
    
    //metro
    Metronome metronome;
    
    int beatDetectorId;
    BeatDetector beatDetector;
    BeatDetectorB beatDetectorB;
};

#endif /* defined(__DrumLooper__Looper__) */
