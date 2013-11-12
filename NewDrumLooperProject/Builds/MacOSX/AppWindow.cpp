//
//  AppWindow.cpp
//  DrumLooper
//
//  Created by Gareth Rendle on 01/11/2013.
//
//

#include "AppWindow.h"

//==============================================================================
AppWindow::AppWindow()
:
DocumentWindow(
               "DrumLooper",                     // Set the text to use for the title
               Colours::lightgrey,					// Set the colour of the window
               DocumentWindow::allButtons,		// Set which buttons are displayed
               true							// This window should be added to the desktop
               )
{
    setResizable(true, false);
	setTitleBarHeight(20);
    //AppComponent*
    //appComponent = new AppComponent();
    setContentOwned(&appComponent, false);
    //setMenuBar (appComponent);
}

AppWindow::~AppWindow()
{
    std::cout << "AppWindow dtor\n";
    
}

void AppWindow::closeButtonPressed()
{
    JUCEApplication::getInstance()->systemRequestedQuit();
}