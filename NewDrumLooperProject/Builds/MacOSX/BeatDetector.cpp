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
    
    
    
}