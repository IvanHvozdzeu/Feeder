#include "GButton.h"
#include "StepperMotor.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DS3231.h>

int buttonPin1 = 6;
int buttonPin2 = 7;

uint8_t hour[2];
uint8_t min[2];
uint8_t sec[2];
GButton button1(buttonPin1);
GButton button2(buttonPin2);
LiquidCrystal_I2C lcd(0x27,16,2);
DS3231 RTC;
bool h12Flag = false;
bool pmFlag;
bool setTimeFlag;


void setup() 
{
 Wire.begin();
 lcd.init();
 lcd.clear();
 Serial.begin (9600);
 pinMode(6,INPUT);
 pinMode(7,INPUT);
 lcd.backlight();
 setTimeFlag = 0;
/*  lcd.backlight();
 lcd.setCursor(2,0);
 lcd.print("Hello, VAFLIA!");
 lcd.setCursor(2,1);
 lcd.print("I Love YOU!"); */
}
void loop() {
timeInit();
if(setTimeFlag == 0)
{
  timeViev();
}

if(button2.clickType() == 4 && button1.clickType() == 4)
{
 setTime();
};
}

/////////////////////////////////////////

void timeViev()
{
  lcd.setCursor(0,0);
  lcd.print(hour[0], DEC);
  lcd.print(hour[1], DEC);
	lcd.print(":");
	lcd.print(min[0], DEC);
  lcd.print(min[1], DEC);
	lcd.print(":");
	lcd.print(sec[0], DEC);
  lcd.print(sec[1], DEC);
}

void resetTime()
{
  bool timeStop = 1;
  for(int i=0; i<1;i++)
  {
  RTC.setHour(0);
  RTC.setMinute(0);
  RTC.setSecond(1);
  };
}
void setTime()
{
 uint8_t cursor = 0;
 uint8_t _hour[2]{0,0};
 uint8_t _min[2]{0,0};
 uint8_t _sec[2]{0,0};
 setTimeFlag = 1;
 lcd.clear();
 lcd.print("00:00:00");
 lcd.setCursor(cursor, 0);
 lcd.blink();
 while(cursor < 8){
  if(button2.clickType() == 1)
  {
   if (cursor == 0)
   {
    _hour[0]++;
    if (_hour[0] > 2){_hour[0]=0;}
    lcd.print(_hour[0]);
    lcd.setCursor(cursor, 0);
   }
   if (cursor == 1)
   {
    lcd.setCursor(cursor, 0);
    _hour[1]++;
    if (_hour[1] > 9){_hour[0] = 0;}
    if (_hour[1] > 4 && _hour[0] == 2){_hour[1]=0;}
    lcd.print(_hour[1]);
   }
  };
  if (button2.clickType() == 2)
  {

    cursor++;
    lcd.setCursor(cursor, 0);
    lcd.blink();
  };
/*   if (button2.clickType() == 2)
   {
    lcd.noBlink();
    cursor++;
    Serial.println(cursor);
    lcd.setCursor(cursor, 0);
    lcd.blink();
    Serial.println(cursor);
   }; */
 };
 lcd.noBlink();
 lcd.noCursor();
 setTimeFlag = 0;
}

void timeInit()
{
 hour[0] = RTC.getHour(h12Flag, pmFlag) / 10;
hour[1] = RTC.getHour(h12Flag, pmFlag) % 10;
min[0] = RTC.getMinute() / 10;
min[1] = RTC.getMinute() % 10;
sec[0] = RTC.getSecond() / 10;
sec[1] = RTC.getSecond() % 10;
}