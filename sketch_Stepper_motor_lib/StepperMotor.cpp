    #include "StepperMotor.h"
    StepperMotor::StepperMotor(int pin1, int pin2, int pin3, int pin4)
    {
      pinMode(pin1, OUTPUT);
      pinMode(pin2, OUTPUT);
      pinMode(pin3, OUTPUT);
      pinMode(pin4, OUTPUT);
      _motorPin1 = pin1;    // Blue   - 28BYJ48 pin 1
      _motorPin2 = pin2;    // Pink   - 28BYJ48 pin 2
      _motorPin3 = pin3;    // Yellow - 28BYJ48 pin 3
      _motorPin4 = pin4;    // Orange - 28BYJ48 pin 4
    }
    /////////////////////////// Вибрационный ход моторчика где right - шаги по часовой а left - против. Необходим для того что бы еда не застрявала в шнеке.
    void StepperMotor::vibroMovement (int right,int left)
    {
      for(int i=0;i<=(right+left);i++)
      {
        if (i<=right)
        {
          clockwise();
        }
        else
        { 
          anticlockwise();
        }
      }
    }
    ////////////////////// Ход моторчика по часовой стрелке
    void StepperMotor::clockwise()
    {
      for(int i = 0; i < 8; i++)
      {
        setOutput(i);
        delayMicroseconds(motorSpeed);
      }
    }
    //////////////////// Ход моторчика против часовой стрелки
    void StepperMotor::anticlockwise()
    {
      for(int i = 7; i >= 0; i--)
      {
        setOutput(i);
        delayMicroseconds(motorSpeed);
      }
    }
    //////////////////// Отработка по пинам для вращения моторчика по кругу. Значение out задействует 1 из 8 полушагов.
    void StepperMotor::setOutput(int out)
    {
      digitalWrite(_motorPin1, bitRead(_lookup[out], 0));
      digitalWrite(_motorPin2, bitRead(_lookup[out], 1));
      digitalWrite(_motorPin3, bitRead(_lookup[out], 2));
      digitalWrite(_motorPin4, bitRead(_lookup[out], 3));
    }
