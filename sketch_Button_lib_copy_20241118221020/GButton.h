#pragma once

#include "Arduino.h"

class GButton
{

  public:
   GButton (uint8_t pin);
   uint8_t clickType(); ///// 1-click, 2-double, 3-triple, 4-hold
   uint32_t holdTimer;


  private:
   uint8_t _clickCount;
   uint8_t _pin;
   bool _holdFlag;
   bool _pressFlag;
   uint32_t _btnTimer;
   bool _timerFlag;
   uint32_t _holdTimer;
};
