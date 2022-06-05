#pragma once

#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include "def.hpp"

#define P_SPEED 2

#define P_WIDTH 3

const int P_SHAPE[3][2] = {
  {0, -P_WIDTH}, // nose
  {-P_WIDTH, P_WIDTH}, // left wing
  {P_WIDTH, P_WIDTH}}; // right wing

class Player {
  public:
    byte x, y;
    
    Player(byte x, byte y) : x(x), y(y) {};

    void draw(Adafruit_SSD1306 &display) {
      for (byte row=0; row<2; row++)
        display.drawLine(
          /*x0, y0 */ x + P_SHAPE[row][0], y + P_SHAPE[row][1],
          /*x1, y1 */ x + P_SHAPE[row+1][0], y + P_SHAPE[row+1][1],
          SSD1306_WHITE
        );
      display.drawLine(
        /*x0, y0 */ x + P_SHAPE[2][0], y + P_SHAPE[2][1],
        /*x1, y1 */ x + P_SHAPE[0][0], y + P_SHAPE[0][1],
        SSD1306_WHITE
      );
    }

    void enforceBorderPolicy() {
      if (x < P_WIDTH) x = 128-P_WIDTH;
      else if (x > (128-P_WIDTH)) x = P_WIDTH;

      if (y < P_WIDTH) y = 64-P_WIDTH;
      else if (y > (64-P_WIDTH)) y = P_WIDTH;
    }

    void moveDirection(byte d) {
      switch (d) {
        case LEFT:
          x -= P_SPEED;
          break;
        case RIGHT:
          x += P_SPEED;
          break;
        case UP:
          y -= P_SPEED;
          break;
        case DOWN:
          y += P_SPEED;
          break;
        default:
          break;
      }
      enforceBorderPolicy();
    }
};
