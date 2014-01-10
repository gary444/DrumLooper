//
//  BeatDetector.h
//  sdaFileEffect
//
//  Created by Gary Rendle on 13/12/2013.
//
//

#ifndef __sdaFileEffect__BeatDetector__
#define __sdaFileEffect__BeatDetector__

#include <iostream>
#include "DetectionState.h"
#include "BeatDetectorBase.h"

class BeatDetector : public BeatDetectorBase
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
    
    
    BeatDetector();
    ~BeatDetector();

    void setListener(Listener* newListener);
    
    void process(float input, int channel);
    
    void reset();
    
    void printConfidences();
    
private:
    
    //functions
    void processPeak();
    
    void reportMostLikelyTempo();
    
    Array<int> sortAgent(Array<DetectionState*> agentToSort);
    
    float getTempo(Array<DetectionState*> hostAgent, int index);
    
    bool tempiAreClose(float tempo1, float tempo2);
    
    void updateLoopSampleTarget(float tempo);
    
    
    //members
    Array<DetectionState*> agent1;
    Array<DetectionState*> agent2;
    Array<DetectionState*> agent3;
    Array<float> testedNoteValues;
    
    Listener* listener;
    
    int loopSampleTarget;
    
};
#endif /* defined(__sdaFileEffect__BeatDetector__) */
