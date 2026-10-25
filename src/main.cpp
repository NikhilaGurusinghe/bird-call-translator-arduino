#include "output/screen/lcd/icons.h"
#include "output/screen/lcd/lcd.h"
#include "output/screen/lcd/state/stateMachine.h"
#include "output/screen/lcd/ui/uiPage.h"
#include <Arduino.h>

#define SERIAL_BAUD_RATE 9600

#define DOWN_BUTTON_PIN 2
#define SELECT_BUTTON_PIN 3
#define VIBRATION_PIN 4
#define PIEZO_PIN 5

// "FF" is a fully illuminated character, " " is blank
// learning screen dependencies
const size_t navPaneHeight = 2;
const String learningScreen_LeftNavPane[navPaneHeight] = {"@3", "FF"};
const String rightNavPane[navPaneHeight] = {"FF", "@1"};
const size_t topAndBottomPaneSize = 14;
const String StaticTopPane[topAndBottomPaneSize] = {"@5", "@6", "@7", "@4",
                                               "@4", "@7", "@6", "@6", 
                                               "@5", "@6", "@7", "@6",
                                              "@4", "@5"};
const String learningScreen_DynamicBottomPanes[][topAndBottomPaneSize] = {{ " ", " ",
   "k", "e", "e", "p",
    " ",
     "a", "w", "a", "y", "!",
      " ", " " }};
const size_t learningScreen_DynamicBottomPaneCount = 1;
bool learningScreen_IsBottomPaneDynamic = false;
UIPage learningScreen(nullptr,
   learningScreen_LeftNavPane, rightNavPane, navPaneHeight,
    StaticTopPane, topAndBottomPaneSize, 
    learningScreen_DynamicBottomPanes, learningScreen_DynamicBottomPaneCount,
    learningScreen_IsBottomPaneDynamic);

// quiz screen dependencies
const String quizScreen_LeftNavPane[navPaneHeight] = {"@2", "@0"};
const String quizScreen_DynamicBottomPanes[][topAndBottomPaneSize] = {
  {" ", "  ", "o", "p", "t", "i", "o", "n", " ", "#", "1", " ", " ", " "},
  {" ", "  ", "o", "p", "t", "i", "o", "n", " ", "#", "2", " ", " ", " "},
  {" ", "  ", "o", "p", "t", "i", "o", "n", " ", "#", "3", " ", " ", " "},
};
const size_t quizScreen_DynamicBottomPaneCount = 3;
bool quizScreen_IsBottomPaneDynamic = true;
UIPage quizScreen(nullptr,
  quizScreen_LeftNavPane, rightNavPane, navPaneHeight,
  StaticTopPane, topAndBottomPaneSize,
  quizScreen_DynamicBottomPanes, quizScreen_DynamicBottomPaneCount,
quizScreen_IsBottomPaneDynamic);

// init state machine dependencies
LCD lcd(0x27, 16, 2);
Icons customIcons;
StateMachine stateMachine(lcd, customIcons, &learningScreen);

// button related
int lastDownButtonState = LOW;
int lastSelectButtonState = LOW;

void setup()
{
  Serial.begin(SERIAL_BAUD_RATE);

  // initialize pins
  pinMode(DOWN_BUTTON_PIN, INPUT_PULLUP);
  pinMode(SELECT_BUTTON_PIN, INPUT_PULLUP);
  // pinMode(PIEZO_PIN, OUTPUT);

  // loop screens around so hitting confirm button keeps them
  // alternating infinitely
  learningScreen.setNextPage(&quizScreen);
  quizScreen.setNextPage(&learningScreen);

  // then initialize the state machine
  stateMachine.initialize();
}

void loop()
{
  int currDownButtonState = digitalRead(DOWN_BUTTON_PIN);
  int currSelectButtonState = digitalRead(SELECT_BUTTON_PIN);

  // previous press was off and current press is on
  // this stops holding down the button from triggering button presses
  bool wasDownButtonPressed = currDownButtonState == HIGH && lastDownButtonState == LOW;
  bool wasSelectButtonPressed = currSelectButtonState == HIGH && lastSelectButtonState == LOW;

  stateMachine.update(wasDownButtonPressed, wasSelectButtonPressed);
}