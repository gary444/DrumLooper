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

class BeatDetector {
    
public:
    
    class Listener
    {
    public:
        
        virtual ~Listener() {}
        virtual void setLoopStartPoint() = 0;
        virtual void setLoopEndPoint() = 0;
    };
    
    BeatDetector();
    ~BeatDetector();
    
    void setListener(Listener* newListener);
    
    void process(float input, int channel);
    
    void setNumberOfBeats(int newNumberOfBeats);
    
private:
    
    Atomic<int> waitingForFirstHit;
    int noOfBeats;
    
    Listener* listener;
};


#endif /* defined(__DrumLooper__BeatDetector__) */
