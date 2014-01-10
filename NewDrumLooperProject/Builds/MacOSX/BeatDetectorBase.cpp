//
//  BeatDetectorBase.cpp
//  sdaFileEffect
//
//  Created by Gary Rendle on 28/12/2013.
//
//

#include "BeatDetectorBase.h"

BeatDetectorBase::BeatDetectorBase(){
    
    //inits
    noOfBeats = 8;
    sampleRate = 44100;
    waitingForFirstHit = true;
    tempoLowerLimit = 60.f;
    tempoUpperLimit = 180.f;
    tempLChannelData = 0.f;
    
    intervalCount = 0;
    interval2Count = 0;
    interval3Count = 0;
    intervalCounting = false;
    interval2Counting = false;
    interval3Counting = false;
    endLoopOnHit = true;
    waitingForLastHit = false;
    
    highestInputValue = 0.f;
    hitCount = 0;
    sampleNumber = 0;
    
}

BeatDetectorBase::~BeatDetectorBase(){
    
}

void BeatDetectorBase::setNumberOfBeats(int newNumberOfBeats){
    
    noOfBeats = newNumberOfBeats;
    
}


void BeatDetectorBase::process(float input, int channel){
    

}

void BeatDetectorBase::reset(){
    
    peakDetector.reset();
    
    hitCount = 0;
    intervalCount = 0;
    interval2Count = 0;
    interval3Count = 0;
    intervalCounting = false;
    interval2Counting = false;
    interval3Counting = false;
    waitingForFirstHit = true;
    waitingForLastHit = false;
    sampleNumber = 0;
}

void BeatDetectorBase::showHits(bool should){
    
    showingHits.set(should);
}


void BeatDetectorBase::processPeak(){
    
    
}

void BeatDetectorBase::reportMostLikelyTempo(){
    
}

float BeatDetectorBase::putTempoInRange(float tempoToCheck){
    
    //std::cout << "Put tempo in range called\n";
    
    float upperLimit = 180.0;
    float lowerLimit = 60.0;
    
    while (tempoToCheck > upperLimit) {
        tempoToCheck = tempoToCheck / 2.0;
    }
    
    while (tempoToCheck < lowerLimit) {
        tempoToCheck = tempoToCheck * 2.0;
    }
    
    return tempoToCheck;
}


void BeatDetectorBase::setEndLoopOnHit(bool shouldBeOn){
    
    endLoopOnHit = shouldBeOn;
}


void BeatDetectorBase::setSampleRate(int newSampleRate){
    
    sampleRate = newSampleRate;
    peakDetector.setSampleRate(newSampleRate);
}