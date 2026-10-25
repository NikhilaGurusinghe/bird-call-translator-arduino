#ifndef BIRD_CALL_TRANSLATOR_ICONS_H
#define BIRD_CALL_TRANSLATOR_ICONS_H

#include "Arduino.h"
class Icons {
    private: 
        byte DOWN_ARROW[8] = {
            B00000,
            B01110,
            B01110,
            B01110,
            B11111,
            B01110,
            B00100,
            B00000
        };
        byte CONFIRMATION_TICK[8] = {
            B00000,
            B00000,
            B00001,
            B00010,
            B10100,
            B01000,
            B00000,
            B00000
        };
        byte QUESTION_ICON[8] = {
            B10001,
            B00100,
            B01010,
            B00010,
            B00100,
            B00000,
            B00100,
            B10001
        };
        byte INFORMATION_ICON[8] = {
            B10001,
            B00000,
            B00100,
            B00000,
            B00100,
            B00100,
            B00100,
            B10001
        };
    
    public:
        byte* icons[8];

        Icons() : icons {
            DOWN_ARROW,
            CONFIRMATION_TICK,
            QUESTION_ICON,
            INFORMATION_ICON,
            nullptr,
            nullptr,
            nullptr,
            nullptr
        } {}

};



#endif //BIRD_CALL_TRANSLATOR_ICONS_H