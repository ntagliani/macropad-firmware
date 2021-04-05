#pragma once 

/// Simple class to manage rotary encoder states
class RotaryEncoder{

  public:
  /// Constructor takes the rotary encoders pins to detect rotation
  RotaryEncoder(int pinA, int pinB);
  /// Initializes the rotary encorder
  void begin();

  /// Returns the state of  the rotary encorder:
  /// 0 is means still
  /// +1 rotating clockwise
  /// -1 rotating counter-clockwise
  int state();
  
  private:
  /// pin A address
  int  m_pinA;
  /// pin B address
  int  m_pinB;

  /// last observed state for pin A to detect start detecting a rotation
  int m_lastA;
  /// First observed state of pin A to detect changes only on that change of level
  int m_firstA;
};
