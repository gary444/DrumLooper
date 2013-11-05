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
    
    //metro test================================================
    //metroTestButton.setButtonText("Metro Test");
    //addAndMakeVisible(&metroTestButton);
    //metroTestButton.addListener(this);
    
    //AudioFormatManager formatManager;
	//formatManager.registerBasicFormats();
    
    /*sampleChooser = new FilenameComponent ("AudioFile",
                                           File::nonexistent,
                                           true, false, false,
                                           formatManager.getWildcardForAllFormats(),
                                           String::empty,
                                           "(choose an audio file)");
    
    addAndMakeVisible (sampleChooser);
    sampleChooser->addListener (this);
    sampleChooser->setBrowseButtonText ("...");*/
    //end of metro test================================================
    
    //audio setup================================================================================
    
    //init
   // noInputChannels = noOutputChannels = 0;

/*
    audioDeviceManager.initialise(3, 2, 0, true, String::empty, 0);
    audioDeviceManager.addAudioCallback(this);
    
    //this part from http://www.juce.com/forum/topic/possible-bug-asioaudioiodeviceopen
    AudioDeviceManager::AudioDeviceSetup oldDeviceSetup;
    audioDeviceManager.getAudioDeviceSetup(oldDeviceSetup);
    int sampleRate = oldDeviceSetup.sampleRate;
    triggerResponse.setSampleRate(sampleRate);
    
    currentDevice = audioDeviceManager.getCurrentAudioDevice();
    
    noInputChannels = currentDevice->getActiveInputChannels();
    noOutputChannels = currentDevice->getActiveOutputChannels();
    
    String channelInfoText;
    channelInfoText << "Audio Device : " << currentDevice->getName() << "\nInput : " << (noInputChannels.toString(10)) << " Output : " << (noOutputChannels.toString(10)) << "\n";
    std::cout << channelInfoText;
    
    String s;
    StringArray sA = currentDevice->getOutputChannelNames();
    s << sA[0] << sA[1] << sA[2] << sA[3];
    std::cout << s;
*/    
    
    
    
    //load metronome file
    String path;
    //absolute path
    //path = "Sounds/CYCdh_VinylK1-ClHat02.wav";
    //File::getCurrentWorkingDirectory().getChildFile (path);
    //file = new File(path);
    //metronome.loadFile(*file);
    
    audio = new Audio;
    addAndMakeVisible(audio);
    
    
}
AppComponent::~AppComponent()
{
    //audioDeviceManager.removeAudioCallback(this);
    
    //delete sampleChooser;
    
    //if (file != nullptr)
    //  delete file;
    
}

//ComponentCallbacks============================================================
void AppComponent::resized()
{
    //int x = getWidth();
    //int y = getHeight();
    
    audio->setBounds(0, 0, 600, 600);
    
    
    //metroTestButton.setBounds(200, 10, 100, 30);
    
    //sampleChooser->setBounds(200, 50, 100, 30);
    
}

void AppComponent::paint (Graphics &g)
{
    
}

void AppComponent::buttonClicked (Button* button)
{
    /*
    if (button == &metroTestButton)
    {
        std::cout << "metro test\n";
        metronome.tick();
        
    }
     */
}

//void AppComponent::mouseDown (const MouseEvent &event)
//{
//   std::cout << "Appp Component mouse click detected" << std::endl;
//}

//FilenameComponent Callback
void AppComponent::filenameComponentChanged (FilenameComponent* filenameComponent)
{
    if (filenameComponent == sampleChooser)
    {
        
        
        //metronome.loadFile(filenameComponent->getCurrentFile());
        
        
        //InputSource inputSource;
        //audioThumbnail->setSource(filenameComponent->getCurrentFile());
    }
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