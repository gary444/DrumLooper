//
//  AppWindow.h
//  DrumLooper
//
//  Created by Gareth Rendle on 01/11/2013.
//
//

#ifndef __DrumLooper__AppWindow__
#define __DrumLooper__AppWindow__

#include "../JuceLibraryCode/JuceHeader.h"
#include "DrumLooperHeaders.h"


/**
 The application window
 */
class AppWindow  : public DocumentWindow
{
public:
	//==============================================================================
    /**
     Constructor
     */
	AppWindow();
    
    /**
     Destructor
     */
	~AppWindow();
	//==============================================================================
	// called when the close button is pressed or esc is pushed
	void closeButtonPressed();
	
};

#endif /* defined(__DrumLooper__AppWindow__) */
