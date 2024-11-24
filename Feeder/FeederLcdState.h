#pragma once
#include "Arduino.h"
#include "FeederLcdState.h"
#include "GButton.h"
#include "Wire.h"
#include "LiquidCrystal_I2C.h"
#include "DS3231.h"

class FeederLcdState : public GButton, public LiquidCrystal_I2C, public DS3231
{
public:
FeederLcdState(uint8_t Button);

////////////////////////////////// Методы состояний

void lcdIdle(); ////////////////СОСТОЯНИЕ 0// Вывод на экран времени, даты и температуры
void setRealTime();/////////////Установка реального времени
void setRealDate();/////////////Установка реальной даты
void showFeedTimers();////////////СОСТОЯНИЕ 3// Вывод на экран двух таймеров времени кормёжки
void setFeedTime();/////////////// Установка двух таймеров кормёжки (будильники)


////////////////// Массивы со значениями даты и времени

uint8_t setRtcTime[6]{0,0,0,0,0,0};//////////// Реальное время в формате hh mm ss
uint8_t setFeedTime_1[6]{0,0,0,0,0,0}; ///////// Время первой порции корма в формате hh mm ss
uint8_t setFeedTime_2[6]{0,0,0,0,0,0}; ///////// Время второй порции корма в формате hh mm ss
uint8_t setRtcDate[6]; ////////// Дата в формате dd mm yy

private:

uint8_t _button;///////////Кнопка
uint8_t currentState;/////////////Текущее остояние
uint8_t _time[6]{0,0,0,0,0,0};/////Массив для установки времени

void setDate();/////////////////СОСТОЯНИЕ 2// Установка даты
void setTime();/////////////////СОСТОЯНИЕ 1// Установка времени
void timeInit();///////////////////////////// инициализация времени в формате hh:mm:ss
void dateInit();///////////////////////////// инициализация даты в формате dd/mm/yy
};