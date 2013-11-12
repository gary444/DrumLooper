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
    
    
    std::cout << "Layer dtor\n";
}
float Layer::getSampleData(int channel, int offset)
{
    float* sample = audioSampleBuffer->getSampleData(channel, offset);
    //play
    float output = *sample;
    
    sharedMemory.enter();
    
    if (isMuted)
        output = 0.f;
    else
        output = output * layerGain;

    sharedMemory.exit();
    
    return output;
    
}

void Layer::setSampleData(int channel, int offset, float newVal)
{
    float* sample = audioSampleBuffer->getSampleData(channel, offset);
    *sample = newVal;
    
}

void Layer::setLayerIndex(int newLayerIndex){
    
    sharedMemory.enter();//is this needed?
    layerIndex = newLayerIndex;
    sharedMemory.exit();
}

void Layer::setLayerGain(float newGain){
    
    //**problem here when accessing audioSampleBuffer
    //if (audioSampleBuffer != NULL) {
    
    //audioSampleBuffer->applyGain(newGain);
    
    //}
    
    if (newGain >= 0.0 && newGain <= 1.0)
    {
        sharedMemory.enter();//is this needed?
        layerGain = newGain;
        sharedMemory.exit();
    }
    
    
}

void Layer::setMuted(bool shouldBeMuted){
    
    sharedMemory.enter();
    isMuted = shouldBeMuted;
    sharedMemory.exit();
}

//void Layer::setBufferSize(int newBufferSize){
    
    //sharedMemory.enter();//is this needed?
    //bufferSize = newBufferSize;
    //sharedMemory.exit();
//}


void Layer::setSize(unsigned int newSize){
    
    audioSampleBuffer->setSize(2, newSize, true);
}

int Layer::getLayerIndex(){
    
    sharedMemory.enter();//is this needed?
    int iD = layerIndex;
    sharedMemory.exit();
    
    return iD;
}

void Layer::signal(){
    
    sharedMemory.enter();
    std::cout << "New Layer: Number" << layerIndex + 1 << "\n";
    sharedMemory.exit();
}