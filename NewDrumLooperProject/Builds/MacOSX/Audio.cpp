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
    
    //audio
    audioDeviceManager.initialise(3, 2, 0, true, String::empty, 0);
    audioDeviceManager.addAudioCallback(this);
    
    //master
    masterControls = new MasterControls;
    addAndMakeVisible(masterControls);
    
    //trigger
    triggerResponse = new TriggerResponse;
    triggerResponse->setListener(this);
    addAndMakeVisible(triggerResponse);
    
    //mode selecter
    modeSelecter = new ModeSelecter;
    modeSelecter->addListener(this);
    addAndMakeVisible(modeSelecter);
    
    
    //meters
//    for (int i = 0; i < NUMBER_OF_METERS; i++) {
//        
//        meter[i].setMeterNumber(i + 1);
//        addAndMakeVisible(&meter[i]);
//    }
    
    //looper
    looper = new Looper;
    addAndMakeVisible(looper);
    
    
}
Audio::~Audio(){
    
    
    std::cout << "Audio dtor\n";
}

//ComponentCallbacks============================================================
void Audio::resized(){
    
    int x = getWidth();
    int y = getHeight();
    
    
    masterControls->setBounds(x - 50, y - 150, 50 , 150);
    triggerResponse->setBounds(x - 50, 0, 50, 50);
    looper->setBoundsRelative(0.0, 0.0, 0.8, 1.0);
    modeSelecter->setBoundsRelative(0.8, 0.1, 0.2, 0.5);
    
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
    
    
    const float *inL, *inR;
    float *outL, *outR;
    
    inL = inputChannelData[0];
    inR = inputChannelData[1];
    outL = outputChannelData[0];
    outR = outputChannelData[1];
    
    while(numSamples--)
    {
        float outputL, outputR = 0.f;
        
        //obtain values from pointers
        outputL = *inL;
        outputR = *inR;
        
//        //pass to meters
//        meter[0].process(outputL);
//        meter[1].process(outputR);
        
        //pass to looper
        outputL = looper->processSample(outputL, 0);
        outputR = looper->processSample(outputR, 1);
        
        //apply master control
        *outL = masterControls->processSample(outputL);
        *outR = masterControls->processSample(outputR);
    
        //increment pointers
        inL++;
        inR++;
        outL++;
        outR++;
    }
}

void Audio::audioDeviceAboutToStart (AudioIODevice* device){
    
}
void Audio::audioDeviceStopped(){
    
}
//Trigger Response Callbacks
void Audio::triggerReceived  (const int triggerType){
    
    //std::cout << "trigger recieved\n";
    
    //first mode
    if (modeIndex == 0) {
        looper->trigger();
    }
    
}

//mode selecter callbacks
void Audio::newModeSelected(int newModeIndex){
    
    std::cout << "new mode: " << newModeIndex + 1 << std::endl;
    
    modeIndex = newModeIndex;
    looper->setMode(newModeIndex);
}