#include "Arduino.h"
#include "GButton.h"

GButton::GButton(uint8_t pin)
{
 _pin=pin;
}
///////////////////////////// Флаг для одного клика и удержания
uint8_t GButton::click()
{
 switch(digitalRead(_pin))
 {
  case 0:
   if(!_pressFlag && _holdFlag && millis() - _btnTimer > 100 )
   {
    _btnTimer = millis();
    _holdFlag = false;
   }
   if(_pressFlag && _holdFlag)
   {
    _btnTimer = millis();
    _pressFlag = false;
    Serial.println("Нажатие");
   }
   else
   {
    return 0;
   }
   break;
  case 1:
   if(!_holdFlag && millis() - _btnTimer > 100 )
   {
    //Serial.println("Нажатие");
    _btnTimer = millis();
    _holdFlag = true;
    _pressFlag = true;
    return 1;
   }
   if(_holdFlag && millis() - _btnTimer > 1000 )
   {
    Serial.println("Удержание");
    _btnTimer = millis();
    _pressFlag = false;
    return 2;
   } 
   break;
 }
}
////////////////////////////
