#include "Arduino.h"
#include "GButton.h"

GButton::GButton(uint8_t pin)
{
 _pin=pin;
}
///////////////////////////// Флаг для одного клика и удержания
uint8_t GButton::tick()
{ 
 unsigned long _btnTimer = 0;
 unsigned long _tmr = millis();
 switch(_pin)
 {
  case 0:
   if(1000 > _btnTimer > 0 )
   {
    return 1;
   }
   else
   {
    _holdFlag = 0;
    return 0;
   }
   _btnTimer = 0;
   _tmr = millis();
   break;
  case 1:
   for(uint8_t i= 0; i=>0; i++)
   {
    _btnTimer = (millis()-_tmr);
    if(_btnTimer >= 1000)
    {
     _holdFlag = 1;
     return 2; 
    }
   }
   break;
 }
}
////////////////////////////
