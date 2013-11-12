//
//  Meter.h
//  DrumLooper
//
//  Created by Gareth Rendle on 01/11/2013.
//
//

#ifndef __DrumLooper__Meter__
#define __DrumLooper__Meter__

#include "../JuceLibraryCode/JuceHeader.h"

class Meter : public Component
{
    
    
public:
    Meter();
    ~Meter();
    
    //ComponentCallbacks============================================================
	void resized();
	void paint (Graphics &g);
    
    void process(const float inputValue);
    
    void setMeterNumber(const int newNumber);
    
private:
    //visible components
    //ScopedPointer<Slider> meterSlider;
    Slider meterSlider;
    Label meterLabel;
    //ScopedPointer<Label> meterLabel;
    
    int meterNumber;
    
    int measuredItems;
    int measuredLength;
    float maxValue;
    float oldMaxValue;
};
#endif /* defined(__DrumLooper__Meter__) */
