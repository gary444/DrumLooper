//
//  DetectionState.h
//  sdaFileEffect
//
//  Created by Gary Rendle on 04/12/2013.
//
//

#ifndef __sdaFileEffect__DetectionState__
#define __sdaFileEffect__DetectionState__

#include <iostream>
#include "../JuceLibraryCode/JuceHeader.h"

class DetectionState {
    
public:
    
    DetectionState();
    ~DetectionState();
    
    void setNoteValue(const float newNoteValue);
    
    float getNoteValue();
    
    void setInterval(const int newInterval);
    
    int getInterval();
    
    void testInterval(const int newTestInterval);
    
    int getConfidence();
    
private:
    
    //functions
    void fillArray();
    
    //members
    float noteValue;
    int rootInterval;
    float errorAllowancePercentage;
    int confidence;
    float beatsSoFar;
    int samplesSoFar;
    //int sampleError;
    
    Array<int> expectedIntervalTimes;
    Array<float> testedNoteValues;
};

#endif /* defined(__sdaFileEffect__DetectionState__) */
