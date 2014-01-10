//
//  ClearButton.h
//  DrumLooper
//
//  Created by Gareth Rendle on 15/11/2013.
//
//

#ifndef DrumLooper_ClearButton_h
#define DrumLooper_ClearButton_h

class ClearAllButton : public TextButton
{
public:
    ClearAllButton() : TextButton("Clear All", "Clear All Layers")
    {
        setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight);
        setColour(TextButton::buttonColourId, Colours::deepskyblue);
        setColour(TextButton::buttonOnColourId, Colours::deepskyblue);
    }
private:
};




#endif
