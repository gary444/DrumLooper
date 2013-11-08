//
//  ModeSelecter.cpp
//  DrumLooper
//
//  Created by Gareth Rendle on 08/11/2013.
//
//

#include "ModeSelecter.h"

ModeSelecter::ModeSelecter(){
    
    listener = nullptr;
    
    tabbedComponent = new TabbedComponent(TabbedButtonBar::Orientation::TabsAtTop);
    addAndMakeVisible(tabbedComponent);
    
    ModeButtons* newButtons = new ModeButtons;
    newButtons->addListener(this);
    tabbedComponent->addTab("Mode Select", Colours::whitesmoke, newButtons, true);
    
    ModeInfo* info = new ModeInfo;
    tabbedComponent->addTab("Mode Info", Colours::whitesmoke, info, true);
    
}
ModeSelecter::~ModeSelecter(){
    
    tabbedComponent = nullptr;
}
void ModeSelecter::resized(){
    
    tabbedComponent->setBounds(0, 0, getWidth(), getHeight());
}
//void ModeSelecter::paint(Graphics &g){
    
//}

void ModeSelecter::addListener(Listener* newListener){
    
    listener = newListener;
}
void ModeSelecter::newModeSelected(int modeIndex){
    
    if (listener != nullptr) 
        listener->newModeSelected(modeIndex);
}