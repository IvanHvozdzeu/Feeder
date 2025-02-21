#include "Arduino.h"
#include "GButton.h"

GButton::GButton(uint8_t pin) {
  _pin = pin;
  pinMode(_pin, INPUT); // Настраиваем пин как вход
  _btnTimer = 0;
  _holdTimer = 0;
  _pressFlag = false;
  _holdFlag = false;
  _timerFlag = false;
  _clickCount = 0;
}

uint8_t GButton::getClickType() {
  if (millis() - _btnTimer < DEBOUNCE_DELAY) return NOCLICK; // Игнорируем дребезг

  bool state = digitalRead(_pin);
  if (state == HIGH && !_holdFlag) { // Нажатие началось
    _btnTimer = millis();
    _holdFlag = true;
    _pressFlag = true;
  }
  else if (state == LOW && _pressFlag) { // Кнопка отпущена
    _pressFlag = false;
    if (millis() - _btnTimer < CLICK_TIMEOUT) { // Короткое нажатие
      _clickCount++;
      _btnTimer = millis();
    }
  }

  if (_holdFlag && state == HIGH && millis() - _btnTimer > HOLD_TIMEOUT) { // Удержание
    Serial.println("Удержание");
    _holdFlag = false;
    _clickCount = 0;
    _btnTimer = millis();
    return HOLD;
  }

  if (_clickCount > 0 && millis() - _btnTimer > CLICK_TIMEOUT) { // Проверяем клики
    uint8_t result = NOCLICK;
    switch (_clickCount) {
      case 1: Serial.println("Нажатие"); result = ONECLICK; break;
      case 2: Serial.println("Двойное нажатие"); result = DOUBLECLICK; break;
      case 3: Serial.println("Тройное нажатие"); result = TRIPLECLICK; break;
    }
    _clickCount = 0;
    return result;
  }

  return NOCLICK;
}
