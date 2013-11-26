//
//  AppComponent.h
//  DrumLooper
//
//  Created by Gareth Rendle on 01/11/2013.
//
//

#ifndef __DrumLooper__AppComponent__
#define __DrumLooper__AppComponent__


#include "../JuceLibraryCode/JuceHeader.h"
#include "Audio.h"


/**
 The main component for the applicaiton
 */
class AppComponent  :   public Component,
                        public MenuBarModel
{
public:
	//==============================================================================
    /**
     Constructor
     */
	AppComponent();
    
    /**
     Destructor
     */
	~AppComponent();
    
	//ComponentCallbacks============================================================
	void resized();
	void paint (Graphics &g);
    
    
    
    
    
    //MenuBarEnums/Callbacks========================================================
    enum Menus
	{
		FileMenu=0,
		
		NumMenus
	};
    
    enum FileMenuItems
	{
        AudioPrefs = 1,
		
		NumFileItems
	};
    StringArray getMenuBarNames();
    PopupMenu getMenuForIndex (int topLevelMenuIndex, const String& menuName);
	void menuItemSelected (int menuItemID, int topLevelMenuIndex);
private:
	//==============================================================================
	//Add data members here
    //Audio
    AudioDeviceManager audioDeviceManager;
    AudioIODevice* currentDevice;
    //Components

    
    Audio audio;
    
};

#endif /* defined(__DrumLooper__AppComponent__) */
