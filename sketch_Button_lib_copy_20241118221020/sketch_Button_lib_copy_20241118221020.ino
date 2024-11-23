#include "GButton.h"
#include "StepperMotor.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DS3231.h>
#include <DHT11.h>

#define SHOW_TIMER 3000;
enum clickType {NO_CLICK, ONE_CLICK, DOUBLE_CLICK, TRIPLE_CLICK, HOLD};
////////////////// Объявление переменных для пинов
uint8_t buttonPin_1 = 6; //////// Кнопка 1
uint8_t buttonPin_2 = 7; //////// Кнопка 2
/////////////////// Объявление массивов для даты и времени
uint8_t realTime[6]{0,0,0,0,0,0};//////////// Реальное время в формате hh mm ss
uint8_t feedTime_1[6]{0,0,0,0,0,0}; ///////// Время первой порции корма в формате hh mm ss
uint8_t feedTime_2[6]{0,0,0,0,0,0}; ///////// Время второй порции корма в формате hh mm ss
uint8_t day[2], mon[2], year[2]; ////////// Дата в формате dd mm yy
uint8_t _clickType1, _clickType2;
unsigned long _initTimer=0;
//////////////// Объявление библиотечных функций
GButton button1(buttonPin_1);
GButton button2(buttonPin_2);
LiquidCrystal_I2C lcd(0x27,16,2);
DS3231 RTC;
/////////////// Объявление флагов
bool CenturyBit = true;
bool h12Flag;
bool pmFlag;
bool viewTimeFlag;
bool extraViewTimeFlag;


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
 viewTimeFlag = 1;
 extraViewTimeFlag = 0;
 h12Flag = 0;
 RTC.setClockMode(h12Flag);
}
void loop() {

 dateInit();
 timeInit();
 _clickType1 = button1.getclickType();
 _clickType2 = button2.getclickType();
 if(viewTimeFlag == 1)
 {
  if(extraViewTimeFlag==0){
  timeViev();
  dateViev();
  }
  else{
    if (millis() - _initTimer > 3000){
      extraViewTimeFlag = 0;
      lcd.clear();
    }

  }
 }
 if(_clickType2 == HOLD && _clickType1 == HOLD)
 {
  setTime();
 }
 if(_clickType2 == ONE_CLICK)
 {
 // unsigned long _currenttimer = 0;
  _initTimer = millis();
  lcd.clear();
  //viewTimeFlag = 0;
  // if (millis() - _initTimer < 3000)
  // {
  feed1_TimeViev();
  feed2_TimeViev();
  extraViewTimeFlag=1;
  // _currenttimer = millis();
// }
 }
}
/////////////////////////////////////////
void feed1_TimeViev()
{
  lcd.setCursor(0,0);
  lcd.print(feedTime_1[0], DEC);
  lcd.print(feedTime_1[1], DEC);
	lcd.print(":");
	lcd.print(feedTime_1[2], DEC);
  lcd.print(feedTime_1[3], DEC);
	lcd.print(":");
	lcd.print(feedTime_1[4], DEC);
  lcd.print(feedTime_1[5], DEC);
}
/////////////////////////////////////////
void feed2_TimeViev()
{
  lcd.setCursor(0,1);
  lcd.print(feedTime_2[0], DEC);
  lcd.print(feedTime_2[1], DEC);
	lcd.print(":");
	lcd.print(feedTime_2[2], DEC);
  lcd.print(feedTime_2[3], DEC);
	lcd.print(":");
	lcd.print(feedTime_2[4], DEC);
  lcd.print(feedTime_2[5], DEC);
}
/////////////////////////////////////////
void timeViev()
{
  lcd.setCursor(0,0);
  lcd.print(realTime[0], DEC);
  lcd.print(realTime[1], DEC);
	lcd.print(":");
	lcd.print(realTime[2], DEC);
  lcd.print(realTime[3], DEC);
	lcd.print(":");
	lcd.print(realTime[4], DEC);
  lcd.print(realTime[5], DEC);
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
//////////////////////////////// Инициализация установки времени.
void setTime()
{
 uint8_t cursor = 0;
 uint8_t _time[6]{0,0,0,0,0,0};
 viewTimeFlag = 0;
 lcd.clear();
 lcd.print("00:00:00");
 lcd.setCursor(cursor, 0);
 lcd.blink();
 while(cursor < 8)
 {
  auto _clickType = button2.getclickType();
  if(_clickType == 1)
  {
   switch(cursor)
   {
    case 0:

     _time[0] = (_time[0] + 1) % 3;
     lcd.print(_time[0]);
     lcd.setCursor(cursor, 0);
     break;
    case 1:
    
     _time[1] = (_time[1] + 1) % (_time[0] == 2 ? 4 : 10);
     lcd.print(_time[1]);
     lcd.setCursor(cursor, 0);
     break;
    
    case 3 :
    
     _time[2] = (_time[2] + 1) % 6;
     lcd.print(_time[2]);
     lcd.setCursor(cursor, 0);
     break;
    
    case 4 :
    
      _time[3] = (_time[3] + 1) % 10;
      lcd.print(_time[3]);
      lcd.setCursor(cursor, 0);
      break;
    
    case 6 :
    
      _time[4] = (_time[4] + 1) % 6;
      lcd.print(_time[4]);
      lcd.setCursor(cursor, 0);
      break;
    
    case 7 :
    
      _time[5] = (_time[5] + 1) % 10;
      lcd.print(_time[5]);
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
  }
 }
 lcd.noBlink();
 lcd.noCursor();
 RTC.setHour(_time[0]*10+_time[1]);
 RTC.setMinute(_time[2]*10+_time[3]);
 RTC.setSecond(_time[4]*10+_time[5]);
 viewTimeFlag = 1;
}
/////////////////////////////////////// Инициализация времени в формате 24h hh:mm:ss
void timeInit()
{
 realTime[0] = RTC.getHour(h12Flag, pmFlag) / 10;
 realTime[1] = RTC.getHour(h12Flag, pmFlag) % 10;
 realTime[2] = RTC.getMinute() / 10;
 realTime[3] = RTC.getMinute() % 10;
 realTime[4] = RTC.getSecond() / 10;
 realTime[5] = RTC.getSecond() % 10;
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
