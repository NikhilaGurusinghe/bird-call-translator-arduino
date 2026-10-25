#ifndef BIRD_CALL_TRANSLATOR_STATEMACHINE_H
#define BIRD_CALL_TRANSLATOR_STATEMACHINE_H

#include <Arduino.h>

#include "output/screen/lcd/ui/uiPage.h"
#include "output/screen/lcd/lcd.h"
#include "output/screen/lcd/icons.h"

class StateMachine {
    // want to track the current icons set to be inserted into CGRAM
    // want the LCD object 
    // want UI configuration for each screen -> singly linked list between main screens
    public:
        StateMachine(LCD lcdScreen, Icons customIcons, UIPage* uiPages);
        // handling button input should change the state
        void update(bool buttonAPressed, bool buttonBPressed);

        // This is mostly to initialize all the stuff in the screen
        // as the screen should be put into the constructor of this
        // class with no prior initialization
        void initialize();



    private:
        Icons _icons;
        LCD _lcdScreen;
        UIPage* _currentUIPage;

        // state stuff
        size_t _currentDynamicBottomPaneIndex = 0;

        // method to parse the strings in UIPage
        // to differentiate between "@<index of icon>"
        // and regular character to print to screen

        // button handle methods
        void handlePageTurn();
        void handleConfirm(); // this will just navigate to the next page
        
        // methods to draw different parts of the interfaces
        void drawNavigationPaneHelper(const String* navigationPane, size_t navigationPaneHeight, uint8_t column);
        void drawLeftNavigationPane();
        void drawRightNavigationPane();
        void drawTopOrBottomPaneHelper(const String* topOrBottomPane, size_t topOrBottomPaneWidth, uint8_t row);
        void drawStaticTopPane();
        void drawDynamicBottomPane();
        
};


#endif //BIRD_CALL_TRANSLATOR_STATEMACHINE_H