#pragma once
#include "GButton.h"
#include "StepperMotor.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DS3231.h>
/////////////////////////////////
#define SHOW_TIMER 3000
#define PIN_BUTTON_1 6//////// Кнопка 1
#define PIN_BUTTON_2 7//////// Кнопка 2 
#define HIGH_PIN_STEPPER 13
/////////////////////////////////
enum  lcdCurrentState
{
  lcdIdle,       //////Покой
  lcdSetTime,    //////Установка времени
  lcdSetDate,    //////Установка даты
  lcdShowTimers,  //////Отображение будильников
  lcdSetFeedTimers /////// Настройка таймеров кормёжки
};
///////////////////
enum getClickType {NOCLICK, ONECLICK, DOUBLECLICK, TRIPLECLICK, HOLD};
/////////////////// Объявление массивов для даты и времени
uint8_t setTimeArray[6]{0,0,0,0,0,0};
uint8_t currentRtcTime[6]{0,0,0,0,0,0};//////////// Реальное время в формате hh mm ss
uint8_t currentFeedTime_1[6]{0,0,0,0,0,0}; ///////// Время первой порции корма в формате hh mm ss
uint8_t currentFeedTime_2[6]{0,0,0,0,0,0}; ///////// Время второй порции корма в формате hh mm ss
uint8_t currentRtcDate[6]; ////////// Дата в формате dd mm yy
uint8_t _button1ClckType, _button2ClickType;/////////// Состояние кнопки SINGLE_CLICK-один клик, DOUBLE_CLICK-двойной клик, TRIPLE_CLICK-тройной клик, HOLD-удержание
uint8_t lcdCurrentState;//////////////////////////// Текщее состояние экрана
unsigned long _initTimer=0;//////////// Таймер
//////////////// Объявление библиотечных функций
GButton button1(PIN_BUTTON_1);
GButton button2(PIN_BUTTON_2);
LiquidCrystal_I2C lcd(0x27,16,2);
DS3231 RTC;
/////////////// Объявление флагов
bool CenturyBit = true;
bool h12Flag;
bool pmFlag;


void setup() 
{
 Wire.begin();
 lcd.init();
 lcd.clear();
 Serial.begin (9600);
 pinMode(PIN_BUTTON_2,INPUT);
 pinMode(PIN_BUTTON_1,INPUT);
 pinMode(HIGH_PIN_STEPPER,OUTPUT);
 lcd.backlight();
 h12Flag = 0;
 RTC.setClockMode(h12Flag);
 lcdCurrentState = lcdIdle;
 digitalWrite(13, HIGH);
 ////////
 pinMode(8,OUTPUT);
 digitalWrite(8, HIGH);
}
/////////////////////////////////////////
void loop() {
 dateInit();
 timeInit();
 _button1ClckType = button1.getClickType();
 _button2ClickType = button2.getClickType();
 unsigned long currentMillis = millis();
 /////////////////////////////////////////// Машина состояний для LCD дисплея кормушки
 switch(lcdCurrentState)
 {
  ///////////////////////////////////// СОСТОЯНИЕ Покой
  case lcdIdle:
   if (_button1ClckType == HOLD) ///////////////////////////////////// Переход в состояние Установить время
   {
    lcdCurrentState = lcdSetTime;
    break;
   }
   if (_button1ClckType == DOUBLECLICK) ///////////////////////////////////// Переход в состояние Установить дату
   {
    lcdCurrentState = lcdSetDate;
    break;
   }
   if (_button1ClckType == ONECLICK) ///////////////////////////////////// Переход в состояние Показать Таймеры
   {
    lcdCurrentState = lcdShowTimers; 
    _initTimer = currentMillis;
    lcd.clear();
    break;
   } 
   Serial.println("current lcd state is IDLE");
   lcdCurrentTimeView();
   lcdCurrentDateView();
   break; 
/////////////////////////////////////   СОСТОЯНИЕ Установка времени
  case lcdSetTime:
  Serial.println("current lcd state is SET TIME");
  setRealTime();
  lcdCurrentState = lcdIdle;
  break;
///////////////////////////////////// СОСТОЯНИЕ Установка даты
  case lcdSetDate:
  Serial.println("current lcd state is SET DATE");
  lcdCurrentState = lcdIdle;
  break;
///////////////////////////////////// СОСТОЯНИЕ Показать таймеры
  case lcdShowTimers:
  Serial.println("current lcd state is SHOW TIMERS");
  feed1_TimeViev();
  feed2_TimeViev();
  if (_button1ClckType == HOLD)
  {
   lcdCurrentState = lcdSetFeedTimers;
   break;
  }
  if (currentMillis - _initTimer >= SHOW_TIMER) 
  {
   lcd.clear();
   _initTimer = currentMillis;
   lcdCurrentState = lcdIdle;
  }
  break;
///////////////////////////////////// СОСТОЯНИЕ Установить таймеры
  case lcdSetFeedTimers:
  Serial.println("current lcd state is SET FEED TIMERS");
  setFeedTimers();
  lcdCurrentState = lcdIdle;
  break;
 }
}

/////////////////////////////////////////
void feed1_TimeViev()
{
  lcd.setCursor(0,0);
  lcd.print(currentFeedTime_1[0], DEC);
  lcd.print(currentFeedTime_1[1], DEC);
	lcd.print(":");
	lcd.print(currentFeedTime_1[2], DEC);
  lcd.print(currentFeedTime_1[3], DEC);
	lcd.print(":");
	lcd.print(currentFeedTime_1[4], DEC);
  lcd.print(currentFeedTime_1[5], DEC);
}
/////////////////////////////////////////
void feed2_TimeViev()
{
  lcd.setCursor(0,1);
  lcd.print(currentFeedTime_2[0], DEC);
  lcd.print(currentFeedTime_2[1], DEC);
	lcd.print(":");
	lcd.print(currentFeedTime_2[2], DEC);
  lcd.print(currentFeedTime_2[3], DEC);
	lcd.print(":");
	lcd.print(currentFeedTime_2[4], DEC);
  lcd.print(currentFeedTime_2[5], DEC);
}
/////////////////////////////////////////
void lcdCurrentTimeView()
{
  lcd.setCursor(0,0);
  lcd.print(currentRtcTime[0], DEC);
  lcd.print(currentRtcTime[1], DEC);
	lcd.print(":");
	lcd.print(currentRtcTime[2], DEC);
  lcd.print(currentRtcTime[3], DEC);
	lcd.print(":");
	lcd.print(currentRtcTime[4], DEC);
  lcd.print(currentRtcTime[5], DEC);
}
//////////////////////////////////
void lcdCurrentDateView()
{
  lcd.setCursor(8,1);
  lcd.print(currentRtcDate[0], DEC);
  lcd.print(currentRtcDate[1], DEC);
	lcd.print("/");
	lcd.print(currentRtcDate[2], DEC);
  lcd.print(currentRtcDate[3], DEC);
	lcd.print("/");
	lcd.print(currentRtcDate[4], DEC);
  lcd.print(currentRtcDate[5], DEC);
}
//////////////////////////////// Инициализация установки времени.
void setTime()
{
 for(uint8_t i = 0; i < 6; i++)
 {
    setTimeArray[i] = 0;
 }
 uint8_t cursor = 0;
 lcd.clear();
 lcd.print("00:00:00");
 lcd.setCursor(cursor, 0);
 lcd.blink();
 while(cursor < 8)
 {
  auto _clickType = button1.getClickType();
  if(_clickType == ONECLICK)
  {
   switch(cursor)
   {
    case 0:

     setTimeArray[0] = (setTimeArray[0] + 1) % 3;
     lcd.print(setTimeArray[0]);
     lcd.setCursor(cursor, 0);
     break;
    case 1:
    
     setTimeArray[1] = (setTimeArray[1] + 1) % (setTimeArray[0] == 2 ? 4 : 10);
     lcd.print(setTimeArray[1]);
     lcd.setCursor(cursor, 0);
     break;
    
    case 3 :
    
     setTimeArray[2] = (setTimeArray[2] + 1) % 6;
     lcd.print(setTimeArray[2]);
     lcd.setCursor(cursor, 0);
     break;
    
    case 4 :
    
      setTimeArray[3] = (setTimeArray[3] + 1) % 10;
      lcd.print(setTimeArray[3]);
      lcd.setCursor(cursor, 0);
      break;
    
    case 6 :
    
      setTimeArray[4] = (setTimeArray[4] + 1) % 6;
      lcd.print(setTimeArray[4]);
      lcd.setCursor(cursor, 0);
      break;
    
    case 7 :
    
      setTimeArray[5] = (setTimeArray[5] + 1) % 10;
      lcd.print(setTimeArray[5]);
      lcd.setCursor(cursor, 0);
      break;
   } 
  } 
  if (_clickType == DOUBLECLICK)
  {
    cursor++;
    if (cursor == 2 ||cursor == 5)
   {
     //lcd.noBlink();
     cursor++;
   }
    lcd.setCursor(cursor, 0);
    lcd.blink();
    continue;
  }
 }
 lcd.noBlink();
 lcd.noCursor();
}
/////////////////////////////////////// Инициализация времени в формате 24h hh:mm:ss
void timeInit()
{
 currentRtcTime[0] = RTC.getHour(h12Flag, pmFlag) / 10;
 currentRtcTime[1] = RTC.getHour(h12Flag, pmFlag) % 10;
 currentRtcTime[2] = RTC.getMinute() / 10;
 currentRtcTime[3] = RTC.getMinute() % 10;
 currentRtcTime[4] = RTC.getSecond() / 10;
 currentRtcTime[5] = RTC.getSecond() % 10;
}
/////////////////////////////////////// инициализация даты в формате dd/mm/yy
void dateInit()
{
 currentRtcDate[0] = RTC.getDate() / 10;
 currentRtcDate[1] = RTC.getDate() % 10;
 currentRtcDate[2] = RTC.getMonth(CenturyBit) / 10;
 currentRtcDate[3] = RTC.getMonth(CenturyBit) % 10;
 currentRtcDate[4] = RTC.getYear() / 10;
 currentRtcDate[5] = RTC.getYear() % 10;
}
///////////////////////////////////// Установка реального времени
void setRealTime()
{
  setTime();
  RTC.setHour(setTimeArray[0]*10+setTimeArray[1]);
  RTC.setMinute(setTimeArray[2]*10+setTimeArray[3]);
  RTC.setSecond(setTimeArray[4]*10+setTimeArray[5]);
}
///////////////////////////////////////
void setFeedTimers()
{
  setTime();
  for(uint8_t i = 0; i < 6; i++)
  {
    currentFeedTime_1[i]=setTimeArray[i];
  }
  setTime();
  for(uint8_t i = 0; i < 6; i++)
  {
    currentFeedTime_2[i]=setTimeArray[i];
  }
}
//////////////////////////////////////
/////////////////////////////////////// Установка даты в формате yy/mm/dd
void setDate()
{
  // Массив для хранения вводимой даты: [yy1, yy2, mm1, mm2, dd1, dd2]
  uint8_t setDateArray[6] = {0, 0, 0, 0, 0, 0};
  // Массив максимального количества дней в каждом месяце (янв-дек)
  const uint8_t daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  
  uint8_t cursor = 0; // Позиция курсора на экране
  lcd.clear();
  lcd.print("00/00/00"); // Начальный шаблон в формате yy/mm/dd
  lcd.setCursor(cursor, 0);
  lcd.blink();

  while (cursor < 8)
  {
    auto _clickType = button1.getClickType();

    if (_clickType == ONECLICK)
    {
      switch (cursor)
      {
        case 0: // Десятки лет
          setDateArray[0] = (setDateArray[0] + 1) % 10; // 00-99
          lcd.print(setDateArray[0]);
          lcd.setCursor(cursor, 0);
          break;

        case 1: // Единицы лет
          setDateArray[1] = (setDateArray[1] + 1) % 10;
          lcd.print(setDateArray[1]);
          lcd.setCursor(cursor, 0);
          break;

        case 3: // Десятки месяцев
          setDateArray[2] = (setDateArray[2] + 1) % 2; // 01-12
          lcd.print(setDateArray[2]);
          lcd.setCursor(cursor, 0);
          break;

        case 4: // Единицы месяцев
          setDateArray[3] = (setDateArray[3] + 1) % ((setDateArray[2] == 1) ? 3 : 10);
          lcd.print(setDateArray[3]);
          lcd.setCursor(cursor, 0);
          break;

        case 6: // Десятки дней
          uint8_t month = setDateArray[2] * 10 + setDateArray[3];
          uint8_t year = setDateArray[0] * 10 + setDateArray[1];
          uint8_t maxDays = (month == 0) ? 31 : daysInMonth[month - 1];
          if (month == 2 && isLeapYear(year)) maxDays = 29;
          setDateArray[4] = (setDateArray[4] + 1) % ((maxDays < 30) ? 3 : 4);
          lcd.print(setDateArray[4]);
          lcd.setCursor(cursor, 0);
          break;

        case 7: // Единицы дней
          month = setDateArray[2] * 10 + setDateArray[3];
          year = setDateArray[0] * 10 + setDateArray[1];
          maxDays = (month == 0) ? 31 : daysInMonth[month - 1];
          if (month == 2 && isLeapYear(year)) maxDays = 29;
          setDateArray[5] = (setDateArray[5] + 1) % ((setDateArray[4] == maxDays / 10) ? (maxDays % 10 + 1) : 10);
          lcd.print(setDateArray[5]);
          lcd.setCursor(cursor, 0);
          break;
      }
    }

    if (_clickType == DOUBLECLICK)
    {
      cursor++;
      if (cursor == 2 || cursor == 5) cursor++; // Пропускаем слэши
      lcd.setCursor(cursor, 0);
      lcd.blink();
    }
  }

  lcd.noBlink();
  lcd.noCursor();

  // Устанавливаем дату в RTC
  RTC.setYear(setDateArray[0] * 10 + setDateArray[1]);
  RTC.setMonth(setDateArray[2] * 10 + setDateArray[3]);
  RTC.setDate(setDateArray[4] * 10 + setDateArray[5]);
}

// Проверка високосного года
bool isLeapYear(uint8_t year)
{
  year += 2000; // Предполагаем, что год в формате 00-99 относится к 2000-м
  return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
