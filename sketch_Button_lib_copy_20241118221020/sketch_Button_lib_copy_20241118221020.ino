#include "GButton.h"
#include "StepperMotor.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DS3231.h>
#include <DHT11.h>

////////////////// Обозначение
uint8_t buttonPin1 = 6;
uint8_t buttonPin2 = 7;

uint8_t hour[2];
uint8_t min[2];
uint8_t sec[2];
bool CenturyBit = true;
uint8_t day[2];
uint8_t mon[2];
uint8_t year[2];

GButton button1(buttonPin1);
GButton button2(buttonPin2);
LiquidCrystal_I2C lcd(0x27,16,2);
DS3231 RTC;
DHT11 dht11(4);

bool h12Flag;
bool pmFlag;
bool setTimeFlag;


void setup() 
{
 Wire.begin();
 lcd.init();
 lcd.clear();
 Serial.begin (9600);
 pinMode(3,HIGH);
 pinMode(4,INPUT);
 pinMode(5,LOW);
 pinMode(6,INPUT);
 pinMode(7,INPUT);
 lcd.backlight();
 setTimeFlag = 0;
 h12Flag = 0;
 RTC.setClockMode(h12Flag);
}
void loop() {
//////////////////////////////////////////////DHT11 TEST	
/* int temperature = 0;
int humidity = 0;
int result = dht11.readTemperatureHumidity(temperature, humidity);
if (result == 0) 
 {
        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.print(" °C\tHumidity: ");
        Serial.print(humidity);
        Serial.println(" %");
 } 
 else 
 {
        // Print error message based on the error code.
        Serial.println(DHT11::getErrorString(result));
 } */
/////////////////////////////////////////////	
dateInit();
timeInit();
if(setTimeFlag == 0)
{
  timeViev();
  dateViev();
}
if(button2.clickType() == 4 && button1.clickType() == 4)
{
 setTime();
}
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
//////////////////////////////////
void dateViev()
{
  lcd.setCursor(8,1);
  lcd.print(day[0], DEC);
  lcd.print(day[1], DEC);
	lcd.print("/");
	lcd.print(mon[0], DEC);
  lcd.print(mon[1], DEC);
	lcd.print("/");
	lcd.print(year[0], DEC);
  lcd.print(year[1], DEC);
}
//////////////////////////////////
void resetTime()
{
  bool timeStop = 1;
  for(int i=0; i<1;i++)
  {
  RTC.setHour(0);
  RTC.setMinute(0);
  RTC.setSecond(1);
  }
}
//////////////////////////////// Инициализация установки времени.
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
 while(cursor < 8)
 {
  auto _clickType = button2.clickType();
  if(_clickType == 1)
  {
   switch(cursor)
   {
    case 0:

     _hour[0] = (_hour[0] + 1) % 3;
     lcd.print(_hour[0]);
     lcd.setCursor(cursor, 0);
     break;
    case 1:
    
     _hour[1] = (_hour[1] + 1) % (_hour[0] == 2 ? 4 : 10);
     lcd.print(_hour[1]);
     lcd.setCursor(cursor, 0);
     break;
    
    case 3 :
    
     _min[0] = (_min[0] + 1) % 6;
     lcd.print(_min[0]);
     lcd.setCursor(cursor, 0);
     break;
    
    case 4 :
    
      _min[1] = (_min[1] + 1) % 10;
      lcd.print(_min[1]);
      lcd.setCursor(cursor, 0);
      break;
    
    case 6 :
    
      _sec[0] = (_sec[0] + 1) % 6;
      lcd.print(_sec[0]);
      lcd.setCursor(cursor, 0);
      break;
    
    case 7 :
    
      _sec[1] = (_sec[1] + 1) % 10;
      lcd.print(_sec[1]);
      lcd.setCursor(cursor, 0);
      break;
   } 
  } 
  if (_clickType == 2)
  {
    cursor++;
    if (cursor == 2 ||cursor == 5)
   {
     lcd.noBlink();
     cursor++;
   }
    lcd.setCursor(cursor, 0);
    lcd.blink();
    Serial.print("отработал иф");
  }
 }
 lcd.noBlink();
 lcd.noCursor();
 RTC.setHour(_hour[0]*10+_hour[1]);
 RTC.setMinute(_min[0]*10+_min[1]);
 RTC.setSecond(_sec[0]*10+_sec[1]);
 setTimeFlag = 0;
}
/////////////////////////////////////// Инициализация времени в формате 24h hh:mm:ss
void timeInit()
{
 hour[0] = RTC.getHour(h12Flag, pmFlag) / 10;
 hour[1] = RTC.getHour(h12Flag, pmFlag) % 10;
 min[0] = RTC.getMinute() / 10;
 min[1] = RTC.getMinute() % 10;
 sec[0] = RTC.getSecond() / 10;
 sec[1] = RTC.getSecond() % 10;
}
/////////////////////////////////////// инициализация даты в формате dd/mm/yy
void dateInit()
{
 day[0] = RTC.getDate() / 10;
 day[1] = RTC.getDate() % 10;
 mon[0] = RTC.getMonth(CenturyBit) / 10;
 mon[1] = RTC.getMonth(CenturyBit) % 10;
 year[0] = RTC.getYear() / 10;
 year[1] = RTC.getYear() % 10;
}
