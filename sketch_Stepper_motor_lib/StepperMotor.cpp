#include "Arduino.h"
    #include "StepperMotor.h"

    StepperMotor::StepperMotor(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4)
    {
      pinMode(pin1, OUTPUT);
      pinMode(pin2, OUTPUT);
      pinMode(pin3, OUTPUT);
      pinMode(pin4, OUTPUT);
      _motorPin1 = pin1;    
      _motorPin2 = pin2;    
      _motorPin3 = pin3;    
      _motorPin4 = pin4;    
    }
    /////////////////////////// Вибрационный ход моторчика где right - шаги по часовой а left - против. Необходим для того что бы еда не застрявала в шнеке.
    void StepperMotor::vibroMovement (uint8_t right,uint8_t left)
    {
     if(micros() - _clcTimer > motorSpeed)
     {
        if (vibroSteps < right)
        {
          _clcTimer = micros();
          vibroSteps ++;
          _stepPos ++;
          //Serial.println (vibroSteps);
          if(_stepPos > 7)
          {
            _stepPos = 0;
          }
          //Serial.println (_lookupI);
          _setOutput(_stepPos);
        }
     }
     if(micros() - _clcTimer > motorSpeed)
     {
        if (right <= vibroSteps)
        {
          _clcTimer = micros();
          _stepPos --;
          if(_stepPos < 0)
          {
           _stepPos = 7;
          }
          vibroSteps ++;
          _setOutput(_stepPos);
          //Serial.println (_lookupI);
          //Serial.println (vibroSteps);
          
          
        }
        if(vibroSteps == right+left)
          {
            vibroSteps = 0;
          }
      }
    }
    ////////////////////// Ход моторчика по часовой стрелке
    void StepperMotor::clockwise()
    { 
     if(micros() - _clcTimer > motorSpeed)
     {
      _clcTimer = micros();
      if(_stepPos == 8)
      {
       _stepPos = 0;
      }
      //Serial.println (_lookupI);
      _setOutput(_stepPos);
      _stepPos = _stepPos + 1;   
     } 
    }
    //////////////////// Ход моторчика против часовой стрелки
    void StepperMotor::anticlockwise()
    {
      
        if(micros() - _clcTimer > motorSpeed)
        {
         _clcTimer = micros();
         
        _stepPos = _stepPos - 1;
        if(_stepPos < 0)
         {
          _stepPos = 7;
         }   
        _setOutput(_stepPos);
        //Serial.println (_lookupI);
        }
    }
    //////////////////// Отработка по пинам для вращения моторчика по кругу. Значение out задействует 1 из 8 положений драйвера.
    void StepperMotor::_setOutput(uint8_t out)
    {
      digitalWrite(_motorPin1, bitRead(_step[out], 0));
      digitalWrite(_motorPin2, bitRead(_step[out], 1));
      digitalWrite(_motorPin3, bitRead(_step[out], 2));
      digitalWrite(_motorPin4, bitRead(_step[out], 3));
    }
