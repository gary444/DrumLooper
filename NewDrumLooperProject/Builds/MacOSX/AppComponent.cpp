//
//  AppComponent.cpp
//  DrumLooper
//
//  Created by Gareth Rendle on 01/11/2013.
//
//

#include "AppComponent.h"

#define NUMBER_OF_METERS 3


AppComponent::AppComponent()
{
    
    
    addAndMakeVisible(&audio);
    
    
}
AppComponent::~AppComponent()
{
    //std::cout << "AppComponent dtor\n";
    
}

//ComponentCallbacks============================================================
void AppComponent::resized()
{
    audio.setBounds(0, 0, 700, 600);
}

void AppComponent::paint (Graphics &g)
{
    
}


//MenuBarCallbacks==============================================================
StringArray AppComponent::getMenuBarNames()
{
	const char* const names[] = { "File", 0 };
	return StringArray (names);
}

PopupMenu AppComponent::getMenuForIndex (int topLevelMenuIndex, const String& menuName)
{
	PopupMenu menu;
	if (topLevelMenuIndex == 0)
        menu.addItem(AudioPrefs, "Audio Prefrences", true, false);
	return menu;
}

void AppComponent::menuItemSelected (int menuItemID, int topLevelMenuIndex)
{
	if (topLevelMenuIndex == FileMenu)
    {
        if (menuItemID == AudioPrefs)
        {
            //AudioDeviceSelectorComponent audioSettingsComp (audioDeviceManager,
                                                            //0, 2, 2, 2,
                                                            //true, true, true, true);
            //audioSettingsComp.setSize (500, 250);
            //DialogWindow::showModalDialog ("Audio Settings", &audioSettingsComp, this, Colours::azure, true);
        }
    }
}