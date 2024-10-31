#include "StepperMotor.h"

void setup()
{
  Serial.begin(9600);
  StepperMotor.setMotorPins(8,9,10,11);
};
void loop()
{
  StepperMotor.clockwise();
};