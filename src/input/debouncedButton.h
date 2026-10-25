#include "Arduino.h"

// https://docs.arduino.cc/built-in-examples/digital/Debounce/
class DebouncedButton {
    public:
        explicit DebouncedButton(uint8_t pin)
            : _pin(pin),
              _stableState(HIGH),
              _lastReading(HIGH),
              _lastDebounceTime(0) {}
    
        void initialize() {
            pinMode(_pin, INPUT_PULLUP);
    
            // Initialize from the actual pin state so startup does not
            // generate a false button press.
            _stableState = digitalRead(_pin);
            _lastReading = _stableState;
        }
    
        // Returns true once when the button changes to the pressed state.
        bool wasPressed() {
            const int reading = digitalRead(_pin);
            const unsigned long now = millis();
    
            if (reading != _lastReading) {
                _lastDebounceTime = now;
                _lastReading = reading;
            }
    
            if ((now - _lastDebounceTime) >= BUTTON_DEBOUNCE_DELAY_MS &&
                reading != _stableState) {
                _stableState = reading;
    
                // INPUT_PULLUP means LOW is pressed.
                return _stableState == LOW;
            }
    
            return false;
        }
    
    private:
        static constexpr unsigned long BUTTON_DEBOUNCE_DELAY_MS = 50;
    
        uint8_t _pin;
        int _stableState;
        int _lastReading;
        unsigned long _lastDebounceTime;
};
