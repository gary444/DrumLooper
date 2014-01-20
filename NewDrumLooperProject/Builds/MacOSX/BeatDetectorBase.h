//
//  BeatDetectorBase.h
//  sdaFileEffect
//
//  Created by Gary Rendle on 28/12/2013.
//
//

#ifndef __sdaFileEffect__BeatDetectorBase__
#define __sdaFileEffect__BeatDetectorBase__

#include "../JuceLibraryCode/JuceHeader.h"
#include "AdaptivePeakDetector.h"

class BeatDetectorBase {
    
public:
    
    BeatDetectorBase();
    virtual ~BeatDetectorBase();
    
    virtual void process(float input, int channel) = 0;
    
    virtual void setNumberOfBeats(int newNumberOfBeats);
    
    virtual void reset();
    
    virtual void showHits(bool should);
    
    virtual float putTempoInRange(float tempoToCheck);
    
    void setEndLoopOnHit(bool shouldBeOn);
    
    void setSampleRate(int newSampleRate);

    void updateLoopSampleTarget(float tempo);
    
    bool tempiAreClose(float tempo1, float tempo2);
    
protected:
    
    //functions
    virtual void processPeak() = 0;
    
    virtual void reportMostLikelyTempo() = 0;
    
    
    //members
    Atomic<int> waitingForFirstHit;
    int noOfBeats;
    int sampleRate;
    float tempoLowerLimit;
    float tempoUpperLimit;
    float tempLChannelData;
    
    
    int loopSampleTarget;
    bool endLoopOnHit;
    bool waitingForLastHit;
    
    int intervalCount;
    int interval2Count;
    int interval3Count;
    bool intervalCounting;
    bool interval2Counting;
    bool interval3Counting;
    
    AdaptivePeakDetector peakDetector;
    
    //for testing
    int hitCount;
    Atomic<int> showingHits;
    float highestInputValue;
    int sampleNumber;
};

#endif /* defined(__sdaFileEffect__BeatDetectorBase__) */
