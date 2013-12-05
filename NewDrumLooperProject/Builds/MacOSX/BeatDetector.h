//
//  BeatDetector.h
//  DrumLooper
//
//  Created by Gary Rendle on 24/11/2013.
//
//

#ifndef __DrumLooper__BeatDetector__
#define __DrumLooper__BeatDetector__

#include <iostream>
#include "../JuceLibraryCode/JuceHeader.h"
#include "AdaptivePeakDetector.h"
#include "DetectionState.h"

class BeatDetector {
    
public:
    
    class Listener
    {
    public:
        
        virtual ~Listener() {}
        virtual void tempoUpdated(float newTempo) = 0;
    };
    
    BeatDetector();
    ~BeatDetector();
    
    void setListener(Listener* newListener);
    
    void process(float input, int channel);
    
    void setNumberOfBeats(int newNumberOfBeats);
    
    void reset();
    
    void showHits(bool should);
    
    void printConfidences();
    
private:
    
    //functions
    void processPeak();
    
    void reportMostLikelyTempo();
    
    //members
    
    Atomic<int> waitingForFirstHit;
    int noOfBeats;
    float tempoLowerLimit;
    float tempoUpperLimit;
    float tempLChannelData;
    
    int intervalCount;
    bool intervalCounting;
    
    Array<DetectionState*> agent1;
    Array<float> testedNoteValues;
    
    Listener* listener;
    AdaptivePeakDetector peakDetector;
    
    //for testing
    int hitCount;
    Atomic<int> showingHits;
    float highestInputValue;
    
};


#endif /* defined(__DrumLooper__BeatDetector__) */
