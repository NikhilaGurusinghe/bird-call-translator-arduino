#ifndef BIRD_CALL_TRANSLATOR_ICONS_H
#define BIRD_CALL_TRANSLATOR_ICONS_H

#include "Arduino.h"
class Icons {
    private: 
        byte DOWN_ARROW[8] = {
            B11111,
            B10001,
            B10001,
            B10001,
            B00000,
            B10001,
            B11011,
            B11111
        };
        byte CONFIRMATION_TICK[8] = {
            B11111,
            B11111,
            B11110,
            B11101,
            B01011,
            B10111,
            B11111,
            B11111
        };
        byte QUESTION_ICON[8] = {
            B11111,
            B11011,
            B10101,
            B11101,
            B11011,
            B11111,
            B11011,
            B11111
        };
        byte INFORMATION_ICON[8] = {
            B11111,
            B10001,
            B10101,
            B11101,
            B11011,
            B11111,
            B11011,
            B11111
        };
        byte SOUNDWAVE_INTENSITY_XL[8] = {
            B01110,
            B01110,
            B01110,
            B01110,
            B01110,
            B01110,
            B01110,
            B11111
        };
        byte SOUNDWAVE_INTENSITY_LG[8] = {
            B00000,
            B01110,
            B01110,
            B01110,
            B01110,
            B01110,
            B00000,
            B11111
        };
        byte SOUNDWAVE_INTENSITY_MD[8] = {
            B00000,
            B00000,
            B01110,
            B01110,
            B01110,
            B00000,
            B00000,
            B11111
        };
        byte SOUNDWAVE_INTENSITY_SM[8] = {
            B00000,
            B00000,
            B00000,
            B01110,
            B00000,
            B00000,
            B00000,
            B11111
        };
    
    public:
        byte* icons[8];

        Icons() : icons {
            DOWN_ARROW,
            CONFIRMATION_TICK,
            QUESTION_ICON,
            INFORMATION_ICON,
            SOUNDWAVE_INTENSITY_XL,
            SOUNDWAVE_INTENSITY_LG,
            SOUNDWAVE_INTENSITY_MD,
            SOUNDWAVE_INTENSITY_SM
        } {}

};



#endif //BIRD_CALL_TRANSLATOR_ICONS_H