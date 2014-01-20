//
//  BeatDetector.cpp
//  sdaFileEffect
//
//  Created by Gary Rendle on 13/12/2013.
//
//

#include "BeatDetector.h"

BeatDetector::BeatDetector(){
    
    listener = nullptr;
    
    agent1.clear();
    agent2.clear();
    agent3.clear();
    
    
    //fill tested note value array
    testedNoteValues.clear();
    //testedNoteValues.add(1.0 / 6.0);
    //testedNoteValues.add(0.25);
    //testedNoteValues.add(1.0 / 3.0);
    //testedNoteValues.add(0.5);
    //testedNoteValues.add(2.0 / 3.0);
    //testedNoteValues.add(0.75);
    //testedNoteValues.add(5.0 / 6.0);
    testedNoteValues.add(1.0);
    //testedNoteValues.add(7.0 / 6.0);
    //testedNoteValues.add(1.25);
    //testedNoteValues.add(4.0 / 3.0);
    //testedNoteValues.add(1.5);
    //testedNoteValues.add(5.0 / 3.0);
    //testedNoteValues.add(1.75);
    //testedNoteValues.add(11.0 / 6.0);
    //testedNoteValues.add(2.0);
    //testedNoteValues.add(2.5);
    //testedNoteValues.add(3.0);
    
}

BeatDetector::~BeatDetector(){
    
    listener = nullptr;
}


void BeatDetector::setListener(Listener* newListener){
    
    listener = newListener;
}

void BeatDetector::process(float input, int channel){
    
    
    //create mono input from pairs of input samples with
    // different channel numbers
    float monoInput;
    if (channel == 0) {
        tempLChannelData = fabsf(input);
        
        sampleNumber++;
        
        //increment counter if necessary
        if (intervalCounting)
            intervalCount++;
        if (interval2Counting)
            interval2Count++;
        if (interval3Counting)
            interval3Count++;
    }
    else
    {
        monoInput = (tempLChannelData + fabsf(input)) * 0.5;
        tempLChannelData = 0.f;
    }
    
    //only process if recieving non-noise values
    if (waitingForFirstHit.get() == false || monoInput > 0.001) {
        
        //check if highest input value
        if (monoInput > highestInputValue){
            highestInputValue = monoInput;
            
            if (hitCount > 5) {
                //std::cout << "highest input value = " << highestInputValue << "\n";
            }
        }
        
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
                //if (showingHits.get())
                //    std::cout << "hit heard : " << hitCount << "\n";
                
                hitCount++;
                
                //call process peak function (after hit count is updated!)
                processPeak();
                
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

void BeatDetector::reset(){
    
    peakDetector.reset();
    
    agent1.clear();
    agent2.clear();
    agent3.clear();
    hitCount = 0;
    intervalCount = 0;
    interval2Count = 0;
    interval3Count = 0;
    intervalCounting = false;
    interval2Counting = false;
    interval3Counting = false;
    waitingForFirstHit = true;
    waitingForLastHit = false;
    sampleNumber = 0;
    
    
    loopSampleTarget = 90 * sampleRate;//start at 90 sec
}



void BeatDetector::processPeak(){
    
    //std::cout << "Process Peak called\n";
    
    //if first peak, detector will not be counting
    if (hitCount == 1) {
        //start counting
        intervalCounting = true;
        interval2Counting = true;
        
        //start loop
        if (listener != nullptr){
            listener->setLoopStartPoint();
            sampleNumber = 0;
        }
    }
    //otherwise process the peak as normal
    else {
        
        //if this is the second hit
        if (hitCount == 2) {
            
            //fill agent 1 with states
            for (int i = 0; i < testedNoteValues.size(); i++) {
                
                //create state
                DetectionState* newState = new DetectionState;
                //add interval and note values
                newState->setInterval(intervalCount);
                newState->setNoteValue(testedNoteValues[i]);
                //add to array
                agent1.add(newState);
                
                
            }
            //std::cout << "agent 1 filled\n";
            
            //start agent 3 count
            interval3Counting = true;
        }
        else if (hitCount == 3){
            
            //fill agent 2 with states
            for (int i = 0; i < testedNoteValues.size(); i++) {
                
                //create state
                DetectionState* newState = new DetectionState;
                //add interval and note values
                newState->setInterval(interval2Count);
                newState->setNoteValue(testedNoteValues[i]);
                //add to array
                agent2.add(newState);
                
                
            }
            //std::cout << "agent 2 filled\n";
            
            //fill agent 3 with states
            for (int i = 0; i < testedNoteValues.size(); i++) {
                
                //create state
                DetectionState* newState = new DetectionState;
                //add interval and note values
                newState->setInterval(interval3Count);
                newState->setNoteValue(testedNoteValues[i]);
                //add to array
                agent3.add(newState);
            }
            //std::cout << "agent 3 filled\n";
            
            //test intervals in agent 1
            for (int i = 0; i < agent1.size(); i++) {
                agent1[i]->testInterval(intervalCount);
            }
            
            //interval 2 count no longer needed, reset and turn off
            interval2Count = 0;
            interval2Counting = false;
            interval3Count = 0;
            interval3Counting = false;
        }
        else if (hitCount > 3){
            
            //test intervals in all agents
            for (int i = 0; i < agent1.size(); i++) {
                agent1[i]->testInterval(intervalCount);
            }
            
            for (int i = 0; i < agent2.size(); i++) {
                agent2[i]->testInterval(intervalCount);
            }
            for (int i = 0; i < agent3.size(); i++) {
                agent3[i]->testInterval(intervalCount);
            }
        }
        
        //reset interval number
        intervalCount = 0;
    }
}

void BeatDetector::reportMostLikelyTempo(){
    
    //find most confident tempo
    Array<int> highestConfidenceIndexes1;
    Array<int> highestConfidenceIndexes2;
    Array<int> highestConfidenceIndexes3;
    highestConfidenceIndexes1.clear();
    highestConfidenceIndexes2.clear();
    highestConfidenceIndexes3.clear();
    
    highestConfidenceIndexes1 = sortAgent(agent1);
    highestConfidenceIndexes2 = sortAgent(agent2);
    highestConfidenceIndexes3 = sortAgent(agent3);
    
    //create arrays to hold likely tempos and respective confidence values
    Array<float> likelyTempi;
    Array<int> likelyTempiConfidences;
    likelyTempi.clear();
    likelyTempiConfidences.clear();
    
    //fill arrays from agents using highest confidence info
    for (int i = 0; i < highestConfidenceIndexes1.size(); i++) {
        float newTempo = getTempo(agent1, highestConfidenceIndexes1[i]);
        int newConfidence = agent1[highestConfidenceIndexes1[i]]->getConfidence();
        likelyTempi.add(newTempo);
        likelyTempiConfidences.add(newConfidence);
    }
    for (int i = 0; i < highestConfidenceIndexes2.size(); i++) {
        float newTempo = getTempo(agent2, highestConfidenceIndexes2[i]);
        int newConfidence = agent2[highestConfidenceIndexes2[i]]->getConfidence();
        likelyTempi.add(newTempo);
        likelyTempiConfidences.add(newConfidence);
    }
    for (int i = 0; i < highestConfidenceIndexes3.size(); i++) {
        float newTempo = getTempo(agent3, highestConfidenceIndexes2[i]);
        int newConfidence = agent3[highestConfidenceIndexes2[i]]->getConfidence();
        likelyTempi.add(newTempo);
        likelyTempiConfidences.add(newConfidence);
    }
    
    //print tempi and confidence for testing
    String s;
    for (int i = 0; i < likelyTempi.size(); i++) {
        s << likelyTempi[i] << " confidence = " << likelyTempiConfidences[i] << " | ";
    }
    s << "\n";
    std::cout << s;
    
    //analyse confidence values to determine a most confident tempo (if present)
    Array<int> mostConfidentTempoIndexes;
    mostConfidentTempoIndexes.clear();
    for (int i = 0; i < likelyTempiConfidences.size(); i++) {
        if (i == 0) {
            mostConfidentTempoIndexes.add(0);
        }
        else {
            if (likelyTempiConfidences[i] > likelyTempiConfidences[mostConfidentTempoIndexes[0]]) {
                mostConfidentTempoIndexes.clear();
                mostConfidentTempoIndexes.add(i);
            }
            else if (likelyTempiConfidences[i] == likelyTempiConfidences[mostConfidentTempoIndexes[0]]) {
                
                mostConfidentTempoIndexes.add(i);
            }
        }
    }
    
    //initialise tempo as 130. not as 0 as this will be changed as tempo is 'put in range'
    float tempo = 130.f;
    
    //if there is one clear 'winner', assign that as the tempo
    if (mostConfidentTempoIndexes.size() == 1) {
        tempo = likelyTempi[mostConfidentTempoIndexes[0]];
        std::cout << "Clear Winner\n";
    }
    else {
        //check if tempi are actually same but out by factor of two
        for (int i = 0; i < likelyTempi.size(); i++) {
            //put all tempos in range
            likelyTempi.set(i, putTempoInRange(likelyTempi[i]));
        }
        for (int i = 0; i < likelyTempi.size(); i++) {
            if (i != 0) {
                for (int j = 0; j < likelyTempi.size(); j++) {
                    //set tempo value to 0 if it matches another one
                    bool matched = false;
                    if (j != i && matched == false) {
                        if (tempiAreClose(likelyTempi[i], likelyTempi[j])) {
                            likelyTempi.set(i, 0);
                            matched = true;
                        }
                    }
                }
            }
        }
        
        //remove zero values
        likelyTempi.removeAllInstancesOf(0);
        
        //check if there is now a clear winner
        if (likelyTempi.size() == 1) {
            //assign
            tempo = likelyTempi[0];
            std::cout << "Clear Winner (2nd Attempt)\n";
        }
        //if not find assume that first agent provdes better result
        else {
            std::cout << "Unreliable Result\n";
            tempo = likelyTempi[0];
            //std::cout << "tempo = " << tempo << "\n";
            
        }
    }

    //ensure tempo is in range
    tempo = putTempoInRange(tempo);
    
    updateLoopSampleTarget(tempo);
    
    if (listener != nullptr) {
        listener->tempoUpdated(tempo);
    }
}

Array<int> BeatDetector::sortAgent(Array<DetectionState*> agentToSort){
    
    Array<int> highestConfidenceIndexes;
    highestConfidenceIndexes.clear();
    
    //sort which states have the highest confidence
    for (int i = 0; i < agentToSort.size(); i++) {
        
        if (i == 0) {
            highestConfidenceIndexes.add(i);
        }
        else {
            
            if (agentToSort[i]->getConfidence() > agentToSort[highestConfidenceIndexes[0]]->getConfidence()) {
                
                highestConfidenceIndexes.clear();
                highestConfidenceIndexes.add(i);
                
            }
            else if (agentToSort[i]->getConfidence() == agentToSort[highestConfidenceIndexes[0]]->getConfidence()){
                
                highestConfidenceIndexes.add(i);
            }
        }
    }
    
    return highestConfidenceIndexes;
    
}


float BeatDetector::getTempo(Array<DetectionState*> hostAgent, int index){
    
    float tempo;
    
    //samples per beat = interval / note value
    float samplesPerBeat = hostAgent[index]->getInterval() / hostAgent[index]->getNoteValue();
    
    
    //tempo = samples in 1 min / samples in 1 beat
    tempo = (sampleRate * 60.0) / samplesPerBeat;
    
    return tempo;
    
}



void BeatDetector::printConfidences(){
    
    std::cout << "Confidences (agent 1):\n";
    
    for (int i = 0; i < agent1.size(); i++) {
        std::cout << "For note value: " << testedNoteValues[i] << ", confidence = " << agent1[i]->getConfidence() << "\n";
    }
    
    std::cout << "Confidences (agent 2):\n";
    
    for (int i = 0; i < agent2.size(); i++) {
        std::cout << "For note value: " << testedNoteValues[i] << ", confidence = " << agent2[i]->getConfidence() << "\n";
    }
    
    std::cout << "Confidences (agent 3):\n";
    
    for (int i = 0; i < agent3.size(); i++) {
        std::cout << "For note value: " << testedNoteValues[i] << ", confidence = " << agent3[i]->getConfidence() << "\n";
    }
    
}

