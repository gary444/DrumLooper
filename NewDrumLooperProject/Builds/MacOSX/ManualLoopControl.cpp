//
//  ManualLoopControl.cpp
//  sdaAssignment
//
//  Created by Gareth Rendle on 15/02/2013.
//
//

#include "ManualLoopControl.h"

/**
 Constructor
 */
ManualLoopControl::ManualLoopControl()
{
    //loopLength = 0;
    //enabled = false;
    listener = nullptr;
    
    //tempo slider
    tempoSlider.setSliderStyle(Slider::IncDecButtons);
    tempoSlider.setRange(40.0, 210.0, 0.01);
    tempoSlider.setValue(100.0);
    tempoSlider.setTextBoxStyle(Slider::TextBoxRight, false, 80, 30);
    tempoSlider.setIncDecButtonsMode(Slider::incDecButtonsDraggable_Vertical);
    tempoSlider.setEnabled(false);
    tempoSlider.addListener(this);
    addAndMakeVisible(&tempoSlider);
    
    bpmLabel.setText("b.p.m.", dontSendNotification);
    bpmLabel.setEditable(false);
    addAndMakeVisible(&bpmLabel);
    
    //beat slider
    beatNumberSlider.setSliderStyle(Slider::IncDecButtons);
    beatNumberSlider.setRange(1, 64, 1);
    beatNumberSlider.setValue(8);
    beatNumberSlider.setTextBoxStyle(Slider::TextBoxRight, false, 80, 30);
    beatNumberSlider.setIncDecButtonsMode(Slider::incDecButtonsDraggable_Vertical);
    beatNumberSlider.setEnabled(false);
    beatNumberSlider.addListener(this);
    addAndMakeVisible(&beatNumberSlider);
    
    beatLabel.setText("Beats", dontSendNotification);
    beatLabel.setEditable(false);
    addAndMakeVisible(&beatLabel);
    
    //count in
    countInSlider.setSliderStyle(Slider::IncDecButtons);
    countInSlider.setRange(1, 16, 1);
    countInSlider.setValue(4);
    countInSlider.setTextBoxStyle(Slider::TextBoxRight, false, 80, 30);
    countInSlider.setIncDecButtonsMode(Slider::incDecButtonsDraggable_Vertical);
    countInSlider.setEnabled(false);
    countInSlider.addListener(this);
    addAndMakeVisible(&countInSlider);
    
    countInLabel.setText("Count In", dontSendNotification);
    countInLabel.setEditable(false);
    addAndMakeVisible(&countInLabel);
    
    //tap tempo button
    tapTempoButton.setEnabled(false);
    tapTempoButton.setToggleState(false, dontSendNotification);
    tapTempoButton.addListener(this);
    addAndMakeVisible(&tapTempoButton);
    
    tapTempoLabel.setText("Tap Tempo?", dontSendNotification);
    tapTempoLabel.setEditable(false);
    addAndMakeVisible(&tapTempoLabel);
    
    //metro on off button
    //metroOnOffButton.setEnabled(true);
    metroOnOffButton.setToggleState(true, dontSendNotification);
    metroOnOffButton.addListener(this);
    addAndMakeVisible(&metroOnOffButton);
    
    metroOnOffLabel.setText("Metro On/Off?", dontSendNotification);
    metroOnOffLabel.setEditable(false);
    addAndMakeVisible(&metroOnOffLabel);
}

/**
 Destructor
 */
ManualLoopControl::~ManualLoopControl()
{
    
}

//Accessors=====================================================================

///**
// returns the current manually selected loop length
// */
//int ManualLoopControl::getLoopLength() const
//{
//    sharedMemory.enter();
//    //int l = loopLength;
//    sharedMemory.exit();
//    
//    return l;
//}

/**
 returns true if ManualLoopControl is enabled
 */
//bool ManualLoopControl::isEnabled() const
//{
//    sharedMemory.enter();
//    bool e = enabled;
//    sharedMemory.exit();
//    
//    return e;
//}

//Mutators=====================================================================

void ManualLoopControl::addListener(Listener* newListener){
    
    listener = newListener;
}

/**
 toggle whether the manual loop control is enabled
 */
void ManualLoopControl::setEnabled(bool shouldBeEnabled)
{
    //enabled = shouldBeEnabled;
    
    if (shouldBeEnabled) {
        beatNumberSlider.setEnabled(true);
        tempoSlider.setEnabled(true);
        countInSlider.setEnabled(true);
        tapTempoButton.setEnabled(true);
    }
    else {
        beatNumberSlider.setEnabled(false);
        tempoSlider.setEnabled(false);
        countInSlider.setEnabled(false);
        tapTempoButton.setEnabled(false);
    }

}

void ManualLoopControl::setTempoValue(float newTempo){
    
    tempoSlider.setValue(newTempo);
}

//ComponentCallbacks============================================================
void ManualLoopControl::resized()
{
    tempoSlider.setBounds(0, 3, 100, 30);
    bpmLabel.setBounds(100, 3, 50, 30);
    beatNumberSlider.setBounds(0, 40, 100, 30);
    beatLabel.setBounds(100, 40, 70, 30);
    countInSlider.setBounds(0, 80, 100, 30);
    countInLabel.setBounds(100, 80, 70, 30);
    tapTempoButton.setBounds(0, 120, 30, 30);
    tapTempoLabel.setBounds(30, 120, 100, 30);
    metroOnOffButton.setBounds(0, 150, 30, 30);
    metroOnOffLabel.setBounds(30, 150, 100, 30);
}

void ManualLoopControl::paint (Graphics &g)
{
    int x = getWidth();
    int y = getHeight();
    
    g.setColour(Colours::whitesmoke);
    g.fillRect(0, 0, x, y);
    g.setColour(Colours::grey);
    g.drawRect(0, 0, x, y);
}



//SliderCallback================================================================
void ManualLoopControl::sliderValueChanged (Slider* slider)
{
    //pass info to listener (if not void)
    if (listener != nullptr) {
        
        if (slider == &tempoSlider){
            listener->tempoValueChanged(slider->getValue());
        }
        else if (slider == &beatNumberSlider){
            listener->numberOfBeatsChanged(slider->getValue());
        }
        else if (slider == &countInSlider){
            listener->countInChanged(slider->getValue());
        }
    }
    
    
}

//ButtonCallback================================================================
void ManualLoopControl::buttonClicked (Button* button)
{
    //pass info to listener (if not void)
    if (listener != nullptr) {
        
        if (button == &tapTempoButton) {
            listener->tapTempoChanged(button->getToggleState());
            
            countInSlider.setEnabled(!button->getToggleState());
        }
        else if (button == &metroOnOffButton){
            
            listener->metroToggled(button->getToggleState());
        }
    }
}