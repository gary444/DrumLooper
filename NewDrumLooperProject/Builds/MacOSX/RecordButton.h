//
//  RecordButton.h
//  DrumLooper
//
//  Created by Gareth Rendle on 05/11/2013.
//
//

#ifndef DrumLooper_RecordButton_h
#define DrumLooper_RecordButton_h

class RecordButton : public TextButton
{
public:
    RecordButton() : TextButton("l", "click here to record")
    {
        setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight);
        setColour(TextButton::buttonColourId, Colours::darkred);
        setColour(TextButton::buttonOnColourId, Colours::red);
    }
    Font 	getFont (){return Font ("Wingdings", jmin(getHeight(),getWidth())/1.5f, Font::plain);}
private:
};

#endif
