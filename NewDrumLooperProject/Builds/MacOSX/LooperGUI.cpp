//
//  LooperGUI.cpp
//  DrumLooper
//
//  Created by Gareth Rendle on 05/11/2013.
//
//

#include "LooperGUI.h"


LooperGUI::LooperGUI()  : Thread ("GuiThread")
{
    noOfLayers = 0;
    
    setThreadState(true);
    
    selectedLayer = 1;
    
    playPosition = 0;
    
    //layout initialisations
    topCornerX = 0;
    topCornerY = 100;
    layerWidth = 400;
    layerHeight = 20;
    cornerSize = 3;
    gapBetweenLayers = 10;
    timeDisplayWidth = layerWidth;
    timeDisplayHeight = 240;
    
    //this->addMouseListener(this, true);
    
    testButton.addListener(this);
    testButton.setButtonText("Test");
    addAndMakeVisible(&testButton);
    
    //slider setup
    addAndMakeVisible(&gainSlider);
	gainSlider.setRange(0.0, 1.0, 0.01);
	gainSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	gainSlider.addListener(this);
	gainSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
	gainSlider.setValue(0.8, dontSendNotification);
    
    //Labels
	gainLabel.setText("Layer Gain", dontSendNotification);
	gainLabel.setJustificationType(Justification::centred);
	addAndMakeVisible(&gainLabel);
    
    //initialise gain values
    for (int i = 0; i < 8; i++)
        gainValues[i] = 0.f;
    
    listener = nullptr;
    
    //play and record buttons
    playButton.addListener(this);
    addAndMakeVisible(&playButton);
    
    recordButton.addListener(this);
    addAndMakeVisible(&recordButton);

    
    
}
LooperGUI::~LooperGUI(){
    
    setThreadState(false);
}

void LooperGUI::setListener(Listener* newListener){

    listener = newListener;
}

void LooperGUI::resized(){
    
    //int x = getWidth();
    //int y = getHeight();
    
    testButton.setBounds(410, 10, 60, 30);
    gainSlider.setBounds(410, 50, 70, 70);
    gainLabel.setBounds(410, 120, 70, 20);
    
    playButton.setBounds(10, 10, 50, 50);
    recordButton.setBounds(70, 10, 50, 50);
}


void LooperGUI::paint(Graphics &g){
    
    //**layout variables in header file**
    
    //draw time display background
    g.setColour(Colours::slateblue);
    g.fillRoundedRectangle(topCornerX, topCornerY, timeDisplayWidth, timeDisplayHeight, cornerSize);
    
    g.setColour(Colours::lightblue);
    
    sharedMemory.enter();
    
    //draw layers
    for (int i = 0; i < noOfLayers; i++) {
        
        g.fillRoundedRectangle(topCornerX + 0, topCornerY + (i * (layerHeight + gapBetweenLayers)), layerWidth, layerHeight, cornerSize);
    }
    
    g.setColour(Colours::black);
    
    //add labels
    for (int i = 0; i < noOfLayers; i++) {
        
        String label;
        label << "Layer " << i + 1;
        g.drawSingleLineText(label, topCornerX + 10, topCornerY + (layerHeight - 5) + (i * (layerHeight + gapBetweenLayers)));
    }
    
    //outline selected layer
    g.setColour(Colours::black);
    if (noOfLayers > 0) {
        g.drawRoundedRectangle(topCornerX + 0, topCornerY + ((selectedLayer - 1) * (layerHeight + gapBetweenLayers)), layerWidth, layerHeight, cornerSize, 2);
    }
    
    sharedMemory.exit();
    
    //play head
    g.setColour(Colours::pink);
    g.drawRect(topCornerX + playPosition, topCornerY, 2, timeDisplayHeight);
}

void LooperGUI::setPlayState (const bool newState)
{
    playState = newState;
}

bool LooperGUI::getPlayState () const
{
    return playState.get();
}

void LooperGUI::setRecordState (const bool newState)
{
    recordState = newState;
}

bool LooperGUI::getRecordState () const
{
    return recordState.get();
}

void LooperGUI::mouseDown(const MouseEvent &event)
{
    std::cout << "Mouse Down detected" << std::endl;
    
    int x = event.x;
    int y = event.y - topCornerY;
    
    //new selected layer variable - init to 1
    sharedMemory.enter();
    int newSelectedLayer = selectedLayer;
    
    
    //check that mouseclick is on one of the layers. check width first
    if (x <= layerWidth) {
        
        //then heights
        for (int i = 0; i <= noOfLayers; i++) {
            
            if (y >= ((layerHeight + gapBetweenLayers) * (i - 1)) && y <= ((layerHeight * i) + (gapBetweenLayers * (i - 1))))
            {
                newSelectedLayer = i;
            }
        }
    }
    
    selectedLayer = newSelectedLayer;
    std::cout << "New selected layer = " << selectedLayer << std::endl;
    
    sharedMemory.exit();
    
}


//ButtonCallback==============================================================================
void LooperGUI::buttonClicked(Button* button){
    
    if (button == &testButton)
    {
        int val = 0;
        //val = looper->getReaderPosition();
        
        std::cout << "TEST" << std::endl;
        std::cout << "position = " << val << std::endl;
        
    }
    else if (button == &playButton)
    {
        
        if (listener != nullptr) {
            listener->playButtonToggled();
        }
        
        playButton.setToggleState (getPlayState(), dontSendNotification);
    }
    else if (button == &recordButton)
    {
        if (listener != nullptr) {
            listener->recordButtonToggled();
        }
        
        recordButton.setToggleState (getRecordState(), dontSendNotification);
    }
}

//SliderCallback==============================================================================
void LooperGUI::sliderValueChanged (Slider* slider)
{
    if (slider == &gainSlider)
    {
		gainValues[selectedLayer] = slider->getValue();
        listener->layerGainChanged(selectedLayer, slider->getValue());
	}
}

void LooperGUI::addLayer(){
    
    std::cout << "GUI Layer Added\n";
    
    sharedMemory.enter();
    noOfLayers++;
    sharedMemory.exit();
    
}
void LooperGUI::setThreadState (bool shouldBeRunning)
{
    if(shouldBeRunning == true)
        startThread();
    else
        stopThread(500);
}

void LooperGUI::run()
{
    //uint32 startTime = Time::getMillisecondCounter();
    
	while (!threadShouldExit())
    {
        uint32 time = Time::getMillisecondCounter();
        
        //if (listener != nullptr)
        //  listener->counterIncremented(time - startTime);
        
		Time::waitForMillisecondCounter (time + 100);
        
        
        
        //this part courtesy of Julian Storer at http://www.juce.com/api/classMessageManagerLock.html
        MessageManagerLock mml (Thread::getCurrentThread());
        if (! mml.lockWasGained())
            return;
        
        //find play position from looper
        //sharedMemory.enter();
        //float exactPlayPosition = (looper->getReaderPosition()) * timeDisplayWidth;
        //playPosition = static_cast<int>(exactPlayPosition);
        //sharedMemory.exit();
        
        repaint();
	}
}