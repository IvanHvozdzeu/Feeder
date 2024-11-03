ifndef StepperMotor_h
#define StepperMotor_h

#include "Arduino.h"

class StepperMotor
{
  public:
    StepperMotor(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4);
    void vibroMovement(uint8_t right,uint8_t left);
    void clockwise();
    void anticlockwise();
    void _setOutput(uint8_t out);
    uint8_t motorSpeed = 1000;
    
  private:
   uint32_t _clcTimer;
   uint8_t _motorPin1;
   uint8_t _motorPin2;    
   uint8_t _motorPin3;    
   uint8_t _motorPin4;    
   uint8_t _lookup[8] = {B01000, B01100, B00100, B00110, B00010, B00011, B00001, B01001};
   uint8_t _lookupI;
   uint8_t vibroSteps;    
  };

  #endif
