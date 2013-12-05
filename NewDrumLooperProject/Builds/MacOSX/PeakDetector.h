//
//  PeakDetector.h
//  DrumLooper
//
//  Created by Gary Rendle on 27/11/2013.
//
//

#ifndef __DrumLooper__PeakDetector__
#define __DrumLooper__PeakDetector__

#include <iostream>
#include "../JuceLibraryCode/JuceHeader.h"

class PeakDetector {
    
public:
    
    PeakDetector();
    virtual ~PeakDetector();
    
    //set sample rate in order to calculate correct hold time
    void setSampleRate(const int newSampleRate);
    
protected:
    
    float triggerThreshold;
    int sampleRate;
    float holdTime;
    int holdTimeInSamples;
    bool isHolding;
    int holdCounter;
    
};

#endif /* defined(__DrumLooper__PeakDetector__) */
