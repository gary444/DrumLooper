//
//  PlayButton.h
//  DrumLooper
//
//  Created by Gareth Rendle on 05/11/2013.
//
//

#ifndef DrumLooper_PlayButton_h
#define DrumLooper_PlayButton_h

class PlayButton : public TextButton
{
public:
    PlayButton() : TextButton("u", "Click to play")
    {
        setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight);
        setColour(TextButton::buttonOnColourId, Colours::deepskyblue);
        setColour(TextButton::buttonColourId, Colours::steelblue);
        
    }
    Font 	getFont (){return Font ("Wingdings 3", jmin(getHeight(),getWidth())/1.5f, Font::plain);}
private:
};

#endif
