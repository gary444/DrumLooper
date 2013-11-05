//
//  Looper.cpp
//  DrumLooper
//
//  Created by Gareth Rendle on 05/11/2013.
//
//

#include "Looper.h"

Looper::Looper()
{
    //initialise - not playing / recording
    playState = false;
    recordState = false;
    //position to the start of audioSampleBuffer
    bufferPosition = 0;
    
    //gui
    looperGUI = new LooperGUI;
    looperGUI->setListener(this);
    addAndMakeVisible(looperGUI);
    
    
    //layers.resize(1);
    
    bufferSize  = 352800;
    
    for (int i = 0; i < 8; i++) {
        layer[i].setLayerId(i);
        layer[i].setBufferSize(bufferSize);
    }
    
    currentLayer = 0;
    
    //**test
    test = 11;
}

Looper::~Looper()
{
    //delete audioSampleBuffer;
}

//ComponentCallbacks============================================================
void Looper::resized(){
    
    looperGUI->setBoundsRelative(0.0, 0.0, 1.0, 1.0);
}
void Looper::paint (Graphics &g){
    
}

//looperGUI listener callbacks==============================================
void Looper::playButtonToggled(){
    
    setPlayState(!getPlayState());
    
}
void Looper::recordButtonToggled(){
    
    setRecordState(!getRecordState());
}

void Looper::layerGainChanged(const int layerNumber, float newGain){
    
    //subtract 1 from layer number to translate to 'computer nos'
    layer[layerNumber - 1].setLayerGain(newGain);
    std::cout << "new gain = " << newGain << " for layer = " << layerNumber << "\n";
}


void Looper::setPlayState (const bool newState)
{
    playState = newState;
    looperGUI->setPlayState(getPlayState());
}

bool Looper::getPlayState () const
{
    return playState.get();
    
}

void Looper::setRecordState (const bool newState)
{
    recordState = newState;
    looperGUI->setRecordState(getRecordState());
}

bool Looper::getRecordState () const
{
    return recordState.get();
}

float Looper::getReaderPosition ()
{
    float position;
    
    
    
    
    
    //const ScopedLock scopedLock(sharedMemory);
    //sharedMemory.enter();
    position = test;
    //position = bufferSize / bufferPosition;
    //sharedMemory.exit();
    
    
    return position;
}

//
//if the same function is used for L + R, buffer should not be moved on each time!
//
float Looper::processSample (float input, int channel)
{
    //lock
    //const ScopedLock scopedLock(sharedMemory);
    
    sharedMemory.enter();
    
    float output = 0.f;
    if (playState.get() == true)
    {
        //read from all preceding layers (from 0 to current layer -1)
        for (int i = 0; i < currentLayer; i++) {
            output += layer[i].getSampleData(0, bufferPosition);
        }
        
        //click 16 times each bufferLength
        if ((bufferPosition % (bufferSize / 16)) == 0){
            output += 0.25f;
            //trigger metronome
            //metronome.tick();
        }
        
        
        
        //record
        if (recordState.get() == true){
            
            //if recording, write input ONLY to current layer
            layer[currentLayer].setSampleData(0, bufferPosition, input);
        }
        else {
            output += layer[currentLayer].getSampleData(0, bufferPosition);
        }
        
        //add metronome output
        //output += metronome.getNextSample(channel);
        
        
        //increment and cycle the buffer counter, changing to a new layer if recording.
        //only increment if processing right channel (channel 1).
        if (channel == 1) {
            bufferPosition++;
        }
        if (bufferPosition == bufferSize){
            
            if (recordState.get() == true && currentLayer != 7){
                looperGUI->addLayer();
                currentLayer++;
                layer[currentLayer].signal();
            }
            
            bufferPosition = 0;
        }
        
    }
    
    sharedMemory.exit();
    
    return output;
}


void Looper::setSampleRate(const int newSampleRate){
    
    sampleRate = newSampleRate;
}

void Looper::setLayerGain(int layerNum, float newGain){
    
    layer[layerNum].setLayerGain(newGain);
}