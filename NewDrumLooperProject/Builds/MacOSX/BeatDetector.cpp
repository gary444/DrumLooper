//
//  BeatDetector.cpp
//  DrumLooper
//
//  Created by Gary Rendle on 24/11/2013.
//
//

#include "BeatDetector.h"


BeatDetector::BeatDetector(){
    
    //inits
    noOfBeats = 8;
    waitingForFirstHit = true;
    tempoLowerLimit = 60.f;
    tempoUpperLimit = 180.f;
    tempLChannelData = 0.f;
    
    intervalCount = 0;
    intervalCounting = false;
    
    highestInputValue = 0.f;
    hitCount = 0;
    
    listener = nullptr;
    
    agent1.clear();
    
    //fill tested note value array
    testedNoteValues.clear();
    testedNoteValues.add(0.25);
    testedNoteValues.add(0.5);
    testedNoteValues.add(0.75);
    testedNoteValues.add(1.0);
    testedNoteValues.add(1.25);
    testedNoteValues.add(1.5);
    testedNoteValues.add(1.75);
}

BeatDetector::~BeatDetector(){
    
    
}


void BeatDetector::setListener(Listener* newListener){
    
    listener = newListener;
}

void BeatDetector::setNumberOfBeats(int newNumberOfBeats){
    
    noOfBeats = newNumberOfBeats;
}


void BeatDetector::process(float input, int channel){
    
    //increment counter if necessary
    if (intervalCounting)
        intervalCount++;
    
    
    
    //create mono input from pairs of input samples with
    // different channel numbers
    float monoInput;
    if (channel == 0) {
        tempLChannelData = fabsf(input);
    }
    else
    {
        monoInput = (tempLChannelData + fabsf(input)) * 0.5;
        tempLChannelData = 0.f;
    }
    
    //only process if recieving non-zero values
    if (monoInput > 0.f) {
        
        //check if highest input value
        if (monoInput > highestInputValue){
            highestInputValue = monoInput;
            
            if (hitCount > 5) {
                std::cout << "highest input value = " << highestInputValue << "\n";
            }
        }
        
        
        
        //if peak is detected
        if (peakDetector.process(monoInput) == true) {
            
            //if testing
            if (showingHits.get())
                std::cout << "hit heard : " << hitCount << "\n";
            
            hitCount++;
            
            //call process peak function (after hit count is updated!)
            processPeak();
            
            //start loop if first hit
            if (waitingForFirstHit.get() == true) {
                waitingForFirstHit = false;
            }
            if (listener != nullptr) {
                //listener->startloop();//
            }
        }
    }
    
    
    
}

void BeatDetector::reset(){
    
    peakDetector.reset();
}

void BeatDetector::showHits(bool should){
    
    showingHits.set(should);
}

void BeatDetector::processPeak(){
    
    //if first peak, detector will not be counting
    if (intervalCounting == false) {
        //start counting
        intervalCounting = true;
    }
    //otherwise process the peak as normal
    else {
        
        //if this is the second hit
        if (hitCount == 2) {
            
            //fill agent 1 with states
            for (int i = 0; i < testedNoteValues.size(); i++) {
                
                //create state
                DetectionState* newState = new DetectionState;
                //add interval and note values
                newState->setInterval(intervalCount);
                newState->setNoteValue(testedNoteValues[i]);
                
                
                agent1.add(newState);
                
            }
        }
        else if (hitCount > 2){
            
            for (int i = 0; i < agent1.size(); i++) {
                agent1[i]->testInterval(intervalCount);
            }
        }
        
        //reset interval number
        intervalCount = 0;
    }
}

void BeatDetector::printConfidences(){
    
    //String confidences;
    std::cout << "Confidences:\n";
    
    for (int i = 0; i < agent1.size(); i++) {
        std::cout << "For note value: " << testedNoteValues[i] << ", confidence = " << agent1[i]->getConfidence() << "\n";
    }
    
    //std::cout << confidences;
    
}