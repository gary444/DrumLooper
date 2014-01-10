//
//  AudioSetupButton.h
//  DrumLooper
//
//  Created by Gary Rendle on 13/12/2013.
//
//

#ifndef DrumLooper_AudioSetupButton_h
#define DrumLooper_AudioSetupButton_h


class AudioSetupButton : public TextButton
{
public:
    AudioSetupButton() : TextButton("Audio Setup", "Click to show audio setup options")
    {
        setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight);
        setColour(TextButton::buttonColourId, Colours::deepskyblue);
        setColour(TextButton::buttonOnColourId, Colours::deepskyblue);
    }
private:
};

#endif
