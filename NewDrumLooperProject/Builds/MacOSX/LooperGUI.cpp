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
    //initialisations
    //noOfLayers = 0;
    selectedLayerIndex = -1;
    //playPosition = 0;
    listener = nullptr;
    recordCycle = false;
    //playState = false;
    muteValues.clear();
    gainValues.clear();
    panValues.clear();
    
    //run thread
    setThreadState(true);
    
    //testButton.addListener(this);
    //testButton.setButtonText("Test");
    //addAndMakeVisible(&testButton);
    
    //slider setup
    addAndMakeVisible(&gainSlider);
	gainSlider.setRange(0.0, 1.0, 0.01);
	gainSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	gainSlider.addListener(this);
	gainSlider.setTextBoxStyle(Slider::NoTextBox, false, 40, 20);
	gainSlider.setValue(0.8, dontSendNotification);
    gainSlider.setColour(Slider::rotarySliderFillColourId, Colours::deepskyblue);
    gainSlider.setColour(Slider::rotarySliderOutlineColourId, Colours::grey);
    gainSlider.setTooltip("Adjust gain of selected layer");
    
    scaleSlider.setRange(1, 40, 1);
    scaleSlider.setSliderStyle(Slider::LinearVertical);
    scaleSlider.addListener(this);
    scaleSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    scaleSlider.setValue(10, dontSendNotification);
    scaleSlider.setColour(Slider::thumbColourId, Colours::deepskyblue);
    scaleSlider.setTooltip("Adjust scale of audio graphic for all layers");
    addAndMakeVisible(&scaleSlider);
    
    panSlider.setRange(0.0, 1.0, 0.01);
    panSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    panSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    panSlider.setTooltip("Adjust pan for selected layer");
    panSlider.addListener(this);
    panSlider.setValue(0.5);
    panSlider.setColour(Slider::rotarySliderFillColourId, Colours::deepskyblue);
    panSlider.setColour(Slider::rotarySliderOutlineColourId, Colours::grey);
    addAndMakeVisible(&panSlider);
    
    
    //Labels
	gainLabel.setText("Layer Gain", dontSendNotification);
	gainLabel.setJustificationType(Justification::centred);
    gainLabel.setColour(Label::textColourId, Colours::lightgrey);
	addAndMakeVisible(&gainLabel);
    
    panLabel.setText("Layer Pan", dontSendNotification);
    panLabel.setJustificationType(Justification::centred);
    panLabel.setColour(Label::textColourId, Colours::lightgrey);
    addAndMakeVisible(&panLabel);
    
    selectedLabel.setText("Selected Layer:", dontSendNotification);
    selectedLabel.setJustificationType(Justification::centred);
    selectedLabel.setEditable(false);
    selectedLabel.setColour(Label::textColourId, Colours::lightgrey);
    addAndMakeVisible(&selectedLabel);
    
    selecterLabel.setText("None", dontSendNotification);
    selecterLabel.setJustificationType(Justification::centred);
    selecterLabel.setEditable(true);
    selecterLabel.addListener(this);
    selecterLabel.setColour(Label::textColourId, Colours::lightgrey);
    selecterLabel.setTooltip("Click to change selected layer");
    addAndMakeVisible(&selecterLabel);
    
    scaleLabel.setText("Scale", dontSendNotification);
    scaleLabel.setJustificationType(Justification::centred);
    scaleLabel.setColour(Label::textColourId, Colours::lightgrey);
    addAndMakeVisible(&scaleLabel);
    
    //buttons
    playButton.addListener(this);
    playButton.setToggleState(false, dontSendNotification);
    addAndMakeVisible(&playButton);
    
    toStartButton.addListener(this);
    addAndMakeVisible(&toStartButton);
    
    recordButton.addListener(this);
    addAndMakeVisible(&recordButton);
    
    muteButton.addListener(this);
    addAndMakeVisible(&muteButton);
    
    clearLayerButton.addListener(this);
    addAndMakeVisible(&clearLayerButton);
    
    clearAllButton.addListener(this);
    addAndMakeVisible(&clearAllButton);
    
    loopRecButton.addListener(this);
    loopRecButton.setClickingTogglesState(true);
    addAndMakeVisible(&loopRecButton);

}
LooperGUI::~LooperGUI(){
    
    setThreadState(false);
    listener = nullptr;
    
    //std::cout << "LooperGui dtor\n";
}

void LooperGUI::setListener(Listener* newListener){

    listener = newListener;
}

void LooperGUI::resized(){
    
    //int x = getWidth();
    //int y = getHeight();
    
    //testButton.setBounds(410, 10, 60, 30);
    
    selectedLabel.setBounds(TIME_DISPLAY_WIDTH + 2, TOP_CORNER_Y + 0, 100, 20);
    selecterLabel.setBounds(TIME_DISPLAY_WIDTH + 13, TOP_CORNER_Y + 20, 70, 20);
    gainSlider.setBounds(TIME_DISPLAY_WIDTH + 23, TOP_CORNER_Y + 70, 50, 50);
    gainLabel.setBounds(TIME_DISPLAY_WIDTH + 13, TOP_CORNER_Y + 50, 70, 20);
    
    panSlider.setBounds(TIME_DISPLAY_WIDTH + 23, TOP_CORNER_Y + 150, 50, 50);
    panLabel.setBounds(TIME_DISPLAY_WIDTH + 13, TOP_CORNER_Y + 130, 70, 20);
    
    muteButton.setBounds(TIME_DISPLAY_WIDTH + 13, TOP_CORNER_Y + 210, 50, 50);
    
    playButton.setBounds(10, 10, 50, 50);
    toStartButton.setBounds(70, 10, 50, 50);
    recordButton.setBounds(130, 10, 50, 50);
    loopRecButton.setBounds(190, 10, 105, 50);
    
    clearLayerButton.setBounds(TOP_CORNER_X + 10, TOP_CORNER_Y + TIME_DISPLAY_HEIGHT + 10, 70, 30);
    clearAllButton.setBounds(TOP_CORNER_X + 10, TOP_CORNER_Y + TIME_DISPLAY_HEIGHT + 50, 70, 30);
    
    scaleSlider.setBounds(TOP_CORNER_X + 90, TOP_CORNER_Y + TIME_DISPLAY_HEIGHT + 10, 30, 60);
    scaleLabel.setBounds(TOP_CORNER_X + 85, TOP_CORNER_Y + TIME_DISPLAY_HEIGHT + 75, 40, 20);
    
    for (int i = 0; i < layerIcons.size(); i++) {
        layerIcons.getUnchecked(i)->setBounds(TOP_CORNER_X, TOP_CORNER_Y + (i * (LAYER_HEIGHT + GAP_BETWEEN_LAYERS)), LAYER_WIDTH, LAYER_HEIGHT);
    }
}


void LooperGUI::paint(Graphics &g){
    
    //draw time display background
    //Colour c = Colours::grey;
    //c = c.withAlpha(0.23);
    
    
    g.setColour(Colours::grey.withAlpha(0.2f));
    g.fillRoundedRectangle(TOP_CORNER_X, TOP_CORNER_Y, TIME_DISPLAY_WIDTH, TIME_DISPLAY_HEIGHT, CORNER_SIZE);
    
    //draw label if recording first layer
    if (recordState.get() == true && playState.get() == true) {
        
        g.setColour(Colours::red);
        
        if (layerIcons.size() == 0) {
            
            if (countIn.get() == true) {
                g.drawSingleLineText("Count In...", 10, 90);
            }
            else {
                g.drawSingleLineText("Recording First Layer...", 10, 90);
            }
        }
        else {
         
            bool showLabel = false;
            if (loopRecButton.getToggleState()) {
                
                if (recordCycle.get()) {
                    showLabel = true;
                }
            }
            else{
                showLabel = true;
            }
            
            if (layerIcons.size() < 7 && showLabel) {
                String s;
                s << "Recording Layer " << layerIcons.size() + 1;
                g.drawSingleLineText(s, 10, 90);
            }
        }
    }
    
    //play head
    g.setColour(Colours::grey);
    int playPosition = static_cast<int>(TIME_DISPLAY_WIDTH * transportPosition.get());
    g.drawRect(TOP_CORNER_X + playPosition, TOP_CORNER_Y, 2, TIME_DISPLAY_HEIGHT);
}

//ButtonCallback==============================================================================
void LooperGUI::buttonClicked(Button* button){
    
    if (button == &playButton)
    {
        //only start playing if record is enabled, or there is pre-existing layers
        if (recordState.get() == true || layerIcons.size() > 0)
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
        if (selectedLayerIndex >= 0 && selectedLayerIndex < layerIcons.size())
        {
            muteButton.setToggleState(!muteButton.getToggleState(), dontSendNotification);
            if (listener != nullptr) {
                listener->layerMuteToggled(selectedLayerIndex, muteButton.getToggleState());
            }
            muteValues.set(selectedLayerIndex, !muteValues[selectedLayerIndex]);
            layerIcons[selectedLayerIndex]->setMuted(muteButton.getToggleState());
            
            
            
        }
        
    }
    else if (button == &clearLayerButton){
        
        //only works if looper is not playing
        if (playState.get() == false) {
            
            //if selected layer is valid
            if (selectedLayerIndex >= 0 && selectedLayerIndex < layerIcons.size())
            {
                //inform looper
                listener->deleteLayer(selectedLayerIndex);
                //clear one element of icon and parameter arrays
                layerIcons.remove(selectedLayerIndex);
                gainValues.remove(selectedLayerIndex);
                muteValues.remove(selectedLayerIndex);
                panValues.remove(selectedLayerIndex);
                
                //reposition and re-number layers
                for (int i = 0; i < layerIcons.size(); i++) {
                    
                    layerIcons[i]->setLayerIndex(i);
                    
                    layerIcons.getUnchecked(i)->setBounds(TOP_CORNER_X, TOP_CORNER_Y + (i * (LAYER_HEIGHT + GAP_BETWEEN_LAYERS)), LAYER_WIDTH, LAYER_HEIGHT);
                    
                }
            }
        }
        
        
        
    }
    else if (button == &clearAllButton){
        
        //inform looper
        listener->deleteAllLayers();
        
        //clear arrays of icons and parameters
        layerIcons.clear();
        gainValues.clear();
        muteValues.clear();
        panValues.clear();
        
        muteButton.setToggleState(false, dontSendNotification);
        gainSlider.setValue(0.8);
        selecterLabel.setText("None", dontSendNotification);
        panSlider.setValue(0.5);
    }
    
    else if (button == &toStartButton){
        
        if (playState.get() == true)
            listener->playButtonToggled();
        
        listener->setReaderToZero();
        
        
        MessageManagerLock mml (Thread::getCurrentThread());
        if (! mml.lockWasGained())
            return;
        playButton.setToggleState(false, dontSendNotification);
    }
    
    else if (button == &loopRecButton){
        
        listener->setAlternateLoopRec(loopRecButton.getToggleState());
        //loopRecButton.setToggleState(!loopRecButton.getToggleState(), 0);
        
        //std::cout << "Boo " << loopRecButton.getToggleState() << "\n";
    }
}


//label listener
void LooperGUI::labelTextChanged (Label *labelThatHasChanged){
    
    if (labelThatHasChanged == &selecterLabel)
    {
        String input = labelThatHasChanged->getText();
        //check input value is in range
        if (input.getIntValue() > 0 && input.getIntValue() <= layerIcons.size()) {
            
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
            panSlider.setValue(panValues[selectedLayerIndex], dontSendNotification);
            
        }
    }
    
}


void LooperGUI::setPlayState (const bool newState)
{
    playState = newState;
    playButton.setToggleState(playState.get(), dontSendNotification);
    clearLayerButton.setEnabled(!newState);
    loopRecButton.setEnabled(!newState);
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

void LooperGUI::setTransportUpdateStatus(bool shouldUpdate, float relativePosition, bool countingIn){
    
    updateState.set(shouldUpdate);
    transportPosition.set(relativePosition);
    countIn.set(countingIn);
}


void LooperGUI::run()
{
    //int startTime = Time::getMillisecondCounter();
    //std::cout << "start time = " << startTime << "\n";
    
	while (!threadShouldExit())
    {
        
        //wait for whatever gui update time is
        uint32 time = Time::getMillisecondCounter();
		Time::waitForMillisecondCounter (time + 20);
        
        
        //this part courtesy of Julian Storer at http://www.juce.com/api/classMessageManagerLock.html
        MessageManagerLock mml (Thread::getCurrentThread());
        if (! mml.lockWasGained())
            return;
        
        if (updatePlayState.get()) {
            setPlayState(true);
            updatePlayState.set(false);
        }
        
        repaint();
	}
}

//SliderCallback=================================================================
void LooperGUI::sliderValueChanged (Slider* slider)
{
    if (slider == &gainSlider)
    {
        // selected layer is valid
        if (selectedLayerIndex >= 0 && selectedLayerIndex < layerIcons.size())
        {
            gainValues.set(selectedLayerIndex, slider->getValue());
            listener->layerGainChanged(selectedLayerIndex, slider->getValue());
            layerIcons[selectedLayerIndex]->setGain(slider->getValue());
        }
		
	}
    else if (slider == &scaleSlider){
        
        for (int i = 0; i < layerIcons.size(); i++) {
            layerIcons[i]->setScale(slider->getValue());
        }
    }
    else if (slider == &panSlider){
        
        // selected layer is valid
        if (selectedLayerIndex >= 0 && selectedLayerIndex < layerIcons.size())
        {
            panValues.set(selectedLayerIndex, slider->getValue());
            listener->layerPanChanged(selectedLayerIndex, slider->getValue());
            layerIcons[selectedLayerIndex]->setPan(slider->getValue());
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
    panSlider.setValue(panValues[selectedLayerIndex]);
    
    
    
    //layerGUI->getLayerId();
    std::cout << "selected layer = " << layerGUI->getLayerIndex() + 1 << "\n";
}

void LooperGUI::shouldUpdatePlayState(){
    
    updatePlayState.set(true);
}


void LooperGUI::addLayer(CustomAudioThumbnail thumbnailToAdd){
    
    //std::cout << "GUI Layer Added\n";
    
    //add a new layer Icon - first create a pointer to a new object
    LayerGUI* newLayerGUI = new LayerGUI(layerIcons.size(), thumbnailToAdd);
    newLayerGUI->setTooltip("Click to select this layer");
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
    //increment number of layers and add gain value and mute value
    gainValues.add(0.8);
    muteValues.add(false);
    panValues.add(0.5);
    //noOfLayers++;
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

