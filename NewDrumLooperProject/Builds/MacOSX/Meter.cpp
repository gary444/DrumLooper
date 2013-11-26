//
//  Meter.cpp
//  DrumLooper
//
//  Created by Gareth Rendle on 01/11/2013.
//
//

#include "Meter.h"

Meter::Meter(){
    
    measuredLength = static_cast<int>(44100 * 0.02);
    measuredItems = 0;
    maxValue = 0.f;
    oldMaxValue = 0.f;
    meterNumber = 0;
    
    meterSlider.setSliderStyle(Slider::LinearBar);
    meterSlider.setTextBoxIsEditable(false);
    meterSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    meterSlider.setColour(Slider::backgroundColourId, Colours::whitesmoke);
    meterSlider.setValue(0.0);
    addAndMakeVisible(&meterSlider);
    
    meterLabel.setEditable(false);
    meterLabel.setText("0", dontSendNotification);
    addAndMakeVisible(&meterLabel);
}
Meter::~Meter(){
    
    std::cout << "meter dtor\n";
}

//ComponentCallbacks============================================================
void Meter::resized(){
    
    meterLabel.setBounds(0, 0, 30, 20);
    meterSlider.setBounds(35, 0, 80, 10);
}
void Meter::paint(Graphics &g){
    
}

void Meter::process(const float inputValue){
    
    float input = 0.f;
    float absInput = 0.f;
    
    
    
    // read left and right input samples
    input = inputValue;
    
    //find absolute value
    absInput = fabsf(input);
    
    //update peak values
    if (absInput > maxValue)
        maxValue = absInput;
    
    //update measured items
    measuredItems++;
    
    //if end of measure cycle, update meters and reset Peak values
    if (measuredItems == measuredLength)
    {
        //scale and shift
        //maxValue = (maxValue * 39.0) + 1.0;
        //log function
        //maxValue = log10f(maxValue) / log10(40.0);
        
        //gradual decay
        if (maxValue < oldMaxValue) {
            maxValue = (maxValue * 0.1) + (oldMaxValue * 0.9);
        }
        
        
        
        //this part courtesy of Julian Storer at http://www.juce.com/api/classMessageManagerLock.html
        MessageManagerLock mml (Thread::getCurrentThread());
        if (! mml.lockWasGained())
          return;
        //**problem here**//
        //meterSlider->setValue(maxValue, dontSendNotification);
        
        //record peak
        oldMaxValue = maxValue;
        
        //reset
        maxValue = measuredItems = 0;
    }
}

void Meter::setMeterNumber(const int newNumber){
    
    meterNumber = newNumber;
    
    String labelText;
    labelText << newNumber;
    meterLabel.setText(labelText, dontSendNotification);
}