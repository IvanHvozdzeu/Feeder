#pragma once

#include "Arduino.h"

class GButton
{
  public:
   GButton (uint8_t pin);
   
  private:
   bool doubleClick();
   uint8_t click();
   uint8_t _pin;
   bool _holdFlag;
   bool _pressFlag;
   uint32_t _btnTimer;
};
