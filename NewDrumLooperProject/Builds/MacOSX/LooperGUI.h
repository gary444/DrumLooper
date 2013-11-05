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



class LooperGUI :   public Component,
public Button::Listener,
public Thread,
public Slider::Listener
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
         virtual void layerGainChanged(const int layerNumber, float newGain) = 0;
         
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
    
    //Thread Callback===============================================================
	void run();
    
    //SliderCallback===============================================================
    void sliderValueChanged (Slider* slider);
    
    //mouse callbacks
    void mouseDown(const MouseEvent &event);
    
    
    void addLayer();
    
    void setThreadState (bool shouldBeRunning);
    
private:
    
    PlayButton playButton;
    RecordButton recordButton;
    //test button
    TextButton testButton;
    Slider gainSlider;
    Label gainLabel;
    
    float gainValues[8];
    
    CriticalSection sharedMemory;
    
    //pointer to looper
    //Looper* looper;
    Listener* listener;
    
    //layout variables
    int topCornerX;
    int topCornerY;
    int layerWidth;
    int layerHeight;
    int cornerSize;
    int gapBetweenLayers;
    int timeDisplayWidth;
    int timeDisplayHeight;
    
    int noOfLayers;
    int selectedLayer;
    int playPosition;
    Atomic<int> recordState;
    Atomic<int> playState;
    //MouseListener mouseListener;
};

#endif /* defined(__DrumLooper__LooperGUI__) */
