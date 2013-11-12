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
    modeIndex = 0;
    beats = 8;
    tempo = 100.f;
    //position to the start of audioSampleBuffer
    bufferPosition = 0;
    //default SR is 44k1
    sampleRate = 44100;
    
    //gui
    //looperGUI = new LooperGUI;
    looperGUI.setListener(this);
    addAndMakeVisible(&looperGUI);
    
    
    bufferSize  = 3969000;//start at 90 sec @ 44.1khz
    
    //for (int i = 0; i < 8; i++) {
    //    layer[i].setLayerIndex(i);
    //    layer[i].setBufferSize(bufferSize);
    //}
    
    currentLayer = 0;
    
    //**test
    test = 11;
}

Looper::~Looper()
{

    std::cout << "Looper dtor\n";
}

//ComponentCallbacks============================================================
void Looper::resized(){
    
    looperGUI.setBoundsRelative(0.0, 0.0, 1.0, 1.0);
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

void Looper::layerGainChanged(const int layerIndex, float newGain){
    
    //layer[layerIndex].setLayerGain(newGain);
    
    //check layerIndex is valid before processing request
    if (layerIndex < currentLayer) {
        layers[layerIndex]->setLayerGain(newGain);
    }
    
    
    std::cout << "new gain = " << newGain << " for layer = " << layerIndex + 1 << "\n";
}
void Looper::layerMuteToggled(const int layerIndexToggled, bool shouldBeMuted){
    
    layers[layerIndexToggled]->setMuted(shouldBeMuted);
}


void Looper::setPlayState (const bool newState)
{
    
    //add a first layer if looper started
    if (layers.size() == 0) {
        
        Layer* newLayer = new Layer(0, bufferSize, 0.8);
        layers.add(newLayer);
        layers[0]->signal();
        
    }
    
    playState = newState;
    looperGUI.setPlayState(getPlayState());
}

bool Looper::getPlayState () const
{
    return playState.get();
}

void Looper::setRecordState (const bool newState)
{
    recordState = newState;
    looperGUI.setRecordState(getRecordState());
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

void Looper::trigger(){
    
    std::cout << "looper has receieved trigger\n";
    
    //for mode 1, if recording...
    if (modeIndex == 0 && recordState.get() == true) {
        //if not playing, start playing (and recording)
        if (playState.get() == false) {
            setPlayState(true);
            //playButtonToggled();
        }
        else {
            //if playing, stop recording and set loop end point
            //setRecordState(false);
            endLoop();
        }
    }
}

void Looper::startLoop(){
    
    
}

void Looper::endLoop(){
    
    //set buffer size to current position
    bufferSize = bufferPosition;
    //reset position
    //bufferPosition = 0;
    
    //trim first layer
    //layers[0]->setSize(bufferSize);
}


void Looper::setMode(int newModeIndex){
    
    modeIndex = newModeIndex;
}


//mode 2 stuff
void Looper::tempoValueChanged(const float newTempo){
    
    tempo = newTempo;
    std::cout << "new Looper tempo = " << newTempo << std::endl;
}
void Looper::numberOfBeatsChanged(const int newNumberOfBeats){
    
    beats = newNumberOfBeats;
    std::cout << "new Looper beats = " << newNumberOfBeats << std::endl;
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
            output += layers[i]->getSampleData(channel, bufferPosition);
        }
        
        //click 16 times each bufferLength
        //if ((bufferPosition % (bufferSize / 16)) == 0){
        //    output += 0.25f;
            //trigger metronome
            //metronome.tick();
        //}
        
        //record
        if (recordState.get() == true){
            
            //if recording, write input ONLY to current layer
            layers[currentLayer]->setSampleData(channel, bufferPosition, input);
            
        }
        else {
            //read from current layer
            output += layers[currentLayer]->getSampleData(channel, bufferPosition);
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
                //notify gui
                looperGUI.addLayer();
                
                //add pointer to new layer to array
                Layer* newLayer = new Layer(currentLayer + 1, bufferSize, 0.8);
                layers.add(newLayer);
                
                //increment current layer to correspond to layer just added
                currentLayer++;
                
                //signal that a layer has been added
                layers[currentLayer]->signal();
                
                //tell looper to start transport if just added first layer
                if (currentLayer == 1) {
                    looperGUI.setTransportRunningState(true);
                }
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