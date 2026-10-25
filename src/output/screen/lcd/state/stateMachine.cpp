#include "StateMachine.h"

StateMachine::StateMachine(LCD lcdScreen, Icons customIcons, UIPage* uiPages) :
                            _icons(customIcons), _lcdScreen(lcdScreen), _currentUIPage(uiPages) {}

void StateMachine::update(bool buttonAPressed, bool buttonBPressed) {

    // can press both buttons at once
    if (buttonAPressed == true) {
        // only handle page turns if our _currentUIPage is has isBottomPaneDynamic == true
        // otherwise do nothing
        if (_currentUIPage->getIsBottomPaneDynamic() == true) {
            handlePageTurn();
        }

    } 
    
    if (buttonBPressed == true) {
        handleConfirm();
    }
}

void StateMachine::initialize() {
    _lcdScreen.initialize();
    _lcdScreen.clear();
    _lcdScreen.backlight();

    // TODO insert the custom icons from _icons into CGRAM
    // TODO get rid of this magic number and make it a constant somewhere
    for (uint8_t iconLocation = 0; iconLocation <= 7; iconLocation++) {
        byte* customIcon = _icons.icons[iconLocation];

        // if the icon isn't a null pointer then add it to our CGRAM
        if (customIcon != nullptr) {
            _lcdScreen.createChar(iconLocation, customIcon);
        }
    }

    _lcdScreen.home();
    drawEntireScreen();
}

bool StateMachine::tryParseIntoCustomIcon(String parseMe, uint8_t& customIconIndex) {
    // if string is of size 2 and has a first character as '@'
    // get 2nd character, check if that 2nd character can be parsed into an integer
    if (parseMe.length() == 2) {
        char firstCharacter = parseMe.charAt(0);
        char customIconIndexCharacter = parseMe.charAt(1);

        // since we can only store 8 things in CGRAM (i.e. 8 custom icons)
        // then we need to check if the second character is between 0 and 7
        if (firstCharacter == '@' && customIconIndexCharacter >= '0' && customIconIndexCharacter <= '7') {
            customIconIndex = customIconIndexCharacter - '0'; // TODO check if this is correct
            return true;
        }
    }

    return false;
}

void StateMachine::writeSingleToScreen(String characterOrCustomIcon) {
    uint8_t optionalCustomIconIndex;
    bool isCustomIcon = tryParseIntoCustomIcon(characterOrCustomIcon, optionalCustomIconIndex);

    if (isCustomIcon) {
        // print custom icon instead of string val
        _lcdScreen.write(optionalCustomIconIndex);
    } else {
        // we have a regular string to write
        _lcdScreen.print(characterOrCustomIcon.c_str());
    }
}


void StateMachine::handlePageTurn() {
    // increment and then wrap around if too large using mod
    _currentDynamicBottomPaneIndex = (_currentDynamicBottomPaneIndex + 1) % _currentUIPage->getDynamicBottomPaneCount();

    // redraw just the dynamic bottom pane
    drawDynamicBottomPane();
}

void StateMachine::handleConfirm() {
    // reset current count to 0
    _currentDynamicBottomPaneIndex = 0;

    // go to the next page
    _currentUIPage = _currentUIPage->getNextPage();

    // draw the entirety of the new page
    _lcdScreen.clear();
    drawEntireScreen();
}

void StateMachine::drawNavigationPaneHelper(const String* navigationPane, size_t navigationPaneHeight, uint8_t column) {
    for (size_t row = 0; row < navigationPaneHeight; row++) {
        _lcdScreen.setCursor(column, row);
        // draw stuff on row = row, col 0
        const String navPaneCharacter = navigationPane[row];
        // this'll be a single character to print out
        // might be a custom icon as well so we ave to check
        writeSingleToScreen(navPaneCharacter);
    }
}


void StateMachine::drawLeftNavigationPane() {
    drawNavigationPaneHelper(_currentUIPage->getLeftNavigationPane(),
    _currentUIPage->getNavigationPaneHeight(),
    0);
}

void StateMachine::drawRightNavigationPane() {
    drawNavigationPaneHelper(_currentUIPage->getRightNavigationPane(),
    _currentUIPage->getNavigationPaneHeight(),
    _currentUIPage->getTopAndBottomPaneSize() + 1); // TODO this hardcoding is bad
}

void StateMachine::drawTopOrBottomPaneHelper(const String *topOrBottomPane, size_t topOrBottomPaneWidth, uint8_t row) {
    // draw from col 1 to 14
    for (size_t col = 0; col < topOrBottomPaneWidth; col++) {
        _lcdScreen.setCursor(col, row);
        // character to write to screen
        const String topAndBottomPaneCharacter = topOrBottomPane[col];
        // TODO write to the screen
        writeSingleToScreen(topAndBottomPaneCharacter);
    }
}

void StateMachine::drawStaticTopPane() {
    const String* staticTopPane = _currentUIPage->getStaticTopPane();

    drawTopOrBottomPaneHelper(staticTopPane,
        _currentUIPage->getTopAndBottomPaneSize(),
        0);
}

void StateMachine::drawDynamicBottomPane() {
    
    if (_currentUIPage->getIsBottomPaneDynamic() == true) {
        // if current ui page has dynamic bottom
        // then we need to query all the available bottom panes using _currentDynamicBottomPaneIndex
        const String* currentBottomPane = _currentUIPage->getDynamicBottomPanesByIndex(_currentDynamicBottomPaneIndex);
        
        drawTopOrBottomPaneHelper(currentBottomPane, 
            _currentUIPage->getTopAndBottomPaneSize(),
             1);

    } else {
        // if the current ui page does not have a dynamic bottom
        // then just return the very first entry in it and draw that to screen
        const String* bottomPane = _currentUIPage->getFirstBottomPane();

        drawTopOrBottomPaneHelper(bottomPane,
            _currentUIPage->getTopAndBottomPaneSize(),
            1);
    }

}

void StateMachine::drawEntireScreen() {
    drawLeftNavigationPane();
    drawStaticTopPane();
    drawDynamicBottomPane();
    drawRightNavigationPane();
}





