#include "Keyboard.h"

#include "rotaryencoder.h"
#include "rgbanimation.h"

#define SERIAL_DEBUG 1

#define ROWS 3
#define COLS 4

const int* col_pins[COLS] = {4,5,6,7};
const int* row_pins[ROWS] = {8,9,10};
const char* values[COLS*ROWS]  = {
  'a', 'b', 'c', 'd',
  'e', 'f', 'g', 'h',
  'i', 'j', 'k', 'l'
  };


unsigned long pressed_times[COLS*ROWS];
unsigned long last_observed_state[COLS*ROWS];
unsigned long button_state[COLS*ROWS];


RotaryEncoder rot0(14,16);
RgbAnimation<3> rgbanimation;


void setup() {
  
  for (int i = 0; i < COLS; i++){
    pinMode(col_pins[i], OUTPUT);
    digitalWrite(col_pins[i], HIGH);
  }
  for (int i = 0; i < ROWS; i++){
    pinMode(row_pins[i], INPUT_PULLUP);
  }

  for (int i = 0; i < ROWS*COLS; i++){
    last_observed_state[i] = HIGH;
    button_state[i] = HIGH;
  }

  rot0.begin();

#if SERIAL_DEBUG
  Serial.begin(9600);
#endif

  Keyboard.begin();

  rgbanimation.begin();

  rgbanimation.setAnimation(None, CRGB::Green, CRGB::Green);
}

void loop() {
  
/*
    rgbanimation.led(0) = CRGB::Red;
    rgbanimation.led(1) = CRGB::Blue;
    rgbanimation.led(2) = CRGB::Green;
  */
    rgbanimation.show();
  
   for (int c = 0; c < COLS; c++){
    digitalWrite(col_pins[c], LOW);
    for (int r = 0; r < ROWS; r++){
      int pin_read = digitalRead(row_pins[r]);
      int offset = COLS * r + c;
      if (pin_read != last_observed_state[offset]){
#if SERIAL_DEBUG
        Serial.println("Pin state changed");
#endif
        pressed_times[offset] = millis();
      }
      if ((millis() - pressed_times[offset]) > 50){
        // confirm the state of the button in here
        if (pin_read != button_state[offset]){
          // observed state is different from current state
#if SERIAL_DEBUG
          Serial.println("State is different from last observed");
#endif
          button_state[offset] = pin_read;
        
          if (button_state[offset] == LOW){
#if SERIAL_DEBUG
            Serial.println("State observed is LOW");
#endif
            Keyboard.write(values[offset]);

          }
        } else {
          // button state is not changing for long time
          if ((millis() - pressed_times[offset]) > 500){
            // Artificial reset to high state to be able simulate new presses (one every 500ms)
            button_state[offset] = HIGH;
          }
        }
      }
      last_observed_state[offset] = pin_read;
     }

    digitalWrite(col_pins[c], HIGH);
  }
  int rot_enc0 = rot0.state();
  if (rot_enc0 != 0){
    if (rot_enc0 == 1){
      Serial.println("Clockwise");
    } else{
     Serial.println("Counter-lockwise");
    }
  }


}
