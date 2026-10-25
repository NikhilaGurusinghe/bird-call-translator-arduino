#include "uiPage.h"

UIPage::UIPage(UIPage* nextPage,
    const String* leftNavigationPane,
    const String* rightNavigationPane,
    const size_t navigationPaneHeight,
    const String* staticTopPane,
    const size_t topAndBottomPaneSize,
    const String (*dynamicBottomPanes)[14],
    const size_t dynamicBottomPaneCount,
    bool isBottomPaneDynamic) : 
    _nextPage(nextPage),
    _leftNavigationPane(leftNavigationPane),
    _rightNavigationPane(rightNavigationPane),
    _navigationPaneHeight(navigationPaneHeight),
    _staticTopPane(staticTopPane),
    _topAndBottomPaneSize(topAndBottomPaneSize),
    _dynamicBottomPanes(dynamicBottomPanes),
    _dynamicBottomPaneCount(dynamicBottomPaneCount),
    _isBottomPaneDynamic(isBottomPaneDynamic) {}

UIPage* UIPage::getNextPage() {
    return _nextPage;
}

void UIPage::setNextPage(UIPage *nextPage) {
    _nextPage = nextPage;
}

const String* UIPage::getLeftNavigationPane() const {
    return _leftNavigationPane;
}

const String* UIPage::getRightNavigationPane() const {
    return _rightNavigationPane;
}

size_t UIPage::getNavigationPaneHeight() const {
    return _navigationPaneHeight;
}

const String* UIPage::getStaticTopPane() const {
    return _staticTopPane;
}

const String* UIPage::getFirstBottomPane() const {
    return _dynamicBottomPanes[0];
}

const String (*UIPage::getDynamicBottomPanes() const)[14] {
    return _dynamicBottomPanes;
}

const String* UIPage::getDynamicBottomPanesByIndex(size_t paneIndex) const {
    // wrap around using modulo (%) operator
    // so we should never have an invalid index/segfault
    size_t validPaneIndex = paneIndex % _dynamicBottomPaneCount;

       
    return _dynamicBottomPanes[validPaneIndex];
}

size_t UIPage::getDynamicBottomPaneCount() const {
    return _dynamicBottomPaneCount;
}

bool UIPage::getIsBottomPaneDynamic() const {
    return _isBottomPaneDynamic;
}

size_t UIPage::getTopAndBottomPaneSize() const {
    return _topAndBottomPaneSize;
}



