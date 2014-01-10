//
//  AdaptivePeakDetector.cpp
//  sdaFileEffect
//
//  Created by Gary Rendle on 13/12/2013.
//
//

#include "AdaptivePeakDetector.h"


AdaptivePeakDetector::AdaptivePeakDetector(){
    
    initialThreshold = 0.1;
    isDetecting = false;
    
    std::cout << "initial threshold = " << initialThreshold << "\n";
    
    float localAverageTimeInSeconds = 0.05;
    localAverageSampleCount = 0;
    localAverageSampleTarget = static_cast<int>(localAverageTimeInSeconds * sampleRate);
    localTotal = 0.f;
    
    float totalAverageTimeInSeconds = 2.f;
    
    averagesRequired = static_cast<int>(totalAverageTimeInSeconds / localAverageTimeInSeconds);
    
    holdTime = 0.4;
    std::cout << "Hold Time = " << holdTime << "\n";
    holdTimeInSamples = static_cast<int>(holdTime * sampleRate);
    
    detectionFactor = 6;
    std::cout << "detection factor = " << detectionFactor << "\n";
    
    localAverages.clear();
    
}
AdaptivePeakDetector::~AdaptivePeakDetector(){
    
}

bool AdaptivePeakDetector::process(float input){
    
    bool peakFound = false;
    
    //only start calculating if has started is above start threshold
    if (input > initialThreshold || isDetecting) {
        isDetecting = true;
        
        //LOCAL THRESHOLD CALCULATION=====================================
        //add input to local total
        localTotal += input;
        //increment counter
        localAverageSampleCount++;
        //if counter has reached target
        if (localAverageSampleCount >= localAverageSampleTarget) {
            
            //find local average and add to end of array
            float localAverage = localTotal / localAverageSampleTarget;
            localAverages.add(localAverage);
            
            //remove first element (if necessary)
            if (localAverages.size() >= averagesRequired) {
                localAverages.remove(0);
            }
            
            //find total average
            float totalAverage = 0.f;
            for (int i = 0; i < localAverages.size(); i++) {
                totalAverage += localAverages[i];
            }
            totalAverage = totalAverage / localAverages.size();
            
            //update threshold
            triggerThreshold = totalAverage * detectionFactor;
            
            //std::cout << "Threshold = " << triggerThreshold << "\n";
            
            //reset
            localAverageSampleCount = 0;
            localTotal = 0;
        }
        //LOCAL THRESHOLD CALCULATION END===================================
        
        if (isHolding) {
            holdCounter++;
            if (holdCounter >= holdTimeInSamples) {
                //reset
                holdCounter = 0;
                isHolding = false;
            }
        }
        else {
            if (input > triggerThreshold) {
                peakFound = true;
                isHolding = true;
            }
        }
    }
    
    return peakFound;
}


void AdaptivePeakDetector::setDetectionFactor(const float newDetectionFactor){
    
    sharedMemory.enter();
    detectionFactor = newDetectionFactor;
    sharedMemory.exit();
    
}

void AdaptivePeakDetector::reset(){
    
    sharedMemory.enter();
    isDetecting = false;
    localAverages.clear();
    sharedMemory.exit();
}