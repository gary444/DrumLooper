//
//  Metronome.h
//  sdaAudio
//
//  Created by Gareth Rendle on 17/10/2013.
//
//

#ifndef __DrumLooper__Metronome__
#define __DrumLooper__Metronome__

#include <iostream>
#include "../JuceLibraryCode/JuceHeader.h"

class Metronome
{
public:
    Metronome();
    ~Metronome();
    
    float getNextSample(int channel);

    void loadFile(File fileToLoad);
    
    void tick();
    
    /**
     Toggles the current play state
     */
    void togglePlayState();
    
    /**
     Returns the playstate of the player
     */
    bool isPlaying() const;

private:

    //State data
    CriticalSection sharedMemory;

    bool playing;
    
    //Audio data
    unsigned int bufferPosition;
    AudioSampleBuffer* audioSampleBuffer;

};

#endif /* defined(__DrumLooper__Metronome__) */
