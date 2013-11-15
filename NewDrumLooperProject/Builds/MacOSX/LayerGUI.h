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

class LayerGUI : public Component
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
    
    LayerGUI(int newLayerIndex);
    
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
    
    void setMuted(float shouldBeMuted);
    
    
    
private:
    
    int layerIndex;
    bool isSelected;
    bool isMuted;
    float gain;
    
    //pointer to listener
    Listener* listener;
};


#endif /* defined(__DrumLooper__LayerGUI__) */
