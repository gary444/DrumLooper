//
//  SimpleTempoCalculator.h
//  DrumLooper
//
//  Created by Gareth Rendle on 15/11/2013.
//
//

#ifndef __DrumLooper__SimpleTempoCalculator__
#define __DrumLooper__SimpleTempoCalculator__

#include <iostream>
#include "../JuceLibraryCode/JuceHeader.h"
#include "SimplePeakDetector.h"

class SimplePeakDetector;


//class to pass values to a peak detector and determine a tempo from the peaks detected, with a given number of count in beats. Informs listener when tempo is found.

class SimpleTempoCalculator {
    
public:
    
    class Listener {
        
    public:
        
        virtual ~Listener() {}
        virtual void tempoDetected(float newTempo) = 0;
        //virtual void peakDetected() = 0;
    };
    
    SimpleTempoCalculator();
    ~SimpleTempoCalculator();
    
    void process(float input);
    
    void setSampleRate(int newSampleRate);
    
    void setListener(Listener* newListener);
    
    void setCountInBeats(int newNumberOfBeats);
    
private:
    Listener* listener;
    SimplePeakDetector peakDetector;
    
    int sampleRate;
    int countInBeats;
    
    unsigned int sampleCount;
    int firstHitSampleTime;
    int lastHitSampleTime;
    int beatCount;
    
};


#endif /* defined(__DrumLooper__SimpleTempoCalculator__) */