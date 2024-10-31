#include "StepperMotor.h"
StepperMotor motor(8,9,10,11);
void setup()
{
  Serial.begin(9600);
  
};
void loop()
{
  motor.clockwise();
};
