//
//  PeakDetector.cpp
//  DrumLooper
//
//  Created by Gary Rendle on 27/11/2013.
//
//

#include "PeakDetector.h"

PeakDetector::PeakDetector(){
    
    triggerThreshold = 0.5;
    
    //default sample rate is 44.1kHz
    sampleRate = 44100;
    holdTime = 0.1;
    holdTimeInSamples = static_cast<int>(sampleRate * holdTime);
    isHolding = false;
    holdCounter = 0;
}
PeakDetector::~PeakDetector(){
    
}
void PeakDetector::setSampleRate(const int newSampleRate){
    
    sampleRate = newSampleRate;
    holdTimeInSamples = static_cast<int>(sampleRate * holdTime);
}