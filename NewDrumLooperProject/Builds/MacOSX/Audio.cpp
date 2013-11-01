//
//  Audio.cpp
//  DrumLooper
//
//  Created by Gareth Rendle on 01/11/2013.
//
//

#include "Audio.h"

Audio::Audio(){
    
    audioDeviceManager.initialise(3, 2, 0, true, String::empty, 0);
    audioDeviceManager.addAudioCallback(this);
}

//AudioCallbacks================================================================
void Audio::audioDeviceIOCallback (const float** inputChannelData,
                            int numInputChannels,
                            float** outputChannelData,
                            int numOutputChannels,
                                   int numSamples)
{
    
    
    const float *inL, *inR;
    float *outL, *outR;
    
    inL = inputChannelData[0];
    inR = inputChannelData[1];
    outL = outputChannelData[0];
    outR = outputChannelData[1];
    
    while(numSamples--)
    {
        //float outputL, outputR = 0.f;
        
        *outL = *inL;
        *outR = *inR;
        
        if (*outL > 0.1) {
            //std::cout << "level detected";
        }
        
        inL++;
        inR++;
        outL++;
        outR++;
    }
}

void Audio::audioDeviceAboutToStart (AudioIODevice* device){
    
}
void Audio::audioDeviceStopped(){
    
}