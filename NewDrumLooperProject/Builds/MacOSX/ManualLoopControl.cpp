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
    tempoSlider.setTooltip("Set Tempo for loop (mode 2 only)");
    tempoSlider.setSliderStyle(Slider::IncDecButtons);
    tempoSlider.setRange(40.0, 210.0, 0.01);
    tempoSlider.setValue(100.0);
    tempoSlider.setTextBoxStyle(Slider::TextBoxRight, false, 80, 30);
    tempoSlider.setIncDecButtonsMode(Slider::incDecButtonsDraggable_Vertical);
    tempoSlider.setEnabled(false);
    //tempoSlider.setColour(Slider::textBoxTextColourId, Colours::black);
    tempoSlider.setColour(Slider::textBoxBackgroundColourId, Colours::lightgrey);
    tempoSlider.addListener(this);
    addAndMakeVisible(&tempoSlider);
    
    bpmLabel.setText("b.p.m.", dontSendNotification);
    bpmLabel.setColour(Label::textColourId, Colours::lightgrey);
    bpmLabel.setEditable(false);
    addAndMakeVisible(&bpmLabel);
    
    //beat slider
    beatNumberSlider.setTooltip("Set number of beats in loop (mode 2/3)");
    beatNumberSlider.setSliderStyle(Slider::IncDecButtons);
    beatNumberSlider.setRange(1, 64, 1);
    beatNumberSlider.setValue(8);
    beatNumberSlider.setTextBoxStyle(Slider::TextBoxRight, false, 80, 30);
    beatNumberSlider.setIncDecButtonsMode(Slider::incDecButtonsDraggable_Vertical);
    beatNumberSlider.setColour(Slider::textBoxBackgroundColourId, Colours::lightgrey);
    beatNumberSlider.setEnabled(false);
    beatNumberSlider.addListener(this);
    addAndMakeVisible(&beatNumberSlider);
    
    beatLabel.setText("Beats", dontSendNotification);
    beatLabel.setColour(Label::textColourId, Colours::lightgrey);
    beatLabel.setEditable(false);
    addAndMakeVisible(&beatLabel);
    
    //count in
    countInSlider.setTooltip("Set length of count in (mode 2 only)");
    countInSlider.setSliderStyle(Slider::IncDecButtons);
    countInSlider.setRange(1, 16, 1);
    countInSlider.setValue(4);
    countInSlider.setTextBoxStyle(Slider::TextBoxRight, false, 80, 30);
    countInSlider.setIncDecButtonsMode(Slider::incDecButtonsDraggable_Vertical);
    countInSlider.setEnabled(false);
    countInSlider.setColour(Slider::textBoxBackgroundColourId, Colours::lightgrey);
    countInSlider.addListener(this);
    addAndMakeVisible(&countInSlider);
    
    countInLabel.setText("Count In", dontSendNotification);
    countInLabel.setColour(Label::textColourId, Colours::lightgrey);
    countInLabel.setEditable(false);
    addAndMakeVisible(&countInLabel);
    
    //tap tempo button
    tapTempoButton.setTooltip("Select to tap in tempo using trigger pad (mode 2 only)");
    tapTempoButton.setEnabled(false);
    tapTempoButton.setToggleState(false, dontSendNotification);
    tapTempoButton.addListener(this);
    addAndMakeVisible(&tapTempoButton);
    
    tapTempoLabel.setText("Tap Tempo?", dontSendNotification);
    tapTempoLabel.setEditable(false);
    tapTempoLabel.setColour(Label::textColourId, Colours::lightgrey);
    addAndMakeVisible(&tapTempoLabel);
    
    //metro on off button
    metroOnOffButton.setTooltip("Turn metronome on/off (mode 2 only)");
    metroOnOffButton.setToggleState(true, dontSendNotification);
    metroOnOffButton.addListener(this);
    metroOnOffButton.setEnabled(false);
    addAndMakeVisible(&metroOnOffButton);
    
    metroOnOffLabel.setText("Metro On/Off?", dontSendNotification);
    metroOnOffLabel.setEditable(false);
    metroOnOffLabel.setColour(Label::textColourId, Colours::lightgrey);
    addAndMakeVisible(&metroOnOffLabel);
    
    //end loop on hit option
    endLoopOnHitButton.setTooltip("End loop with a drum hit rather than automatically (mode 3)");
    endLoopOnHitButton.setToggleState(true, dontSendNotification);
    endLoopOnHitButton.addListener(this);
    endLoopOnHitButton.setEnabled(false);
    addAndMakeVisible(&endLoopOnHitButton);
    
    endLoopOnHitLabel.setText("End Loop On Hit?", dontSendNotification);
    endLoopOnHitLabel.setEditable(false);
    endLoopOnHitLabel.setColour(Label::textColourId, Colours::lightgrey);
    addAndMakeVisible(&endLoopOnHitLabel);
    
    
}

/**
 Destructor
 */
ManualLoopControl::~ManualLoopControl()
{
    
}

//Mutators=====================================================================

void ManualLoopControl::addListener(Listener* newListener){
    
    listener = newListener;
}

/**
 toggle whether the manual loop control is enabled
 */

void ManualLoopControl::setModeIndex(int newModeIndex){
    
    switch (newModeIndex) {
        case 0:
            beatNumberSlider.setEnabled(false);
            tempoSlider.setEnabled(false);
            countInSlider.setEnabled(false);
            tapTempoButton.setEnabled(false);
            metroOnOffButton.setEnabled(false);
            endLoopOnHitButton.setEnabled(false);
            break;
            
        case 1:
            beatNumberSlider.setEnabled(true);
            tempoSlider.setEnabled(true);
            countInSlider.setEnabled(true);
            tapTempoButton.setEnabled(true);
            metroOnOffButton.setEnabled(true);
            endLoopOnHitButton.setEnabled(false);
            break;
            
        case 2:
            beatNumberSlider.setEnabled(true);
            tempoSlider.setEnabled(false);
            countInSlider.setEnabled(false);
            tapTempoButton.setEnabled(false);
            metroOnOffButton.setEnabled(false);
            endLoopOnHitButton.setEnabled(true);
            break;
            
        default:
            break;
    }
}

void ManualLoopControl::setEnabled(bool shouldBeEnabled)
{
    //enabled = shouldBeEnabled;
    
    if (shouldBeEnabled) {
        beatNumberSlider.setEnabled(true);
        tempoSlider.setEnabled(true);
        countInSlider.setEnabled(true);
        tapTempoButton.setEnabled(true);
        endLoopOnHitButton.setEnabled(true);
    }
    else {
        beatNumberSlider.setEnabled(false);
        tempoSlider.setEnabled(false);
        countInSlider.setEnabled(false);
        tapTempoButton.setEnabled(false);
        endLoopOnHitButton.setEnabled(false);
    }

}

void ManualLoopControl::setTempoValue(float newTempo){
    
    tempoSlider.setValue(newTempo);
}

void ManualLoopControl::setTapTempo(bool shouldBeOn){
    
    tapTempoButton.setToggleState(shouldBeOn, dontSendNotification);
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
    endLoopOnHitButton.setBounds(0, 180, 30, 30);
    endLoopOnHitLabel.setBounds(30, 180, 130, 30);
}

void ManualLoopControl::paint (Graphics &g)
{
    int x = getWidth();
    int y = getHeight();
    
    
    g.setColour(Colours::grey.withAlpha(0.2f));
    //g.setColour(Colours::whitesmoke);
    g.fillRect(0, 0, x, y);
    g.setColour(Colours::deepskyblue);
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
            tempoSlider.setEnabled(!button->getToggleState());
        }
        else if (button == &metroOnOffButton){
            
            listener->metroToggled(button->getToggleState());
        }
        else if (button == &endLoopOnHitButton){
            
            listener->endLoopOnHitToggled(button->getToggleState());
        }
    }
}