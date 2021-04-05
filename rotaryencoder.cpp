#include "rotaryencoder.h"
#include "Arduino.h"

  RotaryEncoder::RotaryEncoder(int pinA, int pinB):m_pinA(pinA), m_pinB(pinB){}
 
  void RotaryEncoder::begin(){
    pinMode(m_pinA, INPUT_PULLUP);
    pinMode(m_pinB, INPUT_PULLUP);
    m_lastA = digitalRead(m_pinA);
    m_firstA = m_lastA;
  }

  int RotaryEncoder::state(){
    const int new_state = digitalRead(m_pinA);
    int ret = 0;
    if (new_state != m_lastA){
      if (new_state != m_firstA){
        int b_state = digitalRead(m_pinB);
        if (b_state == new_state){
          ret = 1;
        } else {
          ret = -1;
        }
      }
      m_lastA = new_state;
    }
    return ret;
  }
  
