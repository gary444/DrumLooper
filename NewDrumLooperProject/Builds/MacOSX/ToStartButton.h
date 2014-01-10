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
    ToStartButton() : TextButton("v", "Return play head to start")
    {
        setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight);
        //setColour(TextButton::buttonOnColourId, Colours::deepskyblue);
        setColour(TextButton::buttonColourId, Colours::steelblue);
        
    }
    Font 	getFont (){return Font ("Wingdings 3", jmin(getHeight(),getWidth())/1.5f, Font::plain);}
};

#endif
