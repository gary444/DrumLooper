//
//  ManualLoopControl.h
//  sdaAssignment
//
//  Created by Gareth Rendle on 15/02/2013.
//
//

#ifndef __DrumLooper__ManualLoopControl__
#define __DrumLooper__ManualLoopControl__

#include <iostream>
#include "../JuceLibraryCode/JuceHeader.h"

/**
Class for allowing the user to define loop length
 */

class ManualLoopControl :   public Component,
                            public Slider::Listener,
                            public Button::Listener

{
public:
    
    class Listener{
    public:
        virtual ~Listener() {}
        virtual void tempoValueChanged(const float newTempo) = 0;
        virtual void numberOfBeatsChanged(const int newNumberOfBeats) = 0;
        virtual void countInChanged(const int newNumberOfBeats) = 0;
        virtual void tapTempoChanged(const bool shouldTapTempo) = 0;
        virtual void metroToggled(const bool shouldBeOn) = 0;
        
    };
    /**
     Constructor
     */
    ManualLoopControl();

    /**
     Destructor
     */
    ~ManualLoopControl();
    
    //Accessors=====================================================================
    
    /**
     returns the current manually selected loop length
     */
    //int getLoopLength() const;
    
    /**
     returns true if ManualLoopControl is enabled
     */
    //bool isEnabled() const;
    
    
    //Mutators=====================================================================
    
    void addListener(Listener* newListener);
    
    void setModeIndex(int newModeIndex);
    
    void setEnabled(bool shouldBeEnabled);
    
    void setTempoValue(float newTempo);
    
    void setTapTempo(bool shouldBeOn);

    //ComponentCallbacks============================================================
	void resized();
	void paint (Graphics &g);
    
    //SliderCallbacks===============================================================
    void sliderValueChanged (Slider* slider);
    
    //ButtonCallbacks===============================================================
    void buttonClicked (Button* button);
    
private:
    
    //bool enabled;
    //int loopLength;
//    float tempo;
//    int beats;
    
    Listener* listener;
    
    Slider tempoSlider;
    Label bpmLabel;
    Slider beatNumberSlider;
    Label beatLabel;
    Slider countInSlider;
    Label countInLabel;
    ToggleButton tapTempoButton;
    Label tapTempoLabel;
    ToggleButton metroOnOffButton;
    Label metroOnOffLabel;
    
    //Shared Memory Lock
    CriticalSection sharedMemory;//needed? are all operations taking place in message thread?
    
};

#endif /* defined(__sdaAssignment__ManualLoopControl__) */
