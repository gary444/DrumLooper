//
//  Layer.cpp
//  DrumLooper
//
//  Created by Gareth Rendle on 05/11/2013.
//
//

#include "Layer.h"

Layer::Layer()
{
    layerIndex = 0;
    bufferSize = 352800;
    layerGain = 0.8;
    layerPan = 0.5;
    isMuted = false;
    
    //create and init buffer
    audioSampleBuffer = new AudioSampleBuffer(2, bufferSize);
    //audioSampleBuffer->clear();
}

Layer::Layer(int newLayerIndex, unsigned int newBufferSize, float newLayerGain)
{
    layerIndex = newLayerIndex;
    isMuted = false;
    
    //check gain is in range
    if (newLayerGain >= 0.0 && newLayerGain <= 1.0)
    {
        layerGain = newLayerGain;
    }
    else{
        layerGain = 0.8;
    }
    
    
    //create and init buffer
    audioSampleBuffer = new AudioSampleBuffer(2, newBufferSize);
}

Layer::~Layer()
{
    //delete audioSampleBuffer;
    
    
    //std::cout << "Layer dtor\n";
}
float Layer::getSampleData(int channel, int offset)
{
    float* sample = audioSampleBuffer->getSampleData(channel, offset);
    //play
    float output = *sample;
    
    sharedMemory.enter();
    
    //apply mute/gain
    if (isMuted)
        output = 0.f;
    else
        output = output * layerGain;
    

    //apply pan
    if (channel == 0)
        output = output * (1 - layerPan);
    else if (channel == 1)
        output = output * layerPan;
    
    sharedMemory.exit();
    
    return output;
    
}

void Layer::setSampleData(int channel, int offset, float newVal)
{
    
    if (newVal > 1 || newVal < -1) {
        std::cout << "layer sample out of range (" << newVal << ")\n";
    }
    
    float* sample = audioSampleBuffer->getSampleData(channel, offset);
    *sample = newVal;
    
}

void Layer::setLayerIndex(int newLayerIndex){
    
    sharedMemory.enter();//is this needed?
    layerIndex = newLayerIndex;
    sharedMemory.exit();
}

void Layer::setLayerGain(float newGain){
    
    if (newGain >= 0.0 && newGain <= 1.0)
    {
        sharedMemory.enter();
        layerGain = newGain;
        sharedMemory.exit();
    }
}

void Layer::setLayerPan(float newPan){
    
    if (newPan >= 0.0 && newPan <= 1.0)
    {
        sharedMemory.enter();
        layerPan = newPan;
        sharedMemory.exit();
    }
}
void Layer::setMuted(bool shouldBeMuted){
    
    sharedMemory.enter();
    isMuted = shouldBeMuted;
    sharedMemory.exit();
}
void Layer::setSize(unsigned int newSize){
    
    audioSampleBuffer->setSize(2, newSize, true);
}

int Layer::getSize(){
    
    //return bufferSize;
    
    return audioSampleBuffer->getNumSamples();
}

int Layer::getLayerIndex(){
    
    sharedMemory.enter();//is this needed?
    int iD = layerIndex;
    sharedMemory.exit();
    
    return iD;
}

void Layer::smooth(int sampleRate){
    
    //int sampleRate = 44100;
    float fadeLengthTime = 0.001;
    int fadeLengthSamples = fadeLengthTime * sampleRate;
    
    //fade in
    
    for (int i = 0; i < fadeLengthSamples; i++) {
        
        float* sampleL = audioSampleBuffer->getSampleData(0, i);
        *sampleL = *sampleL * (i / fadeLengthSamples);
        
        float* sampleR = audioSampleBuffer->getSampleData(1, i);
        *sampleR = *sampleR * (i / fadeLengthSamples);
    }
    
    //fade out
    for (int i = 0; i < fadeLengthSamples; i++) {
        
        float* sampleL = audioSampleBuffer->getSampleData(0, audioSampleBuffer->getNumSamples() - 1 - i);
        *sampleL = *sampleL * (i / fadeLengthSamples);
        
        float* sampleR = audioSampleBuffer->getSampleData(1, audioSampleBuffer->getNumSamples() - 1 - i);
        *sampleR = *sampleR * (i / fadeLengthSamples);
    }
    
}
