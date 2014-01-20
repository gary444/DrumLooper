//
//  BeatDetectorB.h
//  sdaFileEffect
//
//  Created by Gary Rendle on 28/12/2013.
//
//

#ifndef __sdaFileEffect__BeatDetectorB__
#define __sdaFileEffect__BeatDetectorB__

#include <iostream>
//#include "../JuceLibraryCode/JuceHeader.h"
//#include "AdaptivePeakDetector.h"
//#include "DetectionState.h"
#include "BeatDetectorBase.h"

struct IntervalInfo {
    int sampleLength;
    int confidence;
    float tempoVal;
    //Array<int> matchedValues;
};

class BeatDetectorB : public BeatDetectorBase
{
    
public:
    
    class Listener
    {
    public:
        
        virtual ~Listener() {}
        virtual void tempoUpdated(float newTempo) = 0;
        virtual void setLoopStartPoint() = 0;
        virtual void setLoopEndPoint() = 0;
    };
    
    BeatDetectorB();
    ~BeatDetectorB();
    
    void setListener(Listener* newListener);
    
    void process(float input, int channel);
    
    //void setNumberOfBeats(int newNumberOfBeats);
    
    void reset();
    
    //void showHits(bool should);
    
    //void printConfidences();
    
private:
    
    //functions
    void processPeak();
    
    void reportMostLikelyTempo();
    
    float getTempo(int sampleInterval);
    
    
    bool sampleValuesAreClose(int val1, int val2);
    
    Array<IntervalInfo> sortIntervalInfos(Array<IntervalInfo> arrayToSort);
    
    
    //members
    Array<int> intervalValues;
    Array<IntervalInfo> intervalInfos;
    
    Listener* listener;
};

#endif /* defined(__sdaFileEffect__BeatDetectorB__) */
