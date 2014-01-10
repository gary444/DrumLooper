//
//  MuteButton.h
//  sdaAssignment
//
//  Created by Gareth Rendle on 15/02/2013.
//
//

#ifndef DrumLooper_MuteButton_h
#define DrumLooper_MuteButton_h

class MuteButton : public TextButton
{
public:
    MuteButton() : TextButton("M", "Mute/Unmute selected channel") {
    
    setColour(TextButton::buttonColourId, Colours::darkred);
    setColour(TextButton::buttonOnColourId, Colours::red);
    //setColour(TextButton::textColourOffId, Colours::darkgrey);
    //setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight);
    }
    
};

#endif
