//
//  SimpleTempoCalculator.cpp
//  DrumLooper
//
//  Created by Gareth Rendle on 15/11/2013.
//
//

#include "SimpleTempoCalculator.h"

SimpleTempoCalculator::SimpleTempoCalculator(){
    
    //default sample rate 44k1
    sampleRate = 44100;
    listener = nullptr;
    sampleCount = 0;
    countInBeats = 4;
    beatCount = 0;
    firstHitSampleTime = lastHitSampleTime = 0;
    
    float indicatorTime = 0.1;
    indicatorCounter = 0;
    indicatorTarget = static_cast<int>(44100 * indicatorTime);
    indicating = false;
    
    tapIndicator.setColour(TextButton::buttonColourId, Colours::grey);
    tapIndicator.setColour(TextButton::buttonOnColourId, Colours::lightgreen);
    addAndMakeVisible(&tapIndicator);
    
    tapLabel.setText("Tap", dontSendNotification);
    tapLabel.setJustificationType(Justification::left);
    addAndMakeVisible(&tapLabel);
    
    
    
    
}
SimpleTempoCalculator::~SimpleTempoCalculator(){
    
}

void SimpleTempoCalculator::resized(){
    
    tapIndicator.setBounds(0, 20, 10, 10);
    tapLabel.setBounds(10, 17, 70, 20);
}

void SimpleTempoCalculator::process(float input){
    
    //if detector returns 'true' it has detected a peak
    if (peakDetector.detect(input) == true) {
        
        std::cout << "Calc received\n";
        //listener->peakDetected();
        setIndicateState(true);
        
        
        //increment number of beats that have been detected
        beatCount++;
        
        //if first hit, record sample time
        if (beatCount == 1) {
            //firstHitSampleTime = sampleCount;
            sampleCount = 0;
        }
        //if last required hit...
        else if (beatCount == countInBeats){
            
            //record sample time
            lastHitSampleTime = sampleCount;
            
            //calculate tempo....
            // get average number of samples per beat
            float samplesPerBeat = (lastHitSampleTime) / (countInBeats - 1);
            
            //tempo in bpm = number of samples in 1 min divided by num samples in one beat
            float tempo = (sampleRate * 60) / samplesPerBeat;
            
            //notify
            
            if (listener != nullptr) {
                listener->tempoDetected(tempo);
            }
            std::cout << "new tempo = " << tempo << "\n";
            
            //reset
            beatCount = 0;
            sampleCount = 0;
        }
    
    }
    
    if (indicating) {
        indicatorCounter++;
        if (indicatorCounter >= indicatorTarget) {
            setIndicateState(false);
        }
    }
    
    //increment counter
    sampleCount++;
}
void SimpleTempoCalculator::setSampleRate(int newSampleRate){
    
    sampleRate = newSampleRate;
}

void SimpleTempoCalculator::setListener(Listener* newListener){
    
    listener = newListener;
}

void SimpleTempoCalculator::setCountInBeats(int newNumberOfBeats){
    
    countInBeats = newNumberOfBeats;
}
void SimpleTempoCalculator::setIndicateState(bool state){
    
    MessageManagerLock mml (Thread::getCurrentThread());
    if (! mml.lockWasGained())
        return;
    
    tapIndicator.setToggleState(state, dontSendNotification);
    indicating = state;
}