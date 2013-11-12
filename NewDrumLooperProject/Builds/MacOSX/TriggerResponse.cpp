//
//  TriggerResponse.cpp
//  DrumLooper
//
//  Created by Gareth Rendle on 01/11/2013.
//
//

#include "TriggerResponse.h"

TriggerResponse::TriggerResponse(){
    
    //default sample rate is 44.1kHz
    sampleRate = 44100;
    holdTime = 0.1;
    holdTimeInSamples = static_cast<int>(sampleRate * holdTime);
    
    triggerThreshold = 0.5;
    noiseThreshold = 0.05;
    
    testButton.addListener(this);
    testButton.setButtonText("Trigger");
    addAndMakeVisible(&testButton);
}
TriggerResponse::~TriggerResponse(){
    
    
    //std::cout << "trigger response dtor\n";
}

void TriggerResponse::resized(){
    
    testButton.setBounds(0, 0, 50, 30);
}

//test button
void TriggerResponse::buttonClicked(Button* button){
    
    if (button == &testButton)
    {
        listener->triggerReceived(1);
    }
    
}



void TriggerResponse::setListener(Listener* newListener){
    
    listener = newListener;
}

void TriggerResponse::setSampleRate(const int newSampleRate){
    
    sampleRate = newSampleRate;
    holdTimeInSamples = static_cast<int>(sampleRate * holdTime);
}

void TriggerResponse::processInput(float input){
    
    //obtain absolute value of input
    input = fabsf(input);
    
    //if input is above noise threshold
    if (input > noiseThreshold) {
        
        //compare to threshold value
        if (input > triggerThreshold) {
            
            //alert listener if trigger is detected
            listener->triggerReceived(1);
            //start holding
            isHolding = true;
        }
    }
    
    //if holding, increment 'hold' counter
    if (isHolding == true) {
        holdCounter++;
    }
    
    //if hold counter has reached hold length, stop holding and reset counter
    if (holdCounter == holdTimeInSamples) {
        isHolding = false;
        holdCounter = 0;
    }
}