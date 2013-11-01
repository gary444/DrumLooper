//
//  TriggerResponse.h
//  DrumLooper
//
//  Created by Gareth Rendle on 01/11/2013.
//
//

#ifndef __DrumLooper__TriggerResponse__
#define __DrumLooper__TriggerResponse__

#include <iostream>
#include "../JuceLibraryCode/JuceHeader.h"


class TriggerResponse : public Component,
public Button::Listener
{
public:
    
    //add listener for trigger response class
    class Listener
    {
    public:
        /**
         Destructor
         */
        virtual ~Listener() {}
        
        /**
         Called when trigger recieved. */
        virtual void triggerReceived  (const int triggerType) = 0;
    };
    
    
    TriggerResponse();
    ~TriggerResponse();
    
    //ComponentCallbacks============================================================
	void resized();
    
    //Button Listener
    void buttonClicked (Button* button);
    
    //set listener
    void setListener(Listener* newListener);
    
    //set sample rate in order to calculate correct hold time
    void setSampleRate(const int newSampleRate);
    
    void processInput(float input);
    
private:
    
    TextButton testButton;
    
    Listener* listener;
    
    float threshold;
    float noiseThreshold;
    int sampleRate;
    float holdTime;
    int holdTimeInSamples;
    bool isHolding;
    int holdCounter;
    
};

#endif /* defined(__DrumLooper__TriggerResponse__) */
