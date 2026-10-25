// UI configuration for each screen -> singly linked list between main screens/uiConfigurations
// within each main page we can have multiple subpages which can be flipped through in a loop (use mod on size of array) 
// page configuration will just be two arrays (in a single array of the size of the screen) -> will have letters and numbers
//  in each spot, but for special characters from an icon use "@<index of icon">
// TODO this should probably be a more robust doubly linked list or something,
//  but for now its fine that this is just singly linked
#ifndef BIRD_CALL_TRANSLATOR_UIPAGE_H
#define BIRD_CALL_TRANSLATOR_UIPAGE_H

#include <Arduino.h>

class UIPage {
    public:
        UIPage(UIPage* nextPage,
                const String* leftNavigationPane,
                const String* rightNavigationPane,
                const size_t navigationPaneHeight,
                const String* staticTopPane,
                const size_t topAndBottomPaneSize,
                const String (*dynamicBottomPanes)[14],
                const size_t dynamicBottomPaneCount,
                bool isBottomPaneDynamic);

        UIPage* getNextPage();
        void setNextPage(UIPage* nextPage);

        const String* getLeftNavigationPane() const;
        const String* getRightNavigationPane() const;
        size_t getNavigationPaneHeight() const;
        
        const String* getStaticTopPane() const;

        // return the one and only bottom pane
        // useful if bottom pane is static
        // this returns a 14-wide array
        const String* getFirstBottomPane() const;
        // this should never out of bounds exception (segfault)
        // cause it should wrap around and around the _dynamicBottomPanes
        // array
        const String (*getDynamicBottomPanes() const)[14];
        const String* getDynamicBottomPanesByIndex(size_t paneIndex) const;
        size_t getDynamicBottomPaneCount() const;
        bool getIsBottomPaneDynamic() const;
        size_t getTopAndBottomPaneSize() const;

    

    private:
        UIPage* _nextPage;

        // Navigation components
        // position 0 is top most on specified side
        // position 1 is bottom most on specified side
        const String* _leftNavigationPane; // size 2
        const String* _rightNavigationPane; // size 2
        const size_t _navigationPaneHeight; // height of navpanes

        // static area on top
        const String* _staticTopPane; // size 14
        const size_t _topAndBottomPaneSize;
        // dynamic options area, this becomes dynamic when
        // we flip the isBottomPaneDynamic to true otherwise
        // this is just a 2 layer deep array with one element
        const String (*_dynamicBottomPanes)[14]; // array of size 14 string arrays
        const size_t _dynamicBottomPaneCount; // this cannot be set to 0
        const bool _isBottomPaneDynamic;

};


#endif //BIRD_CALL_TRANSLATE_UIPAGE_H
