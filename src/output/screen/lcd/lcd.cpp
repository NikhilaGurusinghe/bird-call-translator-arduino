
#include lcd.h


// Set the LCD address to 0x27 in PCF8574 by NXP and Set to 0x3F in PCF8574A by Ti
LCD::LCD(uint8_t lcdAddress, uint8_t lcdColumns, uint8_t lcdRows) : 
        _lcd(lcdAddress, lcdColumns, lcdRows)
{
}

void LCD::initialize() {
    _lcd.init();
}

void LCD::clear() {
    _lcd.clear();
}

void LCD::backlight() {
    _lcd.backlight();
}

void LCD::setCursor(uint8_t column, uint8_t row) {
    _lcd.setCursor(column, row);
}

void LCD::print(const char* string) {
    _lcd.print(string);
}

void LCD::home() {
    _lcd.home();
}