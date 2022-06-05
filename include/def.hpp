#pragma once

#include <Arduino.h>

#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

#define SQUARE(x) ((x)*(x))

float distance(int16_t x0, int16_t y0, int16_t x1, int16_t y1) {
  return sqrt(SQUARE(x0-x1) + SQUARE(y0-y1));
}
