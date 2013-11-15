//
//  ModeButtons.h
//  DrumLooper
//
//  Created by Gareth Rendle on 08/11/2013.
//
//

#ifndef __DrumLooper__ModeButtons__
#define __DrumLooper__ModeButtons__

#include <iostream>
#include "../JuceLibraryCode/JuceHeader.h"

class ModeButtons : public Button::Listener,
public Component
{
    
public:
    
    class Listener{
    public:
        
        
        virtual ~Listener() {}
        
        virtual void newModeSelected(int modeIndex) = 0;
        
    };
    
    ModeButtons();
    ~ModeButtons();
    //ComponentCallbacks============================================================
	void resized();
	void paint (Graphics &g);
    //button callback====================================
    void buttonClicked(Button* button);
    void addListener(Listener* newListener);
    void setEnabled(bool shouldBeEnabled);
    
private:
    
    //void toggleEnabled();
    
    OwnedArray<Label> labels;
    OwnedArray<ToggleButton> buttons;
    
    Listener* listener;
    
    //bool enabled;
};

#endif /* defined(__DrumLooper__ModeButtons__) */
