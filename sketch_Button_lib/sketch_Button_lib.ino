#include "GButton.h"
#include "StepperMotor.h"

uint8_t pin = 7;
GButton button(pin);
StepperMotor motor(8,9,10,11);
uint32_t timer; 

void setup() 
{

 Serial.begin (9600);
 pinMode(8,INPUT);
}
void loop() 
{
 switch(button.clickType())
 {
  case 1:
  timer=millis();
  while(millis() - timer < button.holdTimer)
  {
  motor.vibroMovement(5,3);
  }
  break;
  case 2:
  timer=millis();
  while(millis() - timer < button.holdTimer)
  {
  motor.anticlockwise();
  }
  break;
  case 4:
  motor.vibroMovement(5, 3);
 }
}
/* uint8_t clickType()
{
 switch(digitalRead(pin))
 {
  case 0:
   if(!_pressFlag && _holdFlag && millis() - _btnTimer > 100 )
   {
    _btnTimer = millis();
    _holdFlag = false;
    return 0;
   }
   if(_pressFlag && _holdFlag)
   {
    _btnTimer = millis();
    _pressFlag = false;
    Serial.println("Нажатие");
    return 1;
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
} */
  case 0:
   if(!_pressFlag && _holdFlag && millis() - _btnTimer > 100 )
   {
    _btnTimer = millis();
    _holdFlag = false;
    return 0;
   }
   if(_pressFlag && _holdFlag)
   {
    _btnTimer = millis();
    _pressFlag = false;
    Serial.println("Нажатие");
    return 1;
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
} */
