//
//  LooperGUI.h
//  DrumLooper
//
//  Created by Gareth Rendle on 05/11/2013.
//
//

#ifndef __DrumLooper__LooperGUI__
#define __DrumLooper__LooperGUI__

#include <iostream>
#include "../JuceLibraryCode/JuceHeader.h"
#include "RecordButton.h"
#include "PlayButton.h"
#include "MuteButton.h"
#include "LayerGUI.h"



class LooperGUI :   public Component,
public Button::Listener,
public Thread,
public Slider::Listener,
public LayerGUI::Listener,
public Label::Listener
//public MouseListener
{
public:
    
     //add listener for looperGUI
     class Listener
     {
     public:
     
         // Destructor
     
         virtual ~Listener() {}
     
         //Called when start button toggled
         virtual void playButtonToggled() = 0;
         
         //Called when record button toggled
         virtual void recordButtonToggled() = 0;
         
         //called when the gain of a layer is changed
         virtual void layerGainChanged(const int layerIndex, float newGain) = 0;
         
         //called when a layer is muted or unmuted
         virtual void layerMuteToggled(const int layerIndexToggled, bool shouldBeMuted) = 0;
         
     };
     
    
    LooperGUI();
    ~LooperGUI();
    
    
    //set listener
    void setListener(Listener* newListener);
    
    //ComponentCallbacks============================================================
	void resized();
	void paint (Graphics &g);
    
    //Button Listener
    void buttonClicked (Button* button);
    
    //label listener
    void labelTextChanged (Label *labelThatHasChanged);
    
    /**
     Starts or stops playback of the looper
     */
    void setPlayState (const bool newState);
    
    /**
     Gets the current playback state of the looper
     */
    bool getPlayState () const;
    
    /**
     Sets/unsets the record state of the looper
     */
    void setRecordState (const bool newState);
    
    /**
     Gets the current record state of the looper
     */
    bool getRecordState () const;
    
    void setLoopSampleLength(const int newLength);
    
    void setTransportRunningState(bool shouldBeRunning);
    
    //Thread Callback===============================================================
	void run();
    
    //SliderCallback===============================================================
    void sliderValueChanged (Slider* slider);
    
    //mouse callbacks
    void mouseDown(const MouseEvent &event);
    
    //layerGUI listener callbacks
    void selected(LayerGUI* layerGUI);
    
    
    void addLayer();
    
    void setThreadState (bool shouldBeRunning);
    
private:
    
    PlayButton playButton;
    RecordButton recordButton;
    Slider gainSlider;
    Label gainLabel;
    MuteButton muteButton;
    Label selectedLabel;
    Label selecterLabel;

    OwnedArray<LayerGUI> layerIcons;
    Array<float> gainValues;
    Array<bool> muteValues;
    //test button
    TextButton testButton;
    
    //float gainValues[8];
    
    CriticalSection sharedMemory;
    
    //pointer to listener
    Listener* listener;
    
    int noOfLayers;
    int selectedLayerIndex;
    int playPosition;
    Atomic<int> recordState;
    Atomic<int> playState;
    Atomic<int> transportState;
    int loopSampleLength;
};

#endif /* defined(__DrumLooper__LooperGUI__) */
