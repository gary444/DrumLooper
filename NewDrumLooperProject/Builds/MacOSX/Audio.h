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
#include "SimpleTempoCalculator.h"
#include "PatchInfo.h"
#include "AudioSetupButton.h"


class Audio : public AudioIODeviceCallback,
                public Component,
                public TriggerResponse::Listener,
public ModeSelecter::Listener,
public ManualLoopControl::Listener,
public Looper::Listener,
public SimpleTempoCalculator::Listener,
//public MenuBarModel,
public Button::Listener
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
    
    
    //Button Listener
    void buttonClicked (Button* button);
    
    void audioDeviceAboutToStart (AudioIODevice* device);
    void audioDeviceStopped();
    
    //Trigger Response Callbacks
    void triggerReceived  (const int triggerType);
    void tempoDetected(float newTempo);
    
    //mode selecter callbacks
    void newModeSelected(int newModeIndex);
    
    //manual loop control callbacks (for mode 2)
    void tempoValueChanged(const float newTempo);
    void numberOfBeatsChanged(const int newNumberOfBeats);
    void countInChanged(const int newNumberOfBeats);
    void tapTempoChanged(const bool shouldTapTempo);
    void metroToggled(const bool shouldBeOn);
    void endLoopOnHitToggled(const bool shouldBeOn);
    
    //looper listener callback
    void looperReady(bool isReady);
    
    //tempo calculator callbacks
    
    //MenuBarEnums/Callbacks========================================================
//    enum Menus {
//		OptionMenu=0, NumMenus
//	};
//    
//    enum FileMenuItems
//	{
//        AudioPrefs = 1,
//		
//		NumFileItems
//	};
//    StringArray getMenuBarNames();
//    PopupMenu getMenuForIndex (int topLevelMenuIndex, const String& menuName);
//	void menuItemSelected (int menuItemID, int topLevelMenuIndex);
    
    void showAudioPreferences(Component* centerComponent);
    void patch();
    
private:
    
    AudioDeviceManager audioDeviceManager;
    PatchInfo patchInfo;
    //int sampleRate;
    
    //Components
    TriggerResponse triggerResponse;
    MasterControls masterControls;
    Looper looper;
    ModeSelecter modeSelecter;
    AudioSetupButton audioSetupButton;
    ManualLoopControl manualLoopControl;
    //Meter meter[2];
    
    
    int modeIndex;
    
    //for mode 2 tap tempo
    SimpleTempoCalculator tempoCalculator;
    Atomic<int> isUsingTapTempo;
    Atomic<int> tempoTapAboutToStartLooper;
    int sampleCountTarget;
    int sampleCount;
    
    // the command manager object used to dispatch command events
    ApplicationCommandManager commandManager;
};

#endif /* defined(__DrumLooper__Audio__) */
