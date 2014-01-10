//
//  LayerGUI.h
//  DrumLooper
//
//  Created by Gareth Rendle on 05/11/2013.
//
//

#ifndef __DrumLooper__LayerGUI__
#define __DrumLooper__LayerGUI__

#include <iostream>
#include "../JuceLibraryCode/JuceHeader.h"
#include "CustomAudioThumbnail.h"

class LayerGUI : public Component,
public SettableTooltipClient
{
    
public:
    
    //listener for layer GUI
    class Listener
    {
    public:
        
        virtual ~Listener() {}
        
        virtual void selected(LayerGUI* layerGUI) = 0;
        
    };
    
    LayerGUI();
    
    LayerGUI(int newLayerIndex, CustomAudioThumbnail newThumbnailInfo);
    
    ~LayerGUI();
    
    void addListener(Listener* newListener);

    //ComponentCallbacks============================================================
	void resized();
	void paint (Graphics &g);
    
    //mouse callbacks
    void mouseDown(const MouseEvent &event);
    
    void setLayerIndex(int newIndex);
    
    int getLayerIndex();
    
    void setSelected(bool shouldBeSelected);
    
    void setGain(float newGain);
    
    void setPan(float newPan);
    
    void setMuted(float shouldBeMuted);
    
    void setScale(float newScale);
    
    
    
private:
    
    int layerIndex;
    bool isSelected;
    bool isMuted;
    bool gotThumbnailInfo;
    float gain;
    float pan;
    float scale;
    
    //pointer to listener
    Listener* listener;
    CustomAudioThumbnail thumbnailInfo;
};


#endif /* defined(__DrumLooper__LayerGUI__) */
