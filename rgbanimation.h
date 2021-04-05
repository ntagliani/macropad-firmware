#pragma once 

#include "FastLED.h"

enum AnimationType {
  None,
  Still,
  Breath,
  Horizontal,
  HorizantalAndBack,
  Vertical,
  VerticalAndBack
};


/// Simple class manage at high level the animations.
/// Each animation is defined by a name a main color and a secondary color
template<uint32_t N>
class RgbAnimation {
public:
  uint32_t rgbLeds() const {return N;}

  void begin(){
    for (int i = 0; i < N; i++){
      m_led_order[i] = i;
    }
    FastLED.addLeds<NEOPIXEL, A1>(m_leds, N);
    m_time = millis();
  }
  
  void show(){
    const auto curr_time = millis();
    performAnimation(curr_time - m_time);
    FastLED.setBrightness(64);
    FastLED.show(); 
    m_time = curr_time;
  }

  CRGB& led(uint32_t idx){
    return m_leds[m_led_order[idx]];
  }
  
   void setAnimation(AnimationType type, CRGB main_color, CRGB secondary_color){
     m_animation = type;
     m_main_color = main_color;
     m_secondary_color = secondary_color;
   }
   
private:

  /// advance the animation by delta_t milliseconds
  void performAnimation(uint32_t delta_t){
    switch(m_animation){
      case None:
      default:
        displayNone();
        break;
       case Still:
        displayStill();
        break;
    }
  }

  void displayNone(){
    for (int i = 0; i < N; i++){
      led(i) = CRGB::Black;
    }
  }

    void displayStill(){
    for (int i = 0; i < N; i++){
      led(i) = m_main_color;
    }
  }
  
  uint8_t m_led_order[N];
  CRGB m_leds[N];
  uint32_t m_time;
  AnimationType m_animation{None};
  CRGB m_main_color{CRGB::Red};
  CRGB m_secondary_color{CRGB::White};
  
};
