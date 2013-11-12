//
//  LooperGUI.cpp
//  DrumLooper
//
//  Created by Gareth Rendle on 05/11/2013.
//
//

#include "LooperGUI.h"

#define TOP_CORNER_X 0
#define TOP_CORNER_Y 100
#define LAYER_WIDTH 400
#define LAYER_HEIGHT 20
#define CORNER_SIZE 3
#define GAP_BETWEEN_LAYERS 10
#define TIME_DISPLAY_WIDTH 400
#define TIME_DISPLAY_HEIGHT 240

LooperGUI::LooperGUI()  : Thread ("GuiThread")
{
    //initialisations
    noOfLayers = 0;
    selectedLayerIndex = -1;
    playPosition = 0;
    listener = nullptr;
    
    //run thread
    setThreadState(true);
    
    testButton.addListener(this);
    testButton.setButtonText("Test");
    addAndMakeVisible(&testButton);
    
    //slider setup
    addAndMakeVisible(&gainSlider);
	gainSlider.setRange(0.0, 1.0, 0.01);
	gainSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	gainSlider.addListener(this);
	gainSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 20);
	gainSlider.setValue(0.8, dontSendNotification);
    
    //Labels
	gainLabel.setText("Layer Gain", dontSendNotification);
	gainLabel.setJustificationType(Justification::centred);
	addAndMakeVisible(&gainLabel);
    
    selectedLabel.setText("Selected Layer:", dontSendNotification);
    selectedLabel.setJustificationType(Justification::centred);
    selectedLabel.setEditable(false);
    addAndMakeVisible(&selectedLabel);
    
    selecterLabel.setText("None", dontSendNotification);
    selecterLabel.setJustificationType(Justification::centred);
    selecterLabel.setEditable(true);
    selecterLabel.addListener(this);
    addAndMakeVisible(&selecterLabel);
    
    //buttons
    playButton.addListener(this);
    addAndMakeVisible(&playButton);
    
    recordButton.addListener(this);
    addAndMakeVisible(&recordButton);
    
    muteButton.addListener(this);
    addAndMakeVisible(&muteButton);

    
    
}
LooperGUI::~LooperGUI(){
    
    setThreadState(false);
    listener = nullptr;
    
    std::cout << "LooperGui dtor\n";
}

void LooperGUI::setListener(Listener* newListener){

    listener = newListener;
}

void LooperGUI::resized(){
    
    //int x = getWidth();
    //int y = getHeight();
    
    testButton.setBounds(410, 10, 60, 30);
    selectedLabel.setBounds(TIME_DISPLAY_WIDTH + 2, TOP_CORNER_Y + 0, 100, 20);
    selecterLabel.setBounds(TIME_DISPLAY_WIDTH + 13, TOP_CORNER_Y + 20, 70, 20);
    gainSlider.setBounds(TIME_DISPLAY_WIDTH + 13, TOP_CORNER_Y + 70, 70, 70);
    gainLabel.setBounds(TIME_DISPLAY_WIDTH + 13, TOP_CORNER_Y + 50, 70, 20);
    muteButton.setBounds(TIME_DISPLAY_WIDTH + 13, TOP_CORNER_Y + 150, 50, 50);
    
    playButton.setBounds(10, 10, 50, 50);
    recordButton.setBounds(70, 10, 50, 50);
    
    for (int i = 0; i < layerIcons.size(); i++) {
        layerIcons.getUnchecked(i)->setBounds(TOP_CORNER_X, TOP_CORNER_Y + (i * (LAYER_HEIGHT + GAP_BETWEEN_LAYERS)), LAYER_WIDTH, LAYER_HEIGHT);
    }
}


void LooperGUI::paint(Graphics &g){
    
    //draw time display background
    g.setColour(Colours::slateblue);
    g.fillRoundedRectangle(TOP_CORNER_X, TOP_CORNER_Y, TIME_DISPLAY_WIDTH, TIME_DISPLAY_HEIGHT, CORNER_SIZE);
    
    //draw label if recording first layer
    if (recordState.get() == true && playState.get() == true && noOfLayers == 0) {
        g.setColour(Colours::red);
        g.drawSingleLineText("Recording First Layer...", TOP_CORNER_X + 30, TOP_CORNER_Y + 60);
    }
    
    
    
    //play head
    g.setColour(Colours::pink);
    g.drawRect(TOP_CORNER_X + playPosition, TOP_CORNER_Y, 2, TIME_DISPLAY_HEIGHT);
}

//ButtonCallback==============================================================================
void LooperGUI::buttonClicked(Button* button){
    
    if (button == &playButton)
    {
        //only start playing if record is enabled, or there is pre-existing layers
        if (recordState.get() == true || noOfLayers > 0)
        {
            if (listener != nullptr) {
                listener->playButtonToggled();
            }
            
            playButton.setToggleState (getPlayState(), dontSendNotification);
        }
        
    }
    else if (button == &recordButton)
    {
        if (listener != nullptr) {
            listener->recordButtonToggled();
        }
        
        recordButton.setToggleState (getRecordState(), dontSendNotification);
    }
    else if (button == &muteButton){
        
        
        //if selected layer is valid
        if (selectedLayerIndex >= 0 && selectedLayerIndex < noOfLayers)
        {
            muteButton.setToggleState(!muteButton.getToggleState(), dontSendNotification);
            if (listener != nullptr) {
                listener->layerMuteToggled(selectedLayerIndex, muteButton.getToggleState());
            }
            muteValues.set(selectedLayerIndex, muteButton.getToggleState());
            layerIcons[selectedLayerIndex]->setMuted(muteButton.getToggleState());
            
        }
        
    }
    else if (button == &testButton){
        
        String s;
        
        for (int i = 0; i < gainValues.size(); i++) {
            s << gainValues[i] << " ";
        }
        std::cout << s << "\n";
    }
}


//label listener
void LooperGUI::labelTextChanged (Label *labelThatHasChanged){
    
    if (labelThatHasChanged == &selecterLabel)
    {
        String input = labelThatHasChanged->getText();
        //check input value is in range
        if (input.getIntValue() > 0 && input.getIntValue() <= noOfLayers) {
            
            sharedMemory.enter();
            //subtract one to convert from number to index
            selectedLayerIndex = input.getIntValue() - 1;
            std::cout << "selected layer = " << input.getIntValue() << "\n";
            sharedMemory.exit();
            
            //tell all icons whether they are selected
            for (int i = 0; i < layerIcons.size(); i++)
            {
                if (i == selectedLayerIndex)
                    layerIcons[i]->setSelected(true);
                
                else
                    layerIcons[i]->setSelected(false);
                
            }
            
            //change slider value to selected layer's value
            gainSlider.setValue(gainValues[selectedLayerIndex], dontSendNotification);
            muteButton.setToggleState(muteValues[selectedLayerIndex], dontSendNotification);
        }
    }
    
}


void LooperGUI::setPlayState (const bool newState)
{
    playState = newState;
    if (playState.get() == true && noOfLayers > 0) {
        setTransportRunningState(playState.get());
    }
    repaint();
    
    
}

bool LooperGUI::getPlayState () const
{
    return playState.get();
}

void LooperGUI::setRecordState (const bool newState)
{
    recordState = newState;
    repaint();
}

bool LooperGUI::getRecordState () const
{
    return recordState.get();
}


void LooperGUI::setLoopSampleLength(const int newLength){
    
    loopSampleLength = newLength;
}


void LooperGUI::setTransportRunningState(bool shouldBeRunning){
    
    transportState.set(shouldBeRunning);
}

void LooperGUI::run()
{
    //int startTime = Time::getMillisecondCounter();
    //std::cout << "start time = " << startTime << "\n";
    
	while (!threadShouldExit())
    {
        uint32 time = Time::getMillisecondCounter();
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

//SliderCallback=================================================================
void LooperGUI::sliderValueChanged (Slider* slider)
{
    if (slider == &gainSlider)
    {
        // selected layer is valid
        if (selectedLayerIndex >= 0 && selectedLayerIndex < noOfLayers)
        {
            gainValues.set(selectedLayerIndex, slider->getValue());
            listener->layerGainChanged(selectedLayerIndex, slider->getValue());
            layerIcons[selectedLayerIndex]->setGain(slider->getValue());
        }
		
	}
}

void LooperGUI::mouseDown(const MouseEvent &event)
{
    
}


//layerGUI listener callbacks
void LooperGUI::selected(LayerGUI* layerGUI){
    
    //tell all icons whether they are selected
    for (int i = 0; i < layerIcons.size(); i++)
    {
        if (i == layerGUI->getLayerIndex())
            layerIcons[i]->setSelected(true);
        
        else
            layerIcons[i]->setSelected(false);
    
    }
    
    selectedLayerIndex = layerGUI->getLayerIndex();
    String s;
    s << selectedLayerIndex + 1;
    selecterLabel.setText(s, dontSendNotification);
    
    //change slider value to selected layer's value
    gainSlider.setValue(gainValues[selectedLayerIndex]);
    muteButton.setToggleState(muteValues[selectedLayerIndex], dontSendNotification);
    
    
    
    //layerGUI->getLayerId();
    std::cout << "selected layer = " << layerGUI->getLayerIndex() + 1 << "\n";
}


void LooperGUI::addLayer(){
    
    std::cout << "GUI Layer Added\n";
    
    //add a new layer Icon - first create a pointer to a new object
    LayerGUI* newLayerGUI = new LayerGUI(noOfLayers);
    //pass this to owned array
    layerIcons.add(newLayerGUI);
    //add this looper gui object as its listener
    newLayerGUI->addListener(this);
    //make it visible
    
    MessageManagerLock mml (Thread::getCurrentThread());
    if (! mml.lockWasGained())
        return;
    addAndMakeVisible(newLayerGUI);
    //call resized to set bounds
    resized();
    
    
    sharedMemory.enter();
    //increment number of layers and add gain value
    gainValues.add(0.8);
    noOfLayers++;
    sharedMemory.exit();
    
    repaint();
}
void LooperGUI::setThreadState (bool shouldBeRunning)
{
    if(shouldBeRunning == true)
        startThread();
    else
        stopThread(500);
}

