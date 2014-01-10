//
//  SimplePeakDetector.h
//  DrumLooper
//
//  Created by Gareth Rendle on 18/11/2013.
//
//

#ifndef __DrumLooper__SimplePeakDetector__
#define __DrumLooper__SimplePeakDetector__

#include <iostream>
#include <math.h>

#include "PeakDetector.h"

//class that detects peaks. based on trigger response class but has a detect function that returns true/false if a peak is found for quick processing.


class SimplePeakDetector : public PeakDetector
{
    
    
public:
    SimplePeakDetector();
    ~SimplePeakDetector();
    
    bool detect(float input);
    
private:
    
};

#endif /* defined(__DrumLooper__SimplePeakDetector__) */
