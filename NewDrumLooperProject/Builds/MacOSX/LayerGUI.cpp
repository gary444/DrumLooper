//
//  LayerGUI.cpp
//  DrumLooper
//
//  Created by Gareth Rendle on 05/11/2013.
//
//

#include "LayerGUI.h"

LayerGUI::LayerGUI(){
    
    layerIndex = 0;
    listener = nullptr;
    isSelected = false;
    gain = 0.8;
}

LayerGUI::LayerGUI(int newLayerIndex){
    
    layerIndex = newLayerIndex;
    
    listener = nullptr;
    isSelected = false;
    gain = 0.8;
}

LayerGUI::~LayerGUI(){
    
    
    
    //std::cout << "LayerGUI  dtor\n";
}

void LayerGUI::addListener(Listener* newListener){
    
    listener = newListener;
    
}

//ComponentCallbacks============================================================
void LayerGUI::resized(){
    
    repaint();
}
void LayerGUI::paint (Graphics &g){
    
    int x = getWidth();
    int y = getHeight();
    
    //bg fill
    g.setColour(Colours::lightblue);
    g.fillRoundedRectangle(0, 0, x, y, 3);
    
    //label - add 1 to convert from index to human number. draw red if muted
    if (isMuted) {
        g.setColour(Colours::red);
    }
    else
    {
        g.setColour(Colours::black);
    }
    String label;
    label << "Layer " << layerIndex + 1;
    g.drawSingleLineText(label, 10, y- 5);
    
    //gain indicator
    int indicatorHeight = static_cast<int>(y * gain);
    g.setColour(Colours::grey);
    g.fillRect(x - 8, y - indicatorHeight, 8, indicatorHeight);
    
    //selected indicator
    if (isSelected) {
        g.setColour(Colours::black);
        g.drawRoundedRectangle(0, 0, x, getHeight(), 3, 2);
        
    }
}

//mouse callbacks
void LayerGUI::mouseDown(const MouseEvent &event){
    
    if (listener != nullptr) {
        listener->selected(this);
    }
    
}
int LayerGUI::getLayerIndex(){
    
    return layerIndex;
}

void LayerGUI::setSelected(bool shouldBeSelected){
    
    isSelected = shouldBeSelected;
    repaint();
}

void LayerGUI::setGain(float newGain){
    
    gain = newGain;
    repaint();
}

void LayerGUI::setMuted(float shouldBeMuted){
    
    isMuted = shouldBeMuted;
    repaint();
}