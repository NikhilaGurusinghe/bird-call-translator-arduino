#ifndef BIRD_CALL_TRANSLATOR_STATEMACHINE_H
#define BIRD_CALL_TRANSLATOR_STATEMACHINE_H

#include <Arduino.h>

#include "output/screen/lcd/lcd.h"
#include "output/screen/lcd/icons.h"

class StateMachine {
    // want to track the current icons set to be inserted into CGRAM
    // want the LCD object 
    // want UI configuration for each screen -> singly linked list between main screens
    public:
        StateMachine(LCD lcdScreen, Icons customIcons);
        // handling button input should change the state
        void update(bool buttonAPressed, bool buttonBPressed);


    private:
        Icons _icons;
        LCD _lcdScreen;
};


#endif //BIRD_CALL_TRANSLATOR_STATEMACHINE_H