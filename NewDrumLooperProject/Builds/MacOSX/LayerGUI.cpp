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
}

LayerGUI::LayerGUI(int newLayerIndex){
    
    layerIndex = newLayerIndex;
}

LayerGUI::~LayerGUI(){
    
    
    
    std::cout << "LayerGUI  dtor\n";
}

void LayerGUI::addListener(Listener* newListener){
    
    listener = newListener;
    
}

//ComponentCallbacks============================================================
void LayerGUI::resized(){
    
}
void LayerGUI::paint (Graphics &g){
    
    //bg fill
    g.setColour(Colours::lightblue);
    g.fillRoundedRectangle(0, 0, getWidth(), getHeight(), 3);
    
    //label - add 1 to convert from index to human number
    g.setColour(Colours::black);
    String label;
    label << "Layer " << layerIndex + 1;
    g.drawSingleLineText(label, 10, getHeight() - 5);
    
    //selected indicator
    if (isSelected) {
        g.drawRoundedRectangle(0, 0, getWidth(), getHeight(), 3, 2);
        
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