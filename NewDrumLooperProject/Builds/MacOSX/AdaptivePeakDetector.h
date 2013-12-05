//
//  AdaptivePeakDetector.h
//  DrumLooper
//
//  Created by Gary Rendle on 27/11/2013.
//
//

#ifndef __DrumLooper__AdaptivePeakDetector__
#define __DrumLooper__AdaptivePeakDetector__

#include <iostream>
#include "PeakDetector.h"

//an adaptive peak detector changes its detection threshold in relation to the average local energy of the input signal over a given period of time. This then returns true or false for quick processing.

class AdaptivePeakDetector : public PeakDetector
{
    
    
public:
    AdaptivePeakDetector();
    ~AdaptivePeakDetector();
    
    bool process(const float input);
    
    void setDetectionFactor(const float newDetectionFactor);
    
    void reset();
    
private:
  
    float initialThreshold;
    bool isDetecting;
    
    int localAverageSampleCount;
    int localAverageSampleTarget;
    float localTotal;
    int averagesRequired;
    
    CriticalSection sharedMemory;
    float detectionFactor;
    
    Array<float> localAverages;
};

#endif /* defined(__DrumLooper__AdaptivePeakDetector__) */
