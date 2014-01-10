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
    pan = 0.5;
    isMuted = false;
    scale = 5;
    gotThumbnailInfo = false;
    
}

LayerGUI::LayerGUI(int newLayerIndex, CustomAudioThumbnail newThumbnailInfo){
    
    layerIndex = newLayerIndex;
    
    thumbnailInfo = newThumbnailInfo;
    
    listener = nullptr;
    isSelected = false;
    gain = 0.8;
    pan = 0.5;
    isMuted = false;
    scale = 20;
    gotThumbnailInfo = false;
}

LayerGUI::~LayerGUI(){
    
    
    
    //std::cout << "LayerGUI  dtor\n";
}

void LayerGUI::addListener(Listener* newListener){
    
    listener = newListener;
    
}

//ComponentCallbacks============================================================
void LayerGUI::resized(){
    
    //repaint();
}
void LayerGUI::paint (Graphics &g){
    
    int x = getWidth();
    int y = getHeight();
    
    //bg fill
    //g.setColour(Colours::whitesmoke);
    ColourGradient gradient1(Colours::whitesmoke, 0, 0, Colours::grey, 0, y, false);
    
    g.setGradientFill(gradient1);
    
    g.fillRoundedRectangle(0, 0, x, y, 3);
    
    //thumbnail
    if (!gotThumbnailInfo) {
        thumbnailInfo.fitResolutionToSize(x, y);
        gotThumbnailInfo = true;
    }
    
    
    g.setColour(Colours::deepskyblue);
    
    for (int i = 0; i < x; i++) {
        
        int drawSize = (thumbnailInfo.getPixelDrawValue(i)) * scale;
        if (drawSize > y) 
            drawSize = y;
        
        g.drawRect(i, (y / 2) - thumbnailInfo.getPixelDrawValue(i), 1, drawSize);
        //g.drawRect(i, 0, 1, i % y);
        
    }
    
    
    //label - add 1 to convert from index to human number. draw red if muted
    if (isMuted) {
        g.setColour(Colours::darkred);
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
    g.fillRect(x - 9, y - indicatorHeight, 9, indicatorHeight);
    
    //pan indicator
    int panIndicatorPosition = static_cast<int>(9.f - (9.f * pan));
    g.setColour(Colours::darkgrey);
    g.fillRect(x - panIndicatorPosition - 1, y - indicatorHeight, 1, indicatorHeight);
    
    
    //selected indicator
    if (isSelected) {
        g.setColour(Colours::deepskyblue);
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


void LayerGUI::setLayerIndex(int newIndex){
    
    layerIndex = newIndex;
}

void LayerGUI::setSelected(bool shouldBeSelected){
    
    isSelected = shouldBeSelected;
    repaint();
}

void LayerGUI::setGain(float newGain){
    
    gain = newGain;
    repaint();
}

void LayerGUI::setPan(float newPan){
    
    pan = newPan;
    repaint();
}

void LayerGUI::setMuted(float shouldBeMuted){
    
    isMuted = shouldBeMuted;
    repaint();
}

void LayerGUI::setScale(float newScale){
    
    scale = newScale;
    repaint();
}