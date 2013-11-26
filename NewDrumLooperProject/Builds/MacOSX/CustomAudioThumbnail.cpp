//
//  CustomAudioThumbnail.cpp
//  DrumLooper
//
//  Created by Gareth Rendle on 18/11/2013.
//
//

#include "CustomAudioThumbnail.h"

CustomAudioThumbnail::CustomAudioThumbnail(){
    
    resCount = 0;
    resolution = 50;
    
    drawValues.clear();
    fitToSizeValues.clear();
    
}
CustomAudioThumbnail::~CustomAudioThumbnail(){
    
    
}
void CustomAudioThumbnail::translate(Layer& layer, int lengthInSamples){
    
    runningTotal = 0;
    
    //std::cout << "translate called\n";
    
    
    for (int i = 0; i < lengthInSamples; i++) {
        
        //add to running total
        runningTotal += twoChannelAverage(layer.getSampleData(0, i), layer.getSampleData(1, i));
        
        //if resolution factor is equal write average value to draw array
        if (resCount == resolution) {
            
            drawValues.add(runningTotal / resolution);
            
            //reset
            runningTotal = 0;
            resCount = 0;
        }
        
        //increment resolution counter
        resCount++;
    }
}

void CustomAudioThumbnail::fitResolutionToSize(int thumbnailWidth, int thumbnailHeight){
    
    //check we are not given 0 values
    if (thumbnailHeight != 0 && thumbnailWidth != 0) {
        
        
        float transformFactor = drawValues.size() / thumbnailWidth;
        float position = 0.f;
        
        while (position < drawValues.size()) {
            
            //find pixel height using interpolation function
            //pixel value must be a proportion of half the height as waveform will be mirrored
            int pixelHeight = static_cast<int>((thumbnailHeight / 2.0) * interpolatedRead(position));
            
            //add to array
            fitToSizeValues.add(pixelHeight);
            
            //increase position by transform factor
            position += transformFactor;
        }
        
    }
}

int CustomAudioThumbnail::getPixelDrawValue(int pixel){
    
    return fitToSizeValues[pixel];
}

float CustomAudioThumbnail::interpolatedRead(float readPos)
{
	int pos1, pos2;
	float pDiff, vDiff, result;
	
    pos1 = (int)readPos;
    pos2 = pos1 + 1;
    if(pos2 == drawValues.size())
        pos2 = 0;
    
    pDiff = readPos - pos1;
	vDiff = drawValues[pos2] - drawValues[pos1];
    result = drawValues[pos1] + (vDiff * pDiff);
    
	return result;
}