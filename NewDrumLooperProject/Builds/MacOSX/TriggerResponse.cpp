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
    //sampleRate = 44100;
    holdTime = 0.1;
    holdTimeInSamples = static_cast<int>(sampleRate * holdTime);
    //holdCounter = 0;
    
    //triggerThreshold = 0.5;
    //noiseThreshold = 0.05;
    listener = nullptr;
    
    //indicatorCount = 0;
    //indicatorCounting = false;
    
    //tempoCalculator.setListener(this);
    
    //isUsingTapTempo.set(false);
    
    thresholdSlider.setValue(1.0 - triggerThreshold);
    thresholdSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    thresholdSlider.setRange(0.f, 0.95, 0.01);
    thresholdSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    thresholdSlider.addListener(this);
    thresholdSlider.setColour(Slider::rotarySliderFillColourId, Colours::deepskyblue);
    thresholdSlider.setColour(Slider::rotarySliderOutlineColourId, Colours::grey);
    thresholdSlider.setTooltip("Adjust sensitivity of trigger pad");
    addAndMakeVisible(&thresholdSlider);
    
    sensitivityLabel.setText("Sensitivity", dontSendNotification);
    sensitivityLabel.setJustificationType(Justification::centred);
    sensitivityLabel.setColour(Label::textColourId, Colours::lightgrey);
    //sensitivityLabel.setEditable(false);
    addAndMakeVisible(&sensitivityLabel);
    
    indicatorButton.addListener(this);
    //indicatorButton.setButtonText("T");
    indicatorButton.setColour(TextButton::buttonColourId, Colours::grey);
    indicatorButton.setColour(TextButton::buttonOnColourId, Colours::red);
    addAndMakeVisible(&indicatorButton);
    
    triggerLabel.setText("Trigger", dontSendNotification);
    triggerLabel.setJustificationType(Justification::left);
    triggerLabel.setColour(Label::textColourId, Colours::lightgrey);
    //triggerLabel.setEditable(false);
    addAndMakeVisible(&triggerLabel);
}
TriggerResponse::~TriggerResponse(){
    
    
    //std::cout << "trigger response dtor\n";
}

void TriggerResponse::resized(){
    
    indicatorButton.setBounds(75, 5, 10, 10);
    thresholdSlider.setBounds(30, 0, 40, 40);
    sensitivityLabel.setBounds(0, 41, 100, 15);
    triggerLabel.setBounds(85, 2, 70, 15);
}

void TriggerResponse::buttonClicked(Button* button){
    
    if (button == &indicatorButton)
    {
        listener->triggerReceived(1);
    }
    
}


//slider callback
void TriggerResponse::sliderValueChanged (Slider* slider){
    
    sharedMemory.enter();
    triggerThreshold = 1.0 - slider->getValue();
    sharedMemory.exit();
    
}

//void TriggerResponse::tempoDetected(const float newTempo){
//    
//    listener->tempoDetected(newTempo);
//    isUsingTapTempo.set(false);
//    
//}


//void TriggerResponse::peakDetected(){
//    
//    setIndicatorState(true);
//    indicatorCount = 0;
//    indicatorCounting = true;
//}


void TriggerResponse::setListener(Listener* newListener){
    
    listener = newListener;
}

//void TriggerResponse::setSampleRate(const int newSampleRate){
//    
//    sampleRate = newSampleRate;
//    holdTimeInSamples = static_cast<int>(sampleRate * holdTime);
//}

void TriggerResponse::processInput(float input){
    
//    if (isUsingTapTempo.get()) {
//        tempoCalculator.process(input);
//        
//    }
    //if not holding...
    if (!isHolding) {
        
        //obtain absolute value of input
        input = fabsf(input);
        
        //double input to increase sensitivity
        input = input * 2.0;
        
        //compare to threshold value
        if (input > triggerThreshold) {
            
            //alert listener if trigger is detected
            if (listener != nullptr) {
                listener->triggerReceived(1);
            }
            std::cout << "Trigger Detected\n";
            
            //start holding
            isHolding = true;
            setIndicatorState(true);
        }
        
    }
    //if holding, increment 'hold' counter
    else {
        holdCounter++;
        
        //if hold counter has reached hold length, stop holding and reset counter
        if (holdCounter >= holdTimeInSamples) {
            isHolding = false;
            holdCounter = 0;
            setIndicatorState(false);
        }
    }
    
//    if (indicatorCounting == true) {
//        indicatorCount++;
//        if (indicatorCount >= holdTimeInSamples) {
//            setIndicatorState(false);
//        }
//    }
    
    
}


//void TriggerResponse::useTempoCalculator(bool shouldUseTempoCalculator){
//    
//    isUsingTapTempo.set(shouldUseTempoCalculator);
//}


//void TriggerResponse::setTapTempoCountInBeats(int newNumberOfBeats){
//    
//    tempoCalculator.setCountInBeats(newNumberOfBeats);
//}

void TriggerResponse::setIndicatorState(bool shouldBeOn){
    
    MessageManagerLock mml (Thread::getCurrentThread());
    if (! mml.lockWasGained())
        return;
    
    indicatorButton.setToggleState(shouldBeOn, dontSendNotification);
}

