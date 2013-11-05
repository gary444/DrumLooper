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
    
    LayerGUI();
    
    ~LayerGUI();

    //ComponentCallbacks============================================================
	void resized();
	void paint (Graphics &g);
    
private:
    
    int layerId;
};


#endif /* defined(__DrumLooper__LayerGUI__) */
