//
//  SimplePeakDetector.cpp
//  DrumLooper
//
//  Created by Gareth Rendle on 18/11/2013.
//
//

#include "SimplePeakDetector.h"

SimplePeakDetector::SimplePeakDetector(){
    
    //default sample rate is 44.1kHz
    //sampleRate = 44100;
    holdTime = 0.1;
    holdTimeInSamples = static_cast<int>(sampleRate * holdTime);
    //isHolding = false;
    
    triggerThreshold = 0.2;
    //noiseThreshold = 0.001;
    
    
}
SimplePeakDetector::~SimplePeakDetector(){
    
}

bool SimplePeakDetector::detect(float input){
    
    bool peakFound = false;
    
    //if the detector is not holding
    if (!isHolding) {
        
        //obtain absolute value of input
        input = fabsf(input);
        
        //double input to increase sensitivity
        input = input * 2.0;
        
        //compare to threshold value
        if (input > triggerThreshold) {
                
                //std::cout << "peak at = " << input << "\n";
                
            peakFound = true;
                
            //start holding
            isHolding = true;
        }
    }
    else {
        
        holdCounter++;
        //if hold counter has reached hold length, stop holding and reset counter
        if (holdCounter >= holdTimeInSamples) {
            isHolding = false;
            holdCounter = 0;
        }
    }
    
    return peakFound;
}