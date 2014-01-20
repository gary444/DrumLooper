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
    
    
    //g.setColour(Colours::grey.withAlpha(0.2f));
    tabbedComponent->addTab("Mode Select", Colours::grey.withAlpha(0.4f), newButtons, true);
    
    ModeInfo* info = new ModeInfo;
    tabbedComponent->addTab("Mode Info", Colours::grey.withAlpha(0.4f), info, true);
    
    tabbedComponent->setColour(TabbedComponent::outlineColourId, Colours::deepskyblue);
    
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

void ModeSelecter::setEnabled(bool shouldBeEnabled){
    
    tabbedComponent->setEnabled(shouldBeEnabled);
}


void ModeSelecter::setModeFromKeypress(int newModeIndex){
    
//    ModeButtons* c = tabbedComponent->getTabContentComponent(0);
//    c->ModeButtons::setModeFromKeypress(newModeIndex);
    
}