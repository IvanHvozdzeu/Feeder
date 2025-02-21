#ifndef GBUTTON_H
#define GBUTTON_H

#include "Arduino.h"

// Константы для таймингов (в миллисекундах)
#define DEBOUNCE_DELAY 50    // Задержка для подавления дребезга
#define CLICK_TIMEOUT 200    // Максимальный интервал между кликами для их подсчёта
#define HOLD_TIMEOUT 1000    // Время, после которого считается удержание

enum getClickType {NOCLICK, ONECLICK, DOUBLECLICK, TRIPLECLICK, HOLD};

class GButton {
private:
  uint8_t _pin;
  unsigned long _btnTimer;
  unsigned long _holdTimer;
  bool _pressFlag;
  bool _holdFlag;
  bool _timerFlag;
  uint8_t _clickCount;

public:
  GButton(uint8_t pin);
  uint8_t getClickType();
};

#endif
