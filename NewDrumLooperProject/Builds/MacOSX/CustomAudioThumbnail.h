//
//  CustomAudioThumbnail.h
//  DrumLooper
//
//  Created by Gareth Rendle on 18/11/2013.
//
//

#ifndef __DrumLooper__CustomAudioThumbnail__
#define __DrumLooper__CustomAudioThumbnail__

#include <iostream>

#include "Layer.h"
#include "../JuceLibraryCode/JuceHeader.h"



class CustomAudioThumbnail {
    
    
public:
    CustomAudioThumbnail();
    ~CustomAudioThumbnail();
    
    void translate(Layer& layer, int lengthInSamples);
    
    void fitResolutionToSize(int thumbnailWidth, int thumbnailHeight);
    
    int getPixelDrawValue(int pixel);
    
private:
    //Array<float> sampleValues;
    Array<float> drawValues;
    Array<float> fitToSizeValues;
    
    int resolution;
    int resCount;
    float runningTotal;
    
    //function finds an absolute average of L and R input samples
    float twoChannelAverage(float lValue, float rValue) {
        return (fabsf(lValue) + fabsf(rValue)) / 2.0;
    }
    
    float interpolatedRead(float readPos);
};

#endif /* defined(__DrumLooper__CustomAudioThumbnail__) */
