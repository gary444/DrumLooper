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
                        public MenuBarModel,
                        //public AudioIODeviceCallback,
                        Button::Listener,
                        //TriggerResponse::Listener,
                        public FilenameComponentListener
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
    
    //Button Listener
    void buttonClicked (Button* button);
    
    //mouse callbacks
    //void mouseDown (const MouseEvent &event);
    
    //FilenameComponent Callback
    void filenameComponentChanged (FilenameComponent* fileComponentThatHasChanged);
    
    
    
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
    BigInteger noInputChannels;
    BigInteger noOutputChannels;
    //Components
    
    //metro test
    TextButton metroTestButton;
    //Metronome metronome;
    FilenameComponent* sampleChooser;
    File* file;
    
    
    ScopedPointer<Audio> audio;
    
};

#endif /* defined(__DrumLooper__AppComponent__) */
