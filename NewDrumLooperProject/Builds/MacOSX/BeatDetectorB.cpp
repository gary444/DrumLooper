//
//  BeatDetectorB.cpp
//  sdaFileEffect
//
//  Created by Gary Rendle on 28/12/2013.
//
//

#include "BeatDetectorB.h"


BeatDetectorB::BeatDetectorB(){
    
    //inits
    noOfBeats = 8;
    waitingForFirstHit = true;
    tempoLowerLimit = 60.f;
    tempoUpperLimit = 180.f;
    tempLChannelData = 0.f;
    
    intervalCount = 0;
    interval2Count = 0;
    interval3Count = 0;
    intervalCounting = false;
    interval2Counting = false;
    interval3Counting = false;
    
    highestInputValue = 0.f;
    hitCount = 0;
    sampleNumber = 0;
    
    listener = nullptr;
}

BeatDetectorB::~BeatDetectorB(){
    
    listener = nullptr;
}


void BeatDetectorB::setListener(Listener* newListener){
    
    listener = newListener;
}

//void BeatDetectorB::setNumberOfBeats(int newNumberOfBeats){
//    
//    noOfBeats = newNumberOfBeats;
//}


void BeatDetectorB::process(float input, int channel){
    
    //create mono input from pairs of input samples with
    // different channel numbers
    float monoInput;
    if (channel == 0) {
        tempLChannelData = fabsf(input);
        
        //update sample counters if necessary
        if (intervalCounting)
            intervalCount++;
        if (interval2Counting)
            interval2Count++;
        if (interval3Counting)
            interval3Count++;
        
        sampleNumber++;
        
    
    }
    else
    {
        monoInput = (tempLChannelData + fabsf(input)) * 0.5;
        tempLChannelData = 0.f;
    }
    
    //only process if recieving non-zero values
    if (waitingForFirstHit.get() == false || monoInput > 0.001) {
        
        //if peak is detected
        if (peakDetector.process(monoInput) == true) {
            
            //if waiting for last hit, end loop
            if (waitingForLastHit) {
                if (listener != nullptr) {
                    listener->setLoopEndPoint();
                }
            }
            else {
                
                //if testing
//                if (showingHits.get())
//                    std::cout << "hit heard : " << hitCount << "\n";
                
                hitCount++;
                if (hitCount == 1) {
                    //start counters if necessary
                    intervalCounting = true;
                    interval2Counting = true;
                    
                    //start loop
                    if (listener != nullptr){
                        listener->setLoopStartPoint();
                        sampleNumber = 0;
                    }
                }
                //call process peak function (after hit count is updated!)
                else if (hitCount > 1)
                    processPeak();
                
                if (hitCount == 2)
                    interval3Counting = true;
                
                //report most likely tempo after x hits
                if (hitCount > 3) {
                    reportMostLikelyTempo();
                }
                
                //start loop if first hit
                if (waitingForFirstHit.get() == true) {
                    waitingForFirstHit = false;
                }
            }
        }
        
        //end loop
        if (sampleNumber >= loopSampleTarget) {
            
            if (endLoopOnHit) {
                waitingForLastHit = true;
            }
            else {
                std::cout << "End Of Loop\n";
                if (listener != nullptr) {
                    listener->setLoopEndPoint();
                }
            }
        }
    }
}

void BeatDetectorB::reset(){
    
    peakDetector.reset();
    
    hitCount = 0;
    intervalCount = 0;
    interval2Count = 0;
    interval3Count = 0;
    intervalCounting = false;
    interval2Counting = false;
    interval3Counting = false;
    waitingForFirstHit = true;
    sampleNumber = 0;
    
    intervalValues.clear();
    intervalInfos.clear();
    
    
    loopSampleTarget = 90 * sampleRate;//start at 90 sec
}

void BeatDetectorB::processPeak(){
    
    
    //add interval value to arrays
    intervalValues.add(intervalCount);
    
    IntervalInfo newInfoElement;
    newInfoElement.sampleLength = intervalCount;
    newInfoElement.confidence = 0;
    //newInfoElement.matchedValues.clear();
    intervalInfos.add(newInfoElement);
    
    
    //also add intervals 2 and 3!!!
    if (interval3Count == intervalCount) {
        if (hitCount > 1) {
            IntervalInfo newInfoElement2;
            newInfoElement2.sampleLength = interval2Count;
            newInfoElement2.confidence = 0;
            //newInfoElement2.matchedValues.clear();
            intervalInfos.add(newInfoElement2);
        }
    }
    else {
        if (hitCount > 2) {
            IntervalInfo newInfoElement2;
            newInfoElement2.sampleLength = interval3Count;
            newInfoElement2.confidence = 0;
            //newInfoElement2.matchedValues.clear();
            intervalInfos.add(newInfoElement2);
        }
    }
    
    
    //restart necessary counters
    intervalCount = 0;
    if (intervalCount != interval2Count)
        interval2Count = 0;
    else
        interval3Count = 0;
    
}

void BeatDetectorB::reportMostLikelyTempo(){
    
    //sort array of infos
    
    //reverse for loop to make sure all array elements are processed
    for (int i = (intervalInfos.size() - 1); i >= 0; i--) {
        //check i is in range of array
        if (i < intervalInfos.size()){
            
            //check that info element has no confidence
            if (intervalInfos[i].confidence == 0) {
                //cycle through array checking if sample values are close
                bool matched = false;
                for (int j = 0; j < intervalInfos.size(); j++) {
                    //dont compare to itself, or continue to search once a value is matched
                    if (j != i && matched == false) {
                        //compare interval values
                        if (sampleValuesAreClose(intervalInfos[i].sampleLength, intervalInfos[j].sampleLength)) {
                            
                            matched = true;
                            
                            //update j's sampleLength by averaging matched values
                            int newSampleLength = (intervalInfos[j].sampleLength * (intervalInfos[j].confidence + 1)) + intervalInfos[i].sampleLength;
                            newSampleLength = newSampleLength / (intervalInfos[j].confidence + 2);
                            
                            //add to j's confidence - should be a shorter way
                            IntervalInfo tempInfo = intervalInfos[j];
                            tempInfo.confidence++;
                            tempInfo.sampleLength = newSampleLength;
                            intervalInfos.set(j, tempInfo);
                            
                            //remove element i
                            intervalInfos.remove(i);
                            
                        }
                    }
                }
            }
        }
    }
    
    float tempo = 130.f;
    
    
    //eliminate tempo doubles
    //find all tempos and put in range
    for (int i = 0; i < intervalInfos.size(); i++) {
        float tempTempo = getTempo(intervalInfos[i].sampleLength);
        IntervalInfo tempInfo = intervalInfos[i];
        tempInfo.tempoVal = putTempoInRange(tempTempo);
        intervalInfos.set(i, tempInfo);
    }
    
    //make a copy of the interval infos array and eliminate tempo
    //doubles
    Array<IntervalInfo> infoCopy;
    infoCopy = intervalInfos;
    
    std::cout << "Ungrouped Confidences: ";
    for (int i = 0; i < infoCopy.size(); i++) {
        std::cout << infoCopy[i].confidence << ", ";
    }
    std::cout << "\n";
    
    for (int i = infoCopy.size() - 1; i >= 0; i--) {
        if (i < infoCopy.size()) {
            bool matched = false;
            for (int j = 0; j < infoCopy.size(); j++) {
                if (j != i && matched == false) {
                    //if tempi are close remove 1, adding confidences to the other
                    if (tempiAreClose(infoCopy[i].tempoVal, infoCopy[j].tempoVal)) {
                        matched = true;
                        int newConfidence = infoCopy[i].confidence + infoCopy[j].confidence;
                        
                        //add confidence from i to j
                        IntervalInfo tempInfo = infoCopy[j];
                        tempInfo.confidence = newConfidence;
                        infoCopy.set(j, tempInfo);
                        
                        //remove i
                        infoCopy.remove(i);
                    }
                }
            }
        }
    }
    
    //sort again
    infoCopy = sortIntervalInfos(infoCopy);
    
    
    //check again for clear winner
    if (infoCopy[0].confidence > infoCopy[1].confidence) {
        std::cout << "Clear Winner - 2nd Attempt\n";
        tempo = infoCopy[0].tempoVal;
    }
    else
    {
        //if no clear winner...
        
        std::cout << "Unreliable Result\n";
        
        //assign first interval as tempo indicator
        tempo = infoCopy[0].tempoVal;
    }
    
    
    updateLoopSampleTarget(tempo);
    
    //check listener exists
    if (listener != nullptr)
        listener->tempoUpdated(tempo);
    
    
    
}

bool BeatDetectorB::sampleValuesAreClose(int val1, int val2){
    
    //error percentage
    float errorAllowance = 0.2;
    bool valsAreClose = false;
    int largestVal = val1;
    
    //find larger of 2 values
    if (val2 > largestVal)
        largestVal = val2;
    
    //samples are 'close' if within error percentage value of largest value
    if ((abs(val1 - val2)) < (largestVal * errorAllowance)) {
        valsAreClose = true;
    }
    
    return valsAreClose;
}

Array<IntervalInfo> BeatDetectorB::sortIntervalInfos(Array<IntervalInfo> arrayToSort){
    
    std::cout << "Unsorted Confidences: ";
    for (int i = 0; i < arrayToSort.size(); i++) {
        std::cout << arrayToSort[i].confidence << ", ";
    }
    std::cout << "\n";
    
    
    //sort the interval array by confidence values
    int size = arrayToSort.size();
    
    for (int n = 1; n < size - 1; n++) {
        
        for (int i = size - n; i > 0; i--) {
            
            if (arrayToSort[i].confidence > arrayToSort[i - 1].confidence) {
                arrayToSort.swap(i, i - 1);
            }
        }
    }
    
    std::cout << "Sorted Confidences: ";
    for (int i = 0; i < arrayToSort.size(); i++) {
        std::cout << arrayToSort[i].confidence << ", ";
    }
    std::cout << "\n";
    
    return arrayToSort;
}

float BeatDetectorB::getTempo(int sampleInterval){
    
    //assume for now that SR = 44100 and sample Interval represents 1 beat
    //tempo = samples in 1 min / samples in 1 beat
    float tempo = (44100.0 * 60.0) / sampleInterval;
    
    return tempo;
}