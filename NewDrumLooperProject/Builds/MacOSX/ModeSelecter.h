//
//  ModeSelecter.h
//  DrumLooper
//
//  Created by Gareth Rendle on 08/11/2013.
//
//

#ifndef __DrumLooper__ModeSelecter__
#define __DrumLooper__ModeSelecter__

#include <iostream>
#include "../JuceLibraryCode/JuceHeader.h"

#include "ModeButtons.h"

#ifndef __DrumLooper__ModeInfo__
#define __DrumLooper__ModeInfo__

//Mode Info class - just to describe mode operation to user
class ModeInfo : public Component{
public:
    ModeInfo() {
        String s;
        s << "1: Manually start and end loop using drum trigger pad. \n\n 2: Set tempo and play to metronome.\n\n 3: Beat Detection";
        text = new Label;
        text->setEditable(false);
        text->setText(s, dontSendNotification);
        text->setColour(Label::textColourId, Colours::lightgrey);
        addAndMakeVisible(text);
    };
    ~ModeInfo() {text = nullptr;};
    void resized(){text->setBounds(0, 0, getWidth(), getHeight());};
private:
    ScopedPointer<Label> text;
};

#endif /* defined(__DrumLooper__ModeInfo__) */






class ModeSelecter :  public Component,
ModeButtons::Listener
{
public:
    
    class Listener{
    public:
        
        virtual ~Listener() {}
        
        virtual void newModeSelected(int newModeIndex) = 0;
        
    };
    
    
    ModeSelecter();
    ~ModeSelecter();
    
    
    //ComponentCallbacks============================================================
	void resized();
	//void paint (Graphics &g);
    
    void addListener(Listener* newListener);
    void newModeSelected(int modeIndex);
    void setEnabled(bool shouldBeEnabled);
    
private:
    ScopedPointer<TabbedComponent> tabbedComponent;
    Listener* listener;
    
    
};

#endif /* defined(__DrumLooper__ModeSelecter__) */

