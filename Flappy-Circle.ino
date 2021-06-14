#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 128

#define SQUARE_W 20
#define RADIUS 3
#define GRAVITY 1

#define SCLK_PIN 13
#define MOSI_PIN 11
#define DC_PIN   8
#define CS_PIN   10
#define RST_PIN  9
#define BUTTON   2

// Color definitions
#define BLACK          0x0000
#define BLUE            0x001F
#define RED             0xF800
#define GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0  
#define WHITE           0xFFFF


#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>
#include <SPI.h>

#include "bird.h"
#include "pipe.h"


int x = SCREEN_WIDTH/2-50;
int y = SCREEN_HEIGHT/2;

int pipe_down_x = SCREEN_WIDTH;
int pipe_down_y = SCREEN_HEIGHT;

int old_x = x;
int old_y = y;

int pipe_down_old_x = pipe_down_x;
int pipe_down_old_y = pipe_down_y;

int vx = 2;
int vy = 2;

int button_pressed = 0;

unsigned long lastFrame = millis();

Adafruit_SSD1351 tft = Adafruit_SSD1351(SCREEN_WIDTH, SCREEN_HEIGHT, CS_PIN, DC_PIN, MOSI_PIN, SCLK_PIN, RST_PIN);  
Bird bird = Bird(x,y, RADIUS);
Pipe pipeDown = Pipe(pipe_down_x, pipe_down_y, 20);

void setup() {
  // put your setup code here, to run once:
  tft.begin();
  tft.fillScreen(BLACK);

  pinMode(BUTTON, INPUT);
}

void updateBird() {
  old_x = bird.getX();
  old_y = bird.getY();

  bird.update(GRAVITY);

  x = bird.getX();
  y = bird.getY();
  tft.fillCircle(old_x,old_y, bird.getR(),BLACK);
  tft.fillCircle(x,y,bird.getR(),RED);
}

void liftBirdUp() {
  old_x = bird.getX();
  old_y = bird.getY();

  bird.update(-10);

  x = bird.getX();
  y = bird.getY();
  tft.fillCircle(old_x,old_y, bird.getR(),BLACK);
  tft.fillCircle(x,y,bird.getR(),RED);
}

void updatePipeDown() {
  if (pipeDown.getX() == SCREEN_WIDTH) {
    // If just moving in screen draw a rect
    tft.fillRect(pipeDown.getX(), pipeDown.getY(), pipeDown.getW(), pipeDown.getH(), BLUE);
    pipeDown.update();
  } else {
    if (pipeDown.getX() < -pipeDown.getW()) {
      pipeDown.reset();
    } else {
      
      // Only draw and erase 1 line at a time
      pipe_down_old_x = pipeDown.getX();
  
      pipeDown.update();
      pipe_down_x = pipeDown.getX();
  
      tft.drawFastVLine(pipe_down_old_x + pipeDown.getW(), pipeDown.getY(), SCREEN_HEIGHT, BLACK);
      tft.drawFastVLine(pipe_down_old_x, pipeDown.getY(), SCREEN_HEIGHT, BLUE);
    }

  }
}

void loop() {

  while ((millis()-lastFrame) < 50);
  lastFrame = millis();

  int buttonState = digitalRead(BUTTON);

  // If bird is still going up
  if (bird.getV() < 0) {
    button_pressed = 1;
  } else {
    button_pressed = 0;
  }
  
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH && button_pressed == 0) {
    liftBirdUp();
  }
  
  updateBird();
  updatePipeDown();
}
