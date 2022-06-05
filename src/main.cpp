#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_SSD1306.h>

#include "player.hpp"
#include "balls.hpp"

#define CS 13
#define DC 12
#define RES 11
#define D1 10
#define D0 9

#define V_LOW 0
#define V_HIGH 1022

#define PRINT(x, y, s)\
  display.setCursor(x, y);\
  display.print(F(s))

Adafruit_SSD1306 display(128, 64, D1, D0, DC, RES, CS);

// create player in the middle of the screen
Player player((128/2), (64/2));
Ball balls[B_COUNT];

void setup() {
  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println("SSD1306 Allocation Failed");
    while(1);
  }

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.cp437(true);
}

int vx, vy;
void loop() {
  display.clearDisplay();
  vx = analogRead(A0);
  vy = analogRead(A1);

  if (vx <= V_LOW)
    player.moveDirection(LEFT);
  else if (vx >= V_HIGH)
    player.moveDirection(RIGHT);

  if (vy <= V_LOW)
    player.moveDirection(UP);
  else if (vy >= V_HIGH)
    player.moveDirection(DOWN);

  // tick balls
  for (byte b=0; b<B_COUNT; b++) {
    balls[b].tick(player);
    balls[b].draw(display);
  }
  player.draw(display);

  display.display();
  delay(20);
}
