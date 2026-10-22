#ifndef BIRD_CALL_TRANSLATOR_LCD_H
#define BIRD_CALL_TRANSLATOR_LCD_H

#include <Wire.h> 
// lcd screen driver library
#include <LiquidCrystal_I2C.h>



/**
 * This class is a wrapper around the LCD Display library that provides an interface for the operations
 * that you would perform with the display.
*/
class LCD {

    public:
        LCD(uint8_t lcdAddress, uint8_t lcdColumns, uint8_t lcdRows);
        void initialize();
        void clear();
        void backlight();
        void setCursor(uint8_t column, uint8_t row);
        void print(const char* string);
        void home();
   

    private: 
        LiquidCrystal_I2C _lcd;


}





#endif //BIRD_CALL_TRANSLATOR_LCD_H