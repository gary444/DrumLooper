//
//  Metronome.cpp
//  sdaAudio
//
//  Created by Gareth Rendle on 17/10/2013.
//
//

#include "Metronome.h"

Metronome::Metronome(){
    
    //initial state - not playing
    playing = false;
    //position to the start of audioSampleBuffer
    bufferPosition = 0;
    //Set audio sample buffer to NULL - no file loaded initially
    audioSampleBuffer = NULL;
    
    //File file;
    
    //loadFile(<#juce::File fileToLoad#>)
}
Metronome::~Metronome(){
    
    //only delete if previously allocated
    if (audioSampleBuffer != NULL)
        delete audioSampleBuffer;
}

float Metronome::getNextSample(int channel){
    
    float output = 0.f;
    
    sharedMemory.enter();
    //if there's no file or we are not playing then do nothing
    if(playing && audioSampleBuffer != NULL)
    {
        output = *audioSampleBuffer->getSampleData(0, bufferPosition);
    
    
        //only move on and check buffer if dealing with Right channel
        if (channel == 1)
        {
            
            bufferPosition++;
            if (bufferPosition == audioSampleBuffer->getNumSamples())
            {
                togglePlayState();
                //std::cout << "play state toggled from getNextSample\n";
                bufferPosition = 0;
            }
        }
        
    }
    sharedMemory.exit();
    
    return output;
}

void Metronome::loadFile(File fileToLoad){
    
    
    AudioFormatManager formatManager;
    formatManager.registerBasicFormats();
    AudioFormatReader* reader = formatManager.createReaderFor(fileToLoad);
    
    if (reader != 0)
    {
        //load the new sample
        AudioSampleBuffer *newAudioSampleBuffer;
        AudioSampleBuffer *oldAudioSampleBuffer = NULL;
        newAudioSampleBuffer = new AudioSampleBuffer(reader->numChannels, reader->lengthInSamples);
        reader->read(newAudioSampleBuffer, 0, reader->lengthInSamples, 0, true, true);
        
        //swap pointers load the file before blocking the audio thread!
        sharedMemory.enter();
        oldAudioSampleBuffer = audioSampleBuffer;
        audioSampleBuffer = newAudioSampleBuffer;
        bufferPosition = 0;
        sharedMemory.exit();
        
        //delete old buffer first time this will be NULL
        if (oldAudioSampleBuffer != NULL)
            delete oldAudioSampleBuffer;
        
        //delete the reader
        delete reader;
        
        std::cout << "file loaded to metro\n";
    }
}

void Metronome::tick()
{
    sharedMemory.enter();
    if (audioSampleBuffer != NULL)
    {
        playing = true;
        bufferPosition = 0;
    }
    sharedMemory.exit();
    
    std::cout << "tick\n";
}

void Metronome::togglePlayState()
{
    sharedMemory.enter();
    if (audioSampleBuffer != NULL)
        playing = !playing;
    sharedMemory.exit();
}

bool Metronome::isPlaying() const
{
    sharedMemory.enter();
    bool state = playing;
    sharedMemory.exit();
    
    return state;
}