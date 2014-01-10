//
//  ClearLayerButton.h
//  DrumLooper
//
//  Created by Gareth Rendle on 15/11/2013.
//
//

#ifndef DrumLooper_ClearLayerButton_h
#define DrumLooper_ClearLayerButton_h


class ClearLayerButton : public TextButton
{
public:
    ClearLayerButton() : TextButton("Clear Layer", "Clear Selected Layer")
    {
        setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight);
        setColour(TextButton::buttonColourId, Colours::deepskyblue);
        setColour(TextButton::buttonOnColourId, Colours::deepskyblue);
        //setColour(TextButton::textColourOnId, Colours::darkgrey);
        //setColour(TextButton::textColourOffId, Colours::darkgrey);
    }
private:
};

#endif
