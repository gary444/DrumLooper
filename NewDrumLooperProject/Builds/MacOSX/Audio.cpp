//
//  Audio.cpp
//  DrumLooper
//
//  Created by Gareth Rendle on 01/11/2013.
//
//


#include "Audio.h"

#define NUMBER_OF_METERS 2

Audio::Audio()
{
    modeIndex = 0;
    isUsingTapTempo = false;
    sampleRate = 44100;
    sampleCount = 0;
    sampleCountTarget = 0;
    tempoTapAboutToStartLooper = false;
    
    //master
    addAndMakeVisible(&masterControls);
    
    //trigger
    triggerResponse.setListener(this);
    addAndMakeVisible(&triggerResponse);
    
    //mode selecter
    modeSelecter.addListener(this);
    addAndMakeVisible(&modeSelecter);
    
    //manual Loop control
    manualLoopControl.addListener(this);
    addAndMakeVisible(&manualLoopControl);
    
    //meters
//    for (int i = 0; i < NUMBER_OF_METERS; i++) {
//        
//        meter[i].setMeterNumber(i + 1);
//        addAndMakeVisible(&meter[i]);
//    }
    
    //looper
    addAndMakeVisible(&looper);
    looper.setListener(this);
    
    //tempo calc
    tempoCalculator.setListener(this);
    
    //audio
    audioDeviceManager.initialise(3, 2, 0, true, String::empty, 0);
    patch();
    audioDeviceManager.addAudioCallback(this);
    
    
}
Audio::~Audio(){
    
    audioDeviceManager.removeAudioCallback(this);
    
    //std::cout << "Audio dtor\n";
}



//ComponentCallbacks============================================================
void Audio::resized(){
    
    int x = getWidth();
    int y = getHeight();
    
    
    masterControls.setBounds(x - 50, y - 150, 50 , 150);
    triggerResponse.setBounds(x - 50, 0, 50, 50);
    looper.setBoundsRelative(0.0, 0.0, 0.75, 1.0);
    modeSelecter.setBoundsRelative(0.75, 0.1, 0.25, 0.35);
    manualLoopControl.setBoundsRelative(0.75, 0.46, 0.25, 0.28);
    
    //meters
//    for (int i = 0; i < NUMBER_OF_METERS; i++) {
//        meter[i].setBounds(x - 110, 100 + (i * 20), 110, 20);
//    }
}
void Audio::paint (Graphics &g){
    
}

//AudioCallbacks================================================================
void Audio::audioDeviceIOCallback (const float** inputChannelData,
                            int numInputChannels,
                            float** outputChannelData,
                            int numOutputChannels,
                                   int numSamples)
{
    
    
    const float *inL, *inR, *inTrigger;
    float *outL, *outR;
    
    inL = inputChannelData[patchInfo.getlooperInput1Index()];
    inR = inputChannelData[patchInfo.getlooperInput2Index()];
    inTrigger = inputChannelData[patchInfo.getTriggerInputIndex()];
    
    outL = outputChannelData[0];
    outR = outputChannelData[1];
    
    while(numSamples--)
    {
        float outputL, outputR, trigger = 0.f;
        
        //check inputs are not null
        if (inL != nullptr && inR != nullptr && inTrigger != nullptr ) {
            
            //obtain values from pointers
            outputL = *inL;
            outputR = *inR;
            trigger = *inTrigger;
            
            
            //limiting....shouldn't be needed!?======================
            if (outputL > 1)
                outputL = 1;
            else if (outputL < -1)
                outputL = -1;
            if (outputR > 1)
                outputR = 1;
            else if (outputR < -1)
                outputR = -1;
            if (trigger > 1)
                trigger = 1;
            else if (trigger < -1)
                trigger = -1;
            //end of limiting============================================
            if (outputL > 1 || outputL < -1) {
                std::cout << "audio sample out of range (" << outputL << ")\n";
            }
            
            //        //pass to meters
            //        meter[0].process(outputL);
            //        meter[1].process(outputR);
            
            
            
            //for tempo calculation - pass trigger to tempoCalculator object
            if (isUsingTapTempo.get()) {
                tempoCalculator.process(trigger);
            }
            else {
                //otherwise pass trigger to normal trigger response class
                triggerResponse.processInput(trigger);
            }
            
            
            //for mode2 tap tempo
            if (tempoTapAboutToStartLooper.get()) {
                sampleCount++;
                //if count has reached end...
                if (sampleCount == sampleCountTarget) {
                    //and looper is set to record...
                    if (looper.getRecordState() == true) {
                        //start looper
                        looper.setPlayState(true);
                        
                        //reset
                        tempoTapAboutToStartLooper.set(false);
                        sampleCountTarget = sampleCount = 0;
                        isUsingTapTempo = false;
                        
                        MessageManagerLock mml (Thread::getCurrentThread());
                        if (! mml.lockWasGained())
                            return;
                        
                        manualLoopControl.setTapTempo(false);
                    }
                }
            }
            
            
            //pass to looper
            outputL = looper.processSample(outputL, 0);
            outputR = looper.processSample(outputR, 1);
            
            //apply master control
            *outL = masterControls.processSample(outputL);
            *outR = masterControls.processSample(outputR);
            
            //increment pointers
            inL++;
            inR++;
            outL++;
            outR++;
        }
    }
}

void Audio::audioDeviceAboutToStart (AudioIODevice* device){
    
}
void Audio::audioDeviceStopped(){
    
}
//Trigger Response Callbacks
void Audio::triggerReceived(const int triggerType){
    
    //std::cout << "trigger recieved\n";
    
    //first mode
    if (modeIndex == 0) {
        looper.trigger();
    }
    else if(modeIndex == 1){
        
        looper.trigger();
    }
    
}
void Audio::tempoDetected(float newTempo){
    
    looper.tempoValueChanged(newTempo);
    
    sampleCount = 0;
    sampleCountTarget = (sampleRate * 60) / newTempo;
    tempoTapAboutToStartLooper.set(true);
    
    //lock before updating slider
    MessageManagerLock mml (Thread::getCurrentThread());
    if (! mml.lockWasGained())
        return;
    manualLoopControl.setTempoValue(newTempo);
}

//mode selecter callbacks
void Audio::newModeSelected(int newModeIndex){
    
    
    modeIndex = newModeIndex;
    looper.setMode(newModeIndex);
    manualLoopControl.setModeIndex(newModeIndex);
}

//manual loop control callbacks (for mode 2)
void Audio::tempoValueChanged(const float newTempo){
    
    if (modeIndex == 1) {
        looper.tempoValueChanged(newTempo);
    }
    
}
void Audio::numberOfBeatsChanged(const int newNumberOfBeats)
{
    if (modeIndex == 1) {
        looper.numberOfBeatsChanged(newNumberOfBeats);
    }

}

void Audio::countInChanged(const int newNumberOfBeats){
    
    looper.countInChanged(newNumberOfBeats);
    tempoCalculator.setCountInBeats(newNumberOfBeats);
    //triggerResponse.setTapTempoCountInBeats(newNumberOfBeats);
}
void Audio::tapTempoChanged(const bool shouldTapTempo){
    
    isUsingTapTempo.set(shouldTapTempo);
    
    //triggerResponse.useTempoCalculator(shouldTapTempo);
    
}
void Audio::metroToggled(const bool shouldBeOn){
 
    looper.metroToggled(shouldBeOn);
}

//looper listener callback
void  Audio::looperReady(bool isReady){
    
    
    modeSelecter.setEnabled(isReady);
    manualLoopControl.setEnabled(isReady);
}

//tempo calculator callbacks


StringArray Audio::getMenuBarNames()
{
	const char* const names[] = { "Options", 0 };
	return StringArray (names);
}

PopupMenu Audio::getMenuForIndex (int topLevelMenuIndex, const String& menuName)
{
	PopupMenu menu;
	if (topLevelMenuIndex == 0)
        menu.addItem(AudioPrefs, "Audio Preferences", true, false);
	return menu;
}

void Audio::menuItemSelected (int menuItemID, int topLevelMenuIndex)
{
	if (topLevelMenuIndex == OptionMenu)
    {
        if (menuItemID == AudioPrefs)
        {
            showAudioPreferences(this);
        }
        
    }
}
void Audio::showAudioPreferences(Component* centerComponent)
{
    AudioDeviceSelectorComponent audioSettingsComp (audioDeviceManager,
                                                    2, 3, 2, 2,
                                                    false, false, false, true);
    audioSettingsComp.setSize (500, 300);
    DialogWindow::showModalDialog ("Drum Looper Audio Setup...Close to Start App!", &audioSettingsComp, centerComponent, Colours::azure, true, true);
    
    patch();
    
}

void Audio::patch(){
    
    int ins, outs = 0;
    AudioIODevice* iODevice = audioDeviceManager.getCurrentAudioDevice();
    StringArray sA = iODevice->getInputChannelNames();
    ins = sA.size();
    sA.clear();
    sA = iODevice->getOutputChannelNames();
    outs = sA.size();
    patchInfo.setNumberOfInputChannels(ins);
    patchInfo.setNumberOfOutputChannels(outs);
    std::cout << "DrumLooper is using " << iODevice->getName() << " as audio device\n"
    << "Inputs: " << ins << "\nOutputs: " << outs << "\n";
}