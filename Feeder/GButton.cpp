#include "Arduino.h"
#include "GButton.h"

enum getClickType {NOCLICK, ONECLICK, DOUBLECLICK, TRIPLECLICK, HOLD};

GButton::GButton(uint8_t pin)
{
 _pin=pin;
}
///////////////////////////// Флаг для одного клика или удержания
uint8_t GButton::getclickType()
{
 switch(digitalRead(_pin))
 {
  case 0:
   if(!_pressFlag && _holdFlag && millis() - _btnTimer > 50 ) /// Сброс флагов
   {
    _btnTimer = millis();
    if(millis()-_holdTimer>500)
    {
    holdTimer = millis()-_holdTimer;
    }
    _holdFlag = false;
    _timerFlag = true;
    return NOCLICK;
   }
   if(_pressFlag && _holdFlag) /// Нажатие на кнопку с удержанием 0,05 сек
   {
    _btnTimer = millis();
    _pressFlag = false;
    _clickCount ++;
   }
   if (millis() - _btnTimer > 200)
   {
    if (_clickCount > 3)
    {
      _clickCount = 3;
    }
    switch(_clickCount)
    {
      case 0:
      return NOCLICK;
      break;
      case 1:
      Serial.println("Нажатие");
      _clickCount = 0;
      return ONECLICK;
      break;
      case 2:
      Serial.println("Двойное нажатие");
      _clickCount = 0;
      return DOUBLECLICK;
      break;
      case 3:
      Serial.println("Тройное нажатие");
      _clickCount = 0;
      return TRIPLECLICK;
      break;
    }
    _clickCount = 0;
   }
   else /// Отсутствие нажатия
   {
    return NOCLICK;
   }
   break;
  case 1:
   if(!_holdFlag && millis() - _btnTimer > 50 ) /// Регистрация нажатия. Ничего не возвращает т.к. функция ждёт будет ли удержание или просто нажатие
   {
    _btnTimer = millis();
    _holdFlag = true; /// флаг удержания
    _pressFlag = true; /// флаг нажатия
   }
   if(_holdFlag && millis() - _btnTimer > 1000 ) /// Удержание кнопки более 0,5 сек.
   {
    Serial.println("Удержание");
    if(_timerFlag) /// Удержание кнопки более 0,5 сек.
    {
    _timerFlag = false;
    _holdTimer = millis();
    }
    _btnTimer = millis();
    _pressFlag = false;
     _clickCount = 0;
    return HOLD;
   }
   if(_timerFlag)
   {
    _timerFlag = false;
    _holdTimer = millis();
   }
 }
}
////////////////////////////