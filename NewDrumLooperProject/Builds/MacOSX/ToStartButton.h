//
//  ToStart.h
//  DrumLooper
//
//  Created by Gary Rendle on 01/12/2013.
//
//

#ifndef DrumLooper_ToStart_h
#define DrumLooper_ToStart_h

class ToStartButton : public TextButton {
    
public:
    ToStartButton() : TextButton("v", "return play head to start")
    {
        setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight);
        setColour(TextButton::buttonColourId, Colours::grey);
        setColour(TextButton::buttonOnColourId, Colours::lightgrey);
        
    }
    Font 	getFont (){return Font ("Wingdings 3", jmin(getHeight(),getWidth())/1.5f, Font::plain);}
};

#endif
