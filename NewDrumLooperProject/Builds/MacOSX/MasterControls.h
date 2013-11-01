//
//  MasterControls.h
//  DrumLooper
//
//  Created by Gareth Rendle on 01/11/2013.
//
//

#ifndef __DrumLooper__MasterControls__
#define __DrumLooper__MasterControls__

#include "../JuceLibraryCode/JuceHeader.h"

class MasterControls  :     public Component,
                            public Slider::Listener
{
public:
    MasterControls();
    ~MasterControls();
    
    //ComponentCallbacks============================================================
	void resized();
	void paint (Graphics &g);
    
    void setGain(const float newGain);
    
    float getGain() const;
    
    float processSample(float input);
    
    //SliderCallbacks===============================================================
    void sliderValueChanged (Slider* slider);
    
private:
    Slider gainSlider;
    
    float gain;
    
    CriticalSection sharedMemory;
};

#endif /* defined(__DrumLooper__MasterControls__) */
