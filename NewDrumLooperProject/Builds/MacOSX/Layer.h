//
//  Layer.h
//  DrumLooper
//
//  Created by Gareth Rendle on 05/11/2013.
//
//

#ifndef __DrumLooper__Layer__
#define __DrumLooper__Layer__

#include <iostream>
#include "../JuceLibraryCode/JuceHeader.h"

class Layer
{
public:
    Layer();
    ~Layer();
    
    float getSampleData(int channel, int offset);
    
    void setSampleData(int channel, int offset, float newVal);
    
    void setLayerId(int iD);
    
    void setLayerGain(float newGain);
    
    void setBufferSize(int newBufferSize);
    
    int getLayerId();
    
    void signal();
    
    
private:
    //Audio data
    int bufferSize; //constant (90 sec = 3969000)
    
    AudioSampleBuffer* audioSampleBuffer;
    
    CriticalSection sharedMemory;//is this needed?
    
    int layerId;
};

#endif /* defined(__DrumLooper__Layer__) */
