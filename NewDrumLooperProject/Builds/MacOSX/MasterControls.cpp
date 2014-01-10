//
//  MasterControls.cpp
//  DrumLooper
//
//  Created by Gareth Rendle on 01/11/2013.
//
//

#include "MasterControls.h"

MasterControls::MasterControls(){
    
    gainSlider.setSliderStyle(Slider::LinearVertical);
    gainSlider.setTextBoxStyle(Slider::NoTextBox, false, 40, 20);
    gainSlider.setRange(0.0, 1.0, 0.01);
    gainSlider.setValue(0.8);
    gainSlider.addListener(this);
    gainSlider.setColour(Slider::thumbColourId, Colours::deepskyblue);
    gainSlider.setTooltip("Adjust master volume");
    addAndMakeVisible(&gainSlider);
    
    //repaint();
}
MasterControls::~MasterControls(){
    
    
    //std::cout << "MasterControls dtor\n";
}

void MasterControls::resized(){
    
    gainSlider.setBounds(0, 0, 30, 80);
}
void MasterControls::paint(Graphics &g){
    
    g.setColour(Colours::lightgrey);
    g.drawSingleLineText("Master", 0, 90);
}

void MasterControls::setGain(const float newGain){
    
    sharedMemory.enter();
    gain = newGain;
    sharedMemory.exit();
}

float MasterControls::getGain() const{
    
    sharedMemory.enter();
    float g = gain;
    sharedMemory.exit();
    
    return g;
}

float MasterControls::processSample(float input){
    
    sharedMemory.enter();
    float out = input * gain;
    sharedMemory.exit();
    
    return out;
}

//SliderCallbacks===============================================================
void MasterControls::sliderValueChanged(Slider* slider){
    
    setGain(slider->getValue());
}