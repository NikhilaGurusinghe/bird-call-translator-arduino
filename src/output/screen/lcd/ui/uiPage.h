// UI configuration for each screen -> singly linked list between main screens/uiConfigurations
// within each main page we can have multiple subpages which can be flipped through in a loop (use mod on size of array) 
// page configuration will just be two arrays (in a single array of the size of the screen) -> will have letters and numbers
//  in each spot, but for special characters from an icon use "@<index of icon">

#ifndef BIRD_CALL_TRANSLATOR_UIPAGE_H
#define BIRD_CALL_TRANSLATOR_UIPAGE_H

#include <Arduino.h>

class UIPage {
    public:
        UIPage(UIPage* nextPage,
                const String* leftNavigationPane,
                const String* rightNavigationPane,
                const String* staticTopPane,
                const String* dynamicBottomPanes,
                bool isBottomPaneDynamic);

        const String* getLeftNavigationPane() const;
        const String* getRightNavigationPane() const;
        
        const String* getStaticTopPane() const;

        // return the one and only bottom pane
        // useful if bottom pane is static
        const String* getFirstBottomPane() const;
        // this should never out of bounds exception (segfault)
        // cause it should wrap around and around the _dynamicBottomPanes
        // array
        const String (*getDynamicBottomPanes(int paneIndex) const)[14];
        size_t getDynamicBottomPaneCount() const;
        bool getIsBottomPaneDynamic() const;

    

    private:
        UIPage* _nextPage;

        // Navigation components
        // position 0 is top most on specified side
        // position 1 is bottom most on specified side
        const String* _leftNavigationPane; // size 277
        const String* _rightNavigationPane; // size 2

        // static area on top
        const String* _staticTopPane; // size 14
        // dynamic options area, this becomes dynamic when
        // we flip the isBottomPaneDynamic to true otherwise
        // this is just a 2 layer deep array with one element
        const String (*_dynamicBottomPanes)[14]; // array of size 14 string arrays
        const size_t _dynamicBottomPaneCount;
        const bool _isBottomPaneDynamic;

};


#endif //BIRD_CALL_TRANSLATE_UIPAGE_H
