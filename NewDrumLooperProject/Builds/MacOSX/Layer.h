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
    
    Layer(int newLayerIndex, float newLayerGain);
    
    ~Layer();
    
    float getSampleData(int channel, int offset);
    
    void setSampleData(int channel, int offset, float newVal);
    
    void setLayerIndex(int newLayerIndex);
    
    void setLayerGain(float newGain);
    
    void setBufferSize(int newBufferSize);
    
    int getLayerIndex();
    
    //test function to check number of layer
    void signal();
    
    
private:
    //Audio data
    int bufferSize; //constant (90 sec = 3969000)
    int layerIndex;
    float layerGain;
    
    //members
    AudioSampleBuffer* audioSampleBuffer;
    CriticalSection sharedMemory;//is this needed?
    
    
};

#endif /* defined(__DrumLooper__Layer__) */
