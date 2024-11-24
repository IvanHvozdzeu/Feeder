#pragma once

#include "Arduino.h"

class GButton
{
  public:
   GButton (uint8_t pin);
   uint8_t getclickType(); ///// 1-click, 2-double, 3-triple, 4-hold
   unsigned long holdTimer;


  private:
   uint8_t _clickCount;
   uint8_t _pin;
   bool _holdFlag;
   bool _pressFlag;
   unsigned long _btnTimer;
   bool _timerFlag;
   unsigned long _holdTimer;
};


