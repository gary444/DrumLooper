//
//  Audio.h
//  DrumLooper
//
//  Created by Gareth Rendle on 01/11/2013.
//
//

#ifndef __DrumLooper__Audio__
#define __DrumLooper__Audio__

#include "../JuceLibraryCode/JuceHeader.h"
#include "MasterControls.h"
#include "Looper.h"
#include "TriggerResponse.h"
#include "Meter.h"
#include "ModeSelecter.h"
#include "ManualLoopControl.h"

class Audio : public AudioIODeviceCallback,
                public Component,
                public TriggerResponse::Listener,
ModeSelecter::Listener,
ManualLoopControl::Listener
{
public:
    
    Audio();
    ~Audio();
    
    //ComponentCallbacks============================================================
	void resized();
	void paint (Graphics &g);
    
    //AudioCallbacks================================================================
    void audioDeviceIOCallback (const float** inputChannelData,
                                int numInputChannels,
                                float** outputChannelData,
                                int numOutputChannels,
                                int numSamples);
    
    void audioDeviceAboutToStart (AudioIODevice* device);
    void audioDeviceStopped();
    
    //Trigger Response Callbacks
    void triggerReceived  (const int triggerType);
    
    //mode selecter callbacks
    void newModeSelected(int newModeIndex);
    
    //manual loop control callbacks (for mode 2)
    void tempoValueChanged(const float newTempo);
    void numberOfBeatsChanged(const int newNumberOfBeats);
    void countInChanged(const int newNumberOfBeats);
    void tapTempoChanged(const bool shouldTapTempo);
    
private:
    AudioDeviceManager audioDeviceManager;
    
    //Components
    TriggerResponse triggerResponse;
    MasterControls masterControls;
    Looper looper;
    ModeSelecter modeSelecter;
    ManualLoopControl manualLoopControl;
    //Meter meter[2];
    
    int modeIndex;
};

#endif /* defined(__DrumLooper__Audio__) */
