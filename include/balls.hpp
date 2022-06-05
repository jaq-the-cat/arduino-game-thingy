#pragma once

#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include "player.hpp"
#include "def.hpp"

#define B_COUNT 6

#define B_SPEED 1

#define B_RADIUS 2

class Ball {
  public:
    int16_t x, y;

    Ball() {
      resetPosition();
    };

    void draw(Adafruit_SSD1306 &display) {
      display.drawCircle(x, y, B_RADIUS, SSD1306_WHITE);
    }

    void tick(Player &p) {
      if (distance(p.x, p.y-P_WIDTH, x, y) <= B_RADIUS+1)
        resetPosition();

      y += B_SPEED;

      if (y > 64+B_RADIUS)
        resetPosition();
    }

  private:
    void resetPosition() {
      x = rand() % (128-B_RADIUS*2) + B_RADIUS;
      y = -(rand() % 100);
    }
};
