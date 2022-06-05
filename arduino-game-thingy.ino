#include "Wire.h"
#include "Adafruit_SSD1306.h"
#include "SPI.h"

#define CS 13
#define DC 12
#define RES 11
#define D1 10
#define D0 9

#define V_LOW 0
#define V_HIGH 1022

#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

#define P_SPEED 2
#define P_WIDTH 6

class Player {
  public:
    int x, y;
    
    Player(byte x, byte y) {
      this->x = x;
      this->y = y;
    }

    void enforceBorderPolicy() {
      if (this->x < 0) this->x = 0;
      else if (this->x > (127-P_WIDTH)) this->x = 127-P_WIDTH;

      if (this->y < 0) this->y = 0;
      else if (this->y > (63-P_WIDTH)) this->y = 63-P_WIDTH;
    }

    void moveDirection(byte d) {
      switch (d) {
        case LEFT:
          this->x -= P_SPEED;
          break;
        case RIGHT:
          this->x += P_SPEED;
          break;
        case UP:
          this->y -= P_SPEED;
          break;
        case DOWN:
          this->y += P_SPEED;
          break;
        default:
          break;
      }
      enforceBorderPolicy();
    }
};

#define PRINT(x, y, s)\
  display.setCursor(x, y);\
  display.print(F(s))

Player p((128/2)-(P_WIDTH/2), (64/2)-(P_WIDTH/2));
Adafruit_SSD1306 display(128, 64, D1, D0, DC, RES, CS);

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
  if (vx <= V_LOW) {
    p.moveDirection(LEFT);
  } else if (vx >= V_HIGH) {
    p.moveDirection(RIGHT);
  }

  if (vy <= V_LOW) {
    p.moveDirection(UP);
  } else if (vy >= V_HIGH) {
    p.moveDirection(DOWN);
  }
  for (int i=0; i<P_WIDTH; i++)
    for (int k=0; k<P_WIDTH; k++)
      display.drawPixel(p.x+i, p.y+k, SSD1306_WHITE);
  display.display();
  delay(20);
}
