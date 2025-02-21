#include "Arduino.h"
#include "GButton.h"

enum getClickType {NOCLICK, ONECLICK, DOUBLECLICK, TRIPLECLICK, HOLD};

GButton::GButton(uint8_t pin) {
  _pin = pin;
}

uint8_t GButton::getClickType() {
  switch (digitalRead(_pin)) {
    case 0: // Кнопка отпущена
      if (!_pressFlag && _holdFlag && millis() - _btnTimer > 50) { // Сброс флагов после отпускания
        _btnTimer = millis();
        if (millis() - _holdTimer > 500) { // Если прошло больше 500 мс после удержания
          _holdTimer = millis() - _holdTimer;
        }
        _holdFlag = false;
        _timerFlag = true;
        return NOCLICK;
      }
      if (_pressFlag && _holdFlag) { // Кнопка отпущена после нажатия
        _btnTimer = millis();
        _pressFlag = false;
        _clickCount++;
      }
      if (millis() - _btnTimer > 200) { // Проверка кликов через 200 мс
        if (_clickCount > 3) { // Ограничение максимального числа кликов
          _clickCount = 3;
        }
        switch (_clickCount) {
          case 0:
            return NOCLICK;
            break;
          case 1:
            Serial.println("Нажатие");
            _clickCount = 0;
            return ONECLICK;
            break;
          case 2:
            Serial.println("Двойное нажатие");
            _clickCount = 0;
            return DOUBLECLICK;
            break;
          case 3:
            Serial.println("Тройное нажатие");
            _clickCount = 0;
            return TRIPLECLICK;
            break;
        }
        _clickCount = 0; // Сброс счётчика после обработки
      }
      else { // Отсутствие действия
        return NOCLICK;
      }
      break;

    case 1: // Кнопка нажата
      if (!_holdFlag && millis() - _btnTimer > 50) { // Регистрация нажатия
        _btnTimer = millis();
        _holdFlag = true;  // Флаг удержания
        _pressFlag = true; // Флаг нажатия
      }
      if (_holdFlag && millis() - _btnTimer > 1000) { // Удержание более 1000 мс
        Serial.println("Удержание");
        if (_timerFlag) { // Сброс таймера после удержания
          _timerFlag = false;
          _holdTimer = millis();
        }
        _btnTimer = millis();
        _pressFlag = false;
        _clickCount = 0;
        return HOLD;
      }
      if (_timerFlag) { // Обновление таймера, если флаг активен
        _timerFlag = false;
        _holdTimer = millis();
      }
      break;
  }
  return NOCLICK; // Добавлен возврат по умолчанию вне switch
}
