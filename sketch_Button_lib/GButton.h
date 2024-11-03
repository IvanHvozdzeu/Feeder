#pragma once

#include "Arduino.h"

class GButton
{
  public:
   GButton (uint8_t pin);
   uint8_t click();
   int doubleClick();
  private:
   uint8_t _clickCount;
   uint8_t _pin;
   bool _holdFlag;
   bool _pressFlag;
   uint32_t _btnTimer;
};
