//
//  LayerGUI.cpp
//  DrumLooper
//
//  Created by Gareth Rendle on 05/11/2013.
//
//

#include "LayerGUI.h"

LayerGUI::LayerGUI(){
    
    layerId = 0;
}

LayerGUI::~LayerGUI(){
    
}

//ComponentCallbacks============================================================
void LayerGUI::resized(){
    
}
void LayerGUI::paint (Graphics &g){
    
    //bg fill
    g.setColour(Colours::lightblue);
    g.fillRoundedRectangle(0, 0, getWidth(), getHeight(), 3);
    
    //label
    g.setColour(Colours::black);
    String label;
    label << "Layer " << layerId + 1;
    g.drawSingleLineText(label, 10, getHeight() - 5);
}