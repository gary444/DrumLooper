//
//  ClearButton.h
//  DrumLooper
//
//  Created by Gareth Rendle on 15/11/2013.
//
//

#ifndef DrumLooper_ClearButton_h
#define DrumLooper_ClearButton_h

class ClearLayerButton : public TextButton
{
public:
    ClearLayerButton() : TextButton("Clear Layer", "click here to record")
    {
        setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight);
        setColour(TextButton::buttonColourId, Colours::grey);
        setColour(TextButton::buttonOnColourId, Colours::grey);
    }
private:
};


#endif
