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
    addKeyListener(this);
    
    //inits
    playState = false;
    recordState = false;
    countInState = false;
    alternateLoopRec = false;
    //alternateLoopRecState = true;
    mode1loopSet = false;
    detectingBeat = false;
    mode3waiting = false;
    countInCount = 0;
    countInBeats = 4;
    countInLength = 105840;
    ready = true;
    metroOn = true;
    modeIndex = 0;
    beats = 8;
    tempo = 100.f;
    //position to the start of audioSampleBuffer
    bufferPosition = 0;
    //default SR is 44k1
    sampleRate = 44100;
    guiUpdateCount = 0;
    
    //add gui
    looperGUI.setListener(this);
    addAndMakeVisible(&looperGUI);
    
    //connect beat detector
    beatDetector.setListener(this);
    beatDetectorB.setListener(this);
    beatDetectorId = 1;
    
    bufferSize  = 3969000;//start at 90 sec @ 44.1khz
    
    currentLayer = 0;
    
}

Looper::~Looper()
{
    //std::cout << "Looper dtor\n";
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
    
    //check layerIndex is valid before processing request
    if (layerIndex < currentLayer) {
        layers[layerIndex]->setLayerGain(newGain);
    }
}

void Looper::layerPanChanged(const int layerIndex, const float newPanPosition){
 
    layers[layerIndex]->setLayerPan(newPanPosition);
}

void Looper::layerMuteToggled(const int layerIndexToggled, bool shouldBeMuted){
    
    layers[layerIndexToggled]->setMuted(shouldBeMuted);
}


void Looper::deleteLayer(int layerIndex){
    
    //std::cout << "delete layer\n";
    
    //remove layer
    layers.remove(layerIndex);
    
    for (int i = 0; i < layers.size(); i++) {
        layers[i]->setLayerIndex(i);
    }
    
    //reduce current layer
    currentLayer--;
}
void Looper::deleteAllLayers(){
    
    //std::cout << "delete all layers\n";
    
    //stop playing
    setPlayState(false);
    looperGUI.setPlayState(false);
    setRecordState(true);
    looperGUI.setRecordState(true);
    //clear layer array
    layers.clear();
    
    //set ready
    ready = true;
    listener->looperReady(true);
    
    //reset buffer and position
    bufferPosition = 0;
    looperGUI.setTransportUpdateStatus(true, 0.0, false);
    currentLayer = 0;
    
    //reset if mode 1
    if (modeIndex == 0) {
        bufferSize  = 3969000;//start at 90 sec @ 44.1khz
        mode1loopSet.set(false);
    }
    
    //reset beat detector if mode 3
    if (modeIndex == 2) {
        beatDetector.reset();
        beatDetectorB.reset();
        detectingBeat = false;
        mode3waiting = true;
        bufferSize  = 3969000;//start at 90 sec @ 44.1khz
    }
    
    updateTriggerFunction();
}

void Looper::setReaderToZero(){
    
    bufferPosition = 0;
    looperGUI.setTransportUpdateStatus(true, 0.0, false);
    
}


void Looper::setAlternateLoopRec(bool shouldBeOn){
    
    alternateLoopRec.set(shouldBeOn);
}

//Beat Detector Callbacks
void Looper::setLoopStartPoint(){
    
    
    std::cout << "Looper recieved start loop signal \n";
    
    mode3waiting = false;
    detectingBeat = true;
    setPlayState(true);
    
}
void Looper::setLoopEndPoint(){
    
    std::cout << "Looper recieved end loop signal \n";
    if (detectingBeat.get() == true) {
        detectingBeat.set(false);
        
        std::cout << "Loop ended\n";
        
        endLoop();
    }
}


void Looper::setPlayState (const bool newState)
{
    
    
    
    //add a first layer if looper started
    if (layers.size() == 0) {
        
        Layer* newLayer = new Layer(0, bufferSize, 0.8);
        layers.add(newLayer);
    }
    
    playState = newState;
    ready = false;
    
    MessageManagerLock mml (Thread::getCurrentThread());
    if (! mml.lockWasGained())
        return;
    listener->looperReady(false);
    
    looperGUI.setPlayState(getPlayState());
    
    updateTriggerFunction();
}

bool Looper::getPlayState () const
{
    return playState.get();
}

void Looper::setRecordState (const bool newState)
{
    MessageManagerLock mml (Thread::getCurrentThread());
    if (! mml.lockWasGained())
        return;
    
    recordState = newState;
    looperGUI.setRecordState(getRecordState());
    
    updateTriggerFunction();
    
    //std::cout << "setRec Called";
}

bool Looper::getRecordState () const
{
    return recordState.get();
}


void Looper::setCountInState (const bool newState){
    
    countInState.set(newState);
}

void Looper::trigger(){
    
    std::cout << "looper has receieved trigger\n";
    
    //for mode 1, if recording...
    if (modeIndex == 0) {
        
        
        
        if (recordState.get() && currentLayer == 0) {
            //if not playing, start playing (and recording)
            if (playState.get() == false) {
                setPlayState(true);
                //playButtonToggled();
            }
            else if(mode1loopSet.get() == false){
                //if playing, stop recording and set loop end point
                //setRecordState(false);
                endLoop();
                mode1loopSet = true;
            }
        }
        
        if (currentLayer > 0) {
            
            if (alternateLoopRec.get()) {
                alternateLoopRec.set(false);
                
                MessageManagerLock mml (Thread::getCurrentThread());
                if (! mml.lockWasGained())
                    return;
                looperGUI.cancelAlternateLoopRec();
            }
            
            setRecordState(!recordState.get());
        }
        
        
    }
    
    //for mode 2
    else if (modeIndex == 1){
        
        if (recordState.get()) {
            //if not playing, start count in
            if (playState.get() == false) {
                setPlayState(true);
                setCountInState(true);
                
                //tell gui we are counting in
                looperGUI.setTransportUpdateStatus(true, 0, true);
            }
        }
        
        if (currentLayer > 0) {
            setRecordState(!recordState.get());
        }
        
        
    }
    else if (modeIndex == 2){
        if (currentLayer > 0) {
            setRecordState(!recordState.get());
        }
    }
}

//void Looper::startLoop(){
//    
//    
//}

void Looper::endLoop(){
    
    //set buffer size to current position
    bufferSize = bufferPosition;
    
    //shouldnt need this!
    if (bufferSize == 0) {
        bufferSize = 3696000;
    }
    
    //trim first layer
    //layers[0]->setSize(bufferSize);
}


void Looper::setMode(int newModeIndex){
    
    modeIndex = newModeIndex;
    mode3waiting = false;
    
    
    if (newModeIndex == 1) {
        bufferSize = static_cast<int>(((60 * sampleRate) / tempo) * beats);
    }
    else if (newModeIndex == 2){
        
        detectingBeat = false;
        mode3waiting = true;
    }
    
    updateTriggerFunction();
}


//mode 2 stuff
void Looper::tempoValueChanged(const float newTempo){
    
    tempo = newTempo;
    
    bufferSize = static_cast<int>(((60 * sampleRate) / tempo) * beats);
    
    countInLength = static_cast<int>(((60 * sampleRate) / newTempo) * countInBeats);
    
}
void Looper::numberOfBeatsChanged(const int newNumberOfBeats){
    
    beats = newNumberOfBeats;
    
    if (modeIndex == 1) {
        
        bufferSize = static_cast<int>(((60 * sampleRate) / tempo) * beats);
    }
    
    //tell beat detector
    beatDetector.setNumberOfBeats(newNumberOfBeats);
    beatDetectorB.setNumberOfBeats(newNumberOfBeats);
    
}

void Looper::countInChanged(const int newNumberOfBeats){
    
    countInLength = static_cast<int>(((60 * sampleRate) / tempo) * newNumberOfBeats);
    countInBeats = newNumberOfBeats;
}
void Looper::metroToggled(bool shouldBeOn){
    
    metroOn = shouldBeOn;
}


void Looper::endLoopOnHitToggled(const bool shouldBeOn){
    
    beatDetector.setEndLoopOnHit(shouldBeOn);
    beatDetectorB.setEndLoopOnHit(shouldBeOn);
}

//if the same function is used for L + R, buffer should not be moved on each time!
//
float Looper::processSample (float input, int channel)
{
    
    sharedMemory.enter();
    
    float output = 0.f;
    //if waiting for loop to be started in mode 3
    if (modeIndex == 2 && mode3waiting.get() && recordState.get()) {
        
        if (beatDetectorId == 0)
            beatDetector.process(input, channel);
        else if (beatDetectorId == 1)
            beatDetectorB.process(input, channel);
        
    }
    //if playing....
    else if (playState.get() == true)
    {
        //if counting in
        if (countInState.get()){
            
            //only increment for every other sample
            if (channel == 1) {
                
                //trigger metronome
                if (countInCount % (countInLength / countInBeats) == 0) {
                    //trigger metronome
                    metronome.tick();
                }
                countInCount++;
                
                //if end of count in is reached...
                if (countInCount == countInLength) {
                    
                    //start playing and reset count in
                    countInState = false;
                    countInCount = 0;
                    
                    //tell gui we are no longer counting in
                    looperGUI.setTransportUpdateStatus(true, 0, false);
                }
            }
            
            //add metronome output
            output += metronome.getNextSample(channel);
        }
        //if not counting in...
        else {
            
            
            //read from all preceding layers (from 0 to current layer -1)
            for (int i = 0; i < currentLayer; i++) {
                
                output += layers[i]->getSampleData(channel, bufferPosition);
            }
            
            //record (write) to current layer if recording, read otherwise
            if (recordState.get() == true){
                layers[currentLayer]->setSampleData(channel, bufferPosition, input);
            }
            else {
                //read from current layer
                output += layers[currentLayer]->getSampleData(channel, bufferPosition);
            }
            
            //if current mode is mode 2 and metro is on...
            if (modeIndex == 1 && metroOn) {
                
                //only trigger metronome from R channel
                if (channel == 1) {
                    //...trigger metronome
                    if (bufferPosition % (bufferSize / beats) == 0) {
                        metronome.tick();
                    }
                }
                
                //add metronome to output
                output += metronome.getNextSample(channel);
                
            }
            
            //if current mode is mode 3 and we are still detecting the beat,
            //pass to beat detector
            else if (modeIndex == 2 && detectingBeat.get()) {
                
                if (beatDetectorId == 0)
                    beatDetector.process(input, channel);
                else if (beatDetectorId == 1)
                    beatDetectorB.process(input, channel);
            }
            
            //increment the buffer position.
            //only increment if processing right channel (channel 1).
            if (channel == 1) {
                bufferPosition++;
                
                //only start updating gui if one layer is completed
                if (layers.size() > 1 || (layers.size() == 1 && alternateLoopRec.get() && recordState.get() == false)) {
                    guiUpdateCount++;
                    if (guiUpdateCount == 2205) {
                        
                        //update gui at guiUpdateCount
                        guiUpdateCount = 0;
                        float f = bufferPosition;
                        //cast to float so result is not 0
                        f = static_cast<float>(f);
                        f = f / bufferSize;
                        looperGUI.setTransportUpdateStatus(true, f, false);
                    }
                }
            }
            
            //if the end of the buffer is reached...
            if (bufferPosition >= bufferSize){
                
                std::cout << "End of buffer reached\n";
                
                //if recording....
                if (recordState.get() == true && currentLayer != 7){
                    
                    //create thumbnail for recorded layer
                    CustomAudioThumbnail newThumbnail;
                    newThumbnail.translate(*layers[currentLayer], bufferSize);
                    
                    //notify gui
                    looperGUI.addLayer(newThumbnail);
                    
                    looperGUI.recordCycle.set(false);
                    
                    
                }
                
                if (alternateLoopRec.get()) {
                    
                    setRecordState(!recordState.get());
                }
                
                if (recordState.get() == true && currentLayer != 7) {
                    
                    if (currentLayer == 0) {
                        layers[currentLayer]->setSize(bufferSize);
                    }
                    
                    //smooth previously recorded layer
                    layers[currentLayer]->smooth(sampleRate);
                    
                    //add a new layer.
                    //add pointer to new layer to owned array
                    Layer* newLayer = new Layer(currentLayer + 1, bufferSize, 0.8);
                    layers.add(newLayer);
                    
                    looperGUI.recordCycle.set(true);
                    
                    //increment current layer to correspond to layer just added
                    currentLayer++;
                    
                    updateTriggerFunction();
                }
                
                //reset
                bufferPosition = 0;
            }
        }
    }
    
    
    sharedMemory.exit();
    
    return output;
}

void Looper::setSampleRate(const int newSampleRate){
    
    sampleRate = newSampleRate;
    
    beatDetectorB.setSampleRate(newSampleRate);
    beatDetector.setSampleRate(newSampleRate);
}

void Looper::setListener(Listener* newListener){
    listener = newListener;
}


//beat detector callback
void Looper::tempoUpdated(float newTempo){
    
    std::cout << "Tempo = " << newTempo << "\n";
}

void Looper::updateTriggerFunction(){
    
    String tempString;
    tempString = "None";
    
    if (modeIndex == 0) {
        if (recordState.get()) {
            if (currentLayer == 0) {
                if (playState.get()) {
                    tempString = "Set Loop End Point";
                }
                else {
                    tempString = "Set Loop Start Point";
                }
            }
            else {
                    tempString = "Turn Off Record";
            }
        }
        else {
            if (currentLayer > 0) {
                
                tempString = "Turn On Record";
            }
        }
    }
    else if (modeIndex == 1){
     
        if (recordState.get()) {
            if (currentLayer == 0) {
                if (playState.get()) {
                    //reset?
                }
                else {
                    tempString = "Start Count In/Tap In";
                }
            }
            else {
                
                tempString = "Turn Off Record";
            }
        }
        else {
            if (currentLayer > 0) {
                
                tempString = "Turn On Record";
            }
        }
    }
    else if (modeIndex == 2){
        if (currentLayer > 0) {
            if (recordState.get()) {
                tempString = "Turn Off Record";
            }
            else {
                tempString = "Turn On Record";
            }
        }
    }
    
    looperGUI.updateTriggerFunction(tempString);
}
//key listener callback
bool Looper::keyPressed (const KeyPress &key, Component *originatingComponent){
    
    bool done = false;
    
    //std::cout << "Looper Recieved " << key.getTextDescription() << "\n";
    
    if (key.getTextDescription() == "T"){
        trigger();
        done = true;
    }
    else if (key.getTextDescription() == "E"){
        bufferPosition = 0;
        looperGUI.setTransportUpdateStatus(true, 0, false);
        done = true;
    }
    
    updateTriggerFunction();
    
    return done;
}
