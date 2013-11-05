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
    bufferSize = 352800;
    audioSampleBuffer = new AudioSampleBuffer(2, bufferSize);
}
Layer::~Layer()
{
    delete audioSampleBuffer;
}
float Layer::getSampleData(int channel, int offset)
{
    float* sample = audioSampleBuffer->getSampleData(channel, offset);
    //play
    float output = *sample;
    
    return output;
    
}

void Layer::setSampleData(int channel, int offset, float newVal)
{
    float* sample = audioSampleBuffer->getSampleData(channel, offset);
    
    *sample = newVal;
}

void Layer::setLayerId(int iD){
    
    sharedMemory.enter();//is this needed?
    layerId = iD;
    sharedMemory.exit();
}

void Layer::setLayerGain(float newGain){
    
    //**problem here when accessing audioSampleBuffer
    //if (audioSampleBuffer != NULL) {
    
    audioSampleBuffer->applyGain(0, audioSampleBuffer->getNumSamples(), newGain);
    
    //}
    
}

void Layer::setBufferSize(int newBufferSize){
    
    sharedMemory.enter();//is this needed?
    bufferSize = newBufferSize;
    sharedMemory.exit();
}

int Layer::getLayerId(){
    
    sharedMemory.enter();//is this needed?
    int iD = layerId;
    sharedMemory.exit();
    
    return iD;
}

void Layer::signal(){
    
    sharedMemory.enter();
    std::cout << "New Layer: Number" << layerId << "\n";
    sharedMemory.exit();
}