//
//  AlternateLoopRecordButton.h
//  DrumLooper
//
//  Created by Gary Rendle on 05/01/2014.
//
//

#ifndef DrumLooper_AlternateLoopRecordButton_h
#define DrumLooper_AlternateLoopRecordButton_h

class AlternateLoopRecordButton : public TextButton
{
public:
    AlternateLoopRecordButton() : TextButton("Record On Alternate Cycles", "Click to record layers on alternate cycles, rather than every cycle")
    {
        setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight);
        setColour(TextButton::buttonColourId, Colours::grey);
        setColour(TextButton::buttonOnColourId, Colours::deepskyblue);
    }
private:
};

#endif
