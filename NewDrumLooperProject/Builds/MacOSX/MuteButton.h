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
    MuteButton() : TextButton("Mute", "click to mute this channel") {
    
    setColour(TextButton::buttonColourId, Colours::darkred);
    setColour(TextButton::buttonOnColourId, Colours::red);
    setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight);
    }
    
};

#endif
