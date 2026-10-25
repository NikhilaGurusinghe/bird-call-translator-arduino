#include "StateMachine.h"

StateMachine::StateMachine(LCD lcdScreen, Icons customIcons, UIPage* uiPages) :
                            _icons(customIcons), _lcdScreen(lcdScreen), _currentUIPage(uiPages) {}

void StateMachine::update(bool buttonAPressed, bool buttonBPressed) {

    // increment _currentDynamsicBottomPaneIndex

    if (buttonAPressed == true) {
        // only handle page turns if our _currentUIPage is has isBottomPaneDynamic == true
        // otherwise do nothing
        if (_currentUIPage->getIsBottomPaneDynamic() == true) {
            handlePageTurn();
        }

    } else if (buttonBPressed == true) {
        handleConfirm();
    }
}

void StateMachine::initialize() {
    _lcdScreen.initialize();
    _lcdScreen.clear();
    _lcdScreen.backlight();
}


void StateMachine::handlePageTurn() {
    // increment and then wrap around if too large using mod
    _currentDynamicBottomPaneIndex = (_currentDynamicBottomPaneIndex + 1) % _currentUIPage->getDynamicBottomPaneCount();
}

void StateMachine::handleConfirm() {
    // reset current count to 0
    _currentDynamicBottomPaneIndex = 0;

    // go to the next page
    _currentUIPage = _currentUIPage->getNextPage();
}

void StateMachine::drawNavigationPaneHelper(const String* navigationPane, size_t navigationPaneHeight, uint8_t column) {
    for (size_t row = 0; row < navigationPaneHeight; row++) {
        _lcdScreen.setCursor(0, row);
        // draw stuff on row = row, col 0
        const String navPaneCharacter = navigationPane[row];
        // this'll be a single character to print out
        // might be a custom icon 
        // TODO write to screen
    
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
        

    }
}

void StateMachine::drawStaticTopPane() {
    const String* staticTopPane = _currentUIPage->getStaticTopPane();

    drawTopOrBottomPaneHelper(staticTopPane, _currentUIPage->getTopAndBottomPaneSize(), 0);
}





