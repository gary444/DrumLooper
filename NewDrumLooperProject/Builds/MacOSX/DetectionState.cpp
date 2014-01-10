//
//  DetectionState.cpp
//  sdaFileEffect
//
//  Created by Gary Rendle on 04/12/2013.
//
//

#include "DetectionState.h"

DetectionState::DetectionState(){
    
    //inits
    noteValue = 0.0;
    rootInterval = 0;
    beatsSoFar = 0.f;
    samplesSoFar = 0;
    confidence = 0;
    
    errorAllowancePercentage = 4.f;
    //std::cout << "Error allowance = " << errorAllowancePercentage << "\n";
    
    
    
    
    expectedIntervalTimes.clear();
    
    
    //fill tested note value array
    testedNoteValues.clear();
    //testedNoteValues.add(1.0 / 6.0);
    //testedNoteValues.add(0.25);
    //testedNoteValues.add(1.0 / 3.0);
    //testedNoteValues.add(0.5);
    //testedNoteValues.add(2.0 / 3.0);
    //testedNoteValues.add(0.75);
    //testedNoteValues.add(5.0 / 6.0);
    testedNoteValues.add(1.0);
    //testedNoteValues.add(7.0 / 6.0);
    //testedNoteValues.add(1.25);
    //testedNoteValues.add(4.0 / 3.0);
    //testedNoteValues.add(1.5);
    //testedNoteValues.add(5.0 / 3.0);
    //testedNoteValues.add(1.75);
    //testedNoteValues.add(11.0 / 6.0);
    //testedNoteValues.add(2.0);
    //testedNoteValues.add(2.5);
    //testedNoteValues.add(3.0);
    
    
}

DetectionState::~DetectionState(){
    
}

void DetectionState::setNoteValue(const float newNoteValue){
    
    noteValue = newNoteValue;
    
    //fill array if enough information is known and array is not already filled
    if (rootInterval != 0 && expectedIntervalTimes.size() == 0) {
        fillArray();
    }
    
    //add value of first beat to beat tally
    beatsSoFar += newNoteValue;
}

float DetectionState::getNoteValue(){
    
    return noteValue;
}

void DetectionState::setInterval(const int newInterval){
    
    rootInterval = newInterval;
    
    //fill array if enough information is known and array is not already filled
    if (noteValue != 0 && expectedIntervalTimes.size() == 0) {
        fillArray();
    }
    
    samplesSoFar += newInterval;
}


int DetectionState::getInterval(){
    
    return rootInterval;
}

void DetectionState::testInterval(const int newTestInterval){
    
    for (int i = 0; i < expectedIntervalTimes.size(); i++) {
        
        // calculate permissible error
        int sampleError = static_cast<int>((rootInterval * noteValue) * (errorAllowancePercentage / 100.0));
        
        //calculate difference between expected and input
        //negative difference means beat is later than expected
        int sampleDifference = expectedIntervalTimes[i] - newTestInterval;
        
        //if difference is within allowable error, process
        if (abs(sampleDifference) <= sampleError) {
            
            confidence++;

            //add relevant note value to beat tally
            beatsSoFar += testedNoteValues[i];
            samplesSoFar += newTestInterval;
            
            //adjust interval accordingly to average
            //in future - use sampleDifference and confidence to
            rootInterval = (samplesSoFar / beatsSoFar) * noteValue;
            
            //update array
            fillArray();
            
        }
        
    }
}

int DetectionState::getConfidence(){
    
    return confidence;
}

void DetectionState::fillArray(){
    
    //clear first
    expectedIntervalTimes.clear();
    
    //for each note value that we are testing for, find an equivalent number of samples
    for (int i = 0; i < testedNoteValues.size(); i++) {
    
        //each note value tested for could be expressed as a ratio of the root interval
        float noteRatio = testedNoteValues[i] / noteValue;
        float noteInterval = rootInterval * noteRatio;
        
        //add to array
        expectedIntervalTimes.add(static_cast<int>(noteInterval));
        
    }
    
    //std::cout << "Array filled\n";
}

