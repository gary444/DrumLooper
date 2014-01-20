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
#include "ClearAllButton.h"
#include "ClearLayerButton.h"
#include "ToStartButton.h"
#include "AlternateLoopRecordButton.h"
#include "LayerGUI.h"
#include "CustomAudioThumbnail.h"


class LooperGUI :   public Component,
public Button::Listener,
public Thread,
public Slider::Listener,
public LayerGUI::Listener,
public Label::Listener,
public KeyListener
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
         
         //called when a layer's gain is changed
         virtual void layerPanChanged(const int layerIndex, const float newPanPosition) = 0;
         
         //called when a layer is muted or unmuted
         virtual void layerMuteToggled(const int layerIndexToggled, bool shouldBeMuted) = 0;
         
         //called when a certain layer should be deleted
         virtual void deleteLayer(int layerIndex) = 0;
         
         //called when all layers should be deleted.
         virtual void deleteAllLayers() = 0;
         
         //set position to 0
         virtual void setReaderToZero() = 0;
         
         //set alternate cycle record option
         virtual void setAlternateLoopRec(bool shouldBeOn) = 0;
         
         //virtual void tick() = 0;
         
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
    
    int getSelectedLayerIndex() const;
    
    void setLoopSampleLength(const int newLength);
    
    void setTransportUpdateStatus(bool shouldUpdate, float relativePosition, bool countingIn);
    
    void updateTriggerFunction(String newFunction);
    
    //Thread Callback===============================================================
	void run();
    
    //SliderCallback===============================================================
    void sliderValueChanged (Slider* slider);
    
    //mouse callbacks
    void mouseDown(const MouseEvent &event);
    
    //layerGUI listener callbacks
    void selected(LayerGUI* layerGUI);
    
    void shouldUpdatePlayState();
    
    void addLayer(CustomAudioThumbnail thumbnailToAdd);
    void deleteLayer(int layerIndex);
    void deleteAllLayers();
    
    void setThreadState (bool shouldBeRunning);
    
    void cancelAlternateLoopRec();
    
    Atomic<int> recordCycle;
    
    //key listener callback
    bool keyPressed (const KeyPress &key, Component *originatingComponent);
    
    
private:
    
    PlayButton playButton;
    RecordButton recordButton;
    Slider gainSlider;
    Label gainLabel;
    Slider panSlider;
    Label panLabel;
    MuteButton muteButton;
    Label selectedLabel;
    Label selecterLabel;
    ClearAllButton clearAllButton;
    ClearLayerButton clearLayerButton;
    ToStartButton toStartButton;
    AlternateLoopRecordButton loopRecButton;
    Slider scaleSlider;
    Label scaleLabel;

    OwnedArray<LayerGUI> layerIcons;
    Array<float> gainValues;
    Array<float> panValues;
    Array<bool> muteValues;
    //test button
    //TextButton testButton;
    
    //float gainValues[8];
    
    CriticalSection sharedMemory;
    
    //pointer to listener
    Listener* listener;
    
    //int noOfLayers;
    int selectedLayerIndex;
    //int playPosition;
    Atomic<int> recordState;
    Atomic<int> playState;
    Atomic<int> countIn;
    Atomic<int> updateState;
    Atomic<int> updatePlayState;
    Atomic<float> transportPosition;
    int loopSampleLength;
    
    String triggerFunction;
    
    
    //layout variables
    static const int TOP_CORNER_X = 0;
    static const int TOP_CORNER_Y = 100;
    static const int LAYER_WIDTH = 400;
    static const int LAYER_HEIGHT = 20;
    static const int CORNER_SIZE = 3;
    static const int GAP_BETWEEN_LAYERS = 10;
    static const int TIME_DISPLAY_WIDTH = 400;
    static const int TIME_DISPLAY_HEIGHT = 240;
};

#endif /* defined(__DrumLooper__LooperGUI__) */
