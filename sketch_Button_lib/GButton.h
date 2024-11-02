#pragma once

#include "Arduino.h"

class GButton
{
  public:
   GButton (uint8_t pin);
   
  private:
   bool doubleClick();
   uint8_t tick();
   bool _holdFlag;
   uint8_t _pin;
   unsigned long _tmr = millis();
   unsigned long _btnTimer = 0;
};
