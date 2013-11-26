//
//  PatchInfo.h
//  DrumLooper
//
//  Created by Gareth Rendle on 19/11/2013.
//
//

#ifndef __DrumLooper__PatchInfo__
#define __DrumLooper__PatchInfo__

#include <iostream>

//class to store audio device patch info

class PatchInfo {
    
public:
    PatchInfo() {numInputChannels = numOutputChannels = looperInput1Index = looperInput2Index = triggerInputIndex = 0; }
    ~PatchInfo() { }
    
    void setNumberOfInputChannels(int numChannels) {
        
        numInputChannels = numChannels;
        
        if (numChannels == 2) {
            looperInput2Index = 1;
            triggerInputIndex = 1;
        }
        else if (numChannels > 2){
            looperInput2Index = 1;
            triggerInputIndex = 2;
        }
    }
    void setNumberOfOutputChannels(int numChannels) {
        
        numOutputChannels = numChannels;
    }
    
    int getlooperInput1Index() {return looperInput1Index;}
    int getlooperInput2Index() {return looperInput2Index;}
    int getTriggerInputIndex() {return triggerInputIndex;}
    
private:
    
    int numInputChannels;
    int numOutputChannels;
    
    int looperInput1Index;
    int looperInput2Index;
    int triggerInputIndex;
};

#endif /* defined(__DrumLooper__PatchInfo__) */
