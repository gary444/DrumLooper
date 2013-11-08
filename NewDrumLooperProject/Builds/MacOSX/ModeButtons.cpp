//
//  ModeButtons.cpp
//  DrumLooper
//
//  Created by Gareth Rendle on 08/11/2013.
//
//

#include "ModeButtons.h"

#define NUMBER_OF_MODES 3

ModeButtons::ModeButtons(){
    
    //init listener
    listener = nullptr;
    
    for (int i = 0; i < NUMBER_OF_MODES; i++) {
        
        //Button setup
        ToggleButton* newButton = new ToggleButton;
        //newButton->setRadioGroupId(1);
        newButton->addListener(this);
        
        if (i == 0) 
            newButton->setToggleState(true, dontSendNotification);
        else
            newButton->setToggleState(false, dontSendNotification);
        
        addAndMakeVisible(newButton);
        buttons.add(newButton);
        
        
        //Label setup
        String s;
        s << "Mode " << i + 1;
        Label* newLabel = new Label;
        
        newLabel->setText(s, dontSendNotification);
        addAndMakeVisible(newLabel);
        labels.add(newLabel);
    }
}
ModeButtons::~ModeButtons(){
    
}
//ComponentCallbacks============================================================
void ModeButtons::resized(){
    
    int buttonSize = 30;
    
    for (int i = 0; i < NUMBER_OF_MODES; i++){
        buttons[i]->setBounds(10, i * buttonSize, buttonSize, buttonSize);
        labels[i]->setBounds(0 + buttonSize, i * buttonSize, 100, buttonSize);
    }
    
}

void ModeButtons::paint (Graphics &g){
    
}

void ModeButtons::buttonClicked(Button* button){
    
    int buttonIndex = 0;
    
    //find which button was pressed...
    for (int i = 0; i < NUMBER_OF_MODES; i++) {
        if (button == buttons[i]) {
            //std::cout << "button " << i + 1 << "pressed\n";
            buttonIndex = i;
        }
    }
        
    for (int i = 0; i < NUMBER_OF_MODES; i++){
            
        //turn it on...
        if (i == buttonIndex) {
            buttons[i]->setToggleState(true, dontSendNotification);
            //std::cout << "button " << i + 1 << "on\n";
        }
        //and turn others off.
        else
            buttons[i]->setToggleState(false, dontSendNotification);
            //std::cout << "button " << i + 1 << "off\n";
    }
    
    //inform listener!
    if (listener != nullptr)
    {
        listener->newModeSelected(buttonIndex);
        //std::cout << "buttons say mode " << buttonIndex + 1 << "selected\n";
    }
    
    
}

void ModeButtons::addListener(Listener* newListener){
    
    listener = newListener;
}