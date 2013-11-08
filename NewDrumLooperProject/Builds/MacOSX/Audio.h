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

class Audio : public AudioIODeviceCallback,
                public Component,
                public TriggerResponse::Listener,
ModeSelecter::Listener
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
    
private:
    AudioDeviceManager audioDeviceManager;
    
    //Components
    ScopedPointer<TriggerResponse> triggerResponse;
    ScopedPointer<MasterControls> masterControls;
    ScopedPointer<Looper> looper;
    ScopedPointer<ModeSelecter> modeSelecter;
    //Meter meter[2];
    
    int modeIndex;
};

#endif /* defined(__DrumLooper__Audio__) */
