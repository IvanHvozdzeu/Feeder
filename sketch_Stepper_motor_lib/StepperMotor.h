#pragma once
#include "Arduino.h"
class StepperMotor
{
  public:
    StepperMotor(int pin1, int pin2, int pin3, int pin4);
    vibroMovement(int right,int left);
    clockwise();
    anticlockwise();
    int motorSpeed = 1200;
  private:
    int _motorPin1;    // Blue   - 28BYJ48 pin 1
    int _motorPin2;    // Pink   - 28BYJ48 pin 2
    int _motorPin3;    // Yellow - 28BYJ48 pin 3
    int _motorPin4;    // Orange - 28BYJ48 pin 4
    int _lookup[8] = {B01000, B01100, B00100, B00110, B00010, B00011, B00001, B01001}; /////////Массив со значениями (8,12,4,6,2,3,1,9)
    setOutput(int out); 
  };