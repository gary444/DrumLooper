//
//  ClearLayerButton.h
//  DrumLooper
//
//  Created by Gareth Rendle on 15/11/2013.
//
//

#ifndef DrumLooper_ClearLayerButton_h
#define DrumLooper_ClearLayerButton_h

class ClearAllButton : public TextButton
{
public:
    ClearAllButton() : TextButton("Clear All", "click here to record")
    {
        setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight);
        setColour(TextButton::buttonColourId, Colours::grey);
        setColour(TextButton::buttonOnColourId, Colours::grey);
    }
private:
};


#endif
