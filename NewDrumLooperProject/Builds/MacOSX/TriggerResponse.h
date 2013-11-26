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
//#include "SimpleTempoCalculator.h"

class TriggerResponse : public Component,
public Button::Listener,
public Slider::Listener//,
//public SimpleTempoCalculator::Listener
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
        
        //virtual void tempoDetected(const float newTempo) = 0;
    };
    
    
    TriggerResponse();
    ~TriggerResponse();
    
    //ComponentCallbacks============================================================
	void resized();
    
    //Button Listener
    void buttonClicked (Button* button);
    
    //slider callback
    void sliderValueChanged (Slider* slider);
    
    //tempo calculator callbacks
    //void tempoDetected(const float newTempo);
    //void peakDetected();
    
    //set listener
    void setListener(Listener* newListener);
    
    //set sample rate in order to calculate correct hold time
    void setSampleRate(const int newSampleRate);
    
    void processInput(float input);
    
    //void useTempoCalculator(bool shouldUseTempoCalculator);
    
    //void setTapTempoCountInBeats(int newNumberOfBeats);
    
    void setIndicatorState(bool shouldBeOn);
    //void indicate();
    
    
protected:
    
    
    
    TextButton indicatorButton;
    Slider thresholdSlider;
    Label sensitivityLabel;
    
    CriticalSection sharedMemory;
    
    //SimpleTempoCalculator tempoCalculator;
    
    Listener* listener;
    
    float triggerThreshold;
    //float noiseThreshold;
    int sampleRate;
    float holdTime;
    int holdTimeInSamples;
    bool isHolding;
    int holdCounter;
    //int indicatorCount;
    //bool indicatorCounting;
    
    //Atomic<int> isUsingTapTempo;
};

#endif /* defined(__DrumLooper__TriggerResponse__) */
