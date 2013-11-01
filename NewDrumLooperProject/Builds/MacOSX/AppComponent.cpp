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
    //playButton.addListener(this);
    //addAndMakeVisible(&playButton);
    
    //recordButton.addListener(this);
    //addAndMakeVisible(&recordButton);
    
    //meters
    //for (int i = 0; i < NUMBER_OF_METERS; i++) {
     //   meters[i].setMeterNumber(i + 1);
       // addAndMakeVisible(&meters[i]);
    //}
    
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
    
    ///addAndMakeVisible(&masterControls);
    
    //addAndMakeVisible(&triggerResponse);
    //triggerResponse.setListener(this);
    
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
    
    //looper GUI================================================================================
    
    //looper.setGUIReference(&looperGUI);
    //looper.setListener(&looperGUI);
    //addAndMakeVisible(&looperGUI);
    
    
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
    
    //playButton.setBounds(10, 10, 50, 50);
    //recordButton.setBounds(70, 10, 50, 50);
    //masterControls.setBounds(10, 80, 50, 130);
    
    //looperGUI.setBounds(10, 300, 500, 500);
    
    //triggerResponse.setBounds(500, 10, 100, 100);
    
    
    //metroTestButton.setBounds(200, 10, 100, 30);
    
    //sampleChooser->setBounds(200, 50, 100, 30);
    
    //meters
    //for (int i = 0; i < NUMBER_OF_METERS; i++) {
    //    meters[i].setBounds(200, 100 + (i * 20), 110, 20);
    //}
}

void AppComponent::paint (Graphics &g)
{
    
}

//MidiInputCallback=============================================================

void AppComponent::buttonClicked (Button* button)
{
    /*
    if (button == &playButton)
    {
        looper.setPlayState (!looper.getPlayState());
        playButton.setToggleState (looper.getPlayState(), false);
    }
    else if (button == &recordButton)
    {
        looper.setRecordState (!looper.getRecordState());
        recordButton.setToggleState (looper.getRecordState(), false);
    }
    else if (button == &metroTestButton)
    {
        std::cout << "metro test\n";
        metronome.tick();
        
    }
     */
}

/*void AppComponent::triggerReceived  (const unsigned int triggerType)
{
    std::cout << "trigger type " << triggerType << " receieved" << std::endl;
}*/

/*//AudioCallbacks================================================================
void AppComponent::audioDeviceIOCallback (const float** inputChannelData,
                                          int numInputChannels,
                                          float** outputChannelData,
                                          int numOutputChannels,
                                          int numSamples)
{
    //3 input
    const float *inL, *inR, *inTrigger;
    float *outL, *outR;
    
    inL = inputChannelData[0];
    inR = inputChannelData[1];
    inTrigger = inputChannelData[2];
    outL = outputChannelData[0];
    outR = outputChannelData[1];
    
    while(numSamples--)
    {
        float outputL, outputR = 0.f;
        
        //pass inputs to meters
        //meters[0].process(*inL);
        //meters[1].process(*inR);
        //meters[2].process(*inTrigger);
        
        
       // outputL = looper.processSample (*inL, 0);
        //outputR = looper.processSample(*inR, 1);
        
        //pass channel 3 input to triggerResponse class
        //triggerResponse.processInput(*inTrigger);
        
        //outputL += metronome.getNextSample(0);
        //outputR += metronome.getNextSample(1);
        
        //*outL = masterControls.processSample(outputL);
        //*outR = masterControls.processSample(outputR);
        
        inL++;
        inR++;
        inTrigger++;
        outL++;
        outR++;
    }
    
}

void AppComponent::audioDeviceAboutToStart (AudioIODevice* device)
{
    
}

void AppComponent::audioDeviceStopped()
{
    
}*/

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