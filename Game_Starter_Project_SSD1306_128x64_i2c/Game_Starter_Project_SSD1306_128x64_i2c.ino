/*
   Game Starter Project 15.02.2017
   Board: Arduino nano
   OLED: SSD1306 i2c
   Author: Aleksey

*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SSD1306_LCDHEIGHT 64
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define UP      8
#define DOWN    10
#define LEFT    9
#define RIGHT   5
#define A       A0
#define B       A1
#define SPEAKER A2
#define LED     2

int playerX = 63;
int playerY = 31;

int targetX = 0;
int targetY = 0;

// Images
static const unsigned char PROGMEM player[] = {
  B11111111, 
  B11111111,
  B11011011, 
  B11111111,
  B11111111, 
  B11000011, 
  B11100111, 
  B11111111, 
};

static const unsigned char PROGMEM target[] = {
  B11111111, 
  B10000001,
  B10100101, 
  B10000001,
  B10000001, 
  B10111101, 
  B10000001, 
  B11111111,
};

void setup() {
  pinMode (UP, INPUT_PULLUP);
  pinMode (DOWN, INPUT_PULLUP);
  pinMode (LEFT, INPUT_PULLUP);
  pinMode (RIGHT, INPUT_PULLUP);
  pinMode (A, INPUT_PULLUP);
  pinMode (SPEAKER, OUTPUT);
  pinMode (LED, OUTPUT);

  digitalWrite(SPEAKER, LOW);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  // initialize with the I2C addr 0x3D (for the 128x64)

  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(1000);

  // Clear the buffer.
  display.clearDisplay();

  // draw a single pixel
  display.invertDisplay(false);
  //display.drawPixel(63, 31, WHITE);
  // Show the display buffer on the hardware.
  // NOTE: You _must_ call display after making any drawing commands
  // to make them visible on the display hardware!
  display.display();
  delay(2000);
  display.clearDisplay();

}

void loop() {
  //testButton();
  display.clearDisplay();

  if (readButton(UP)) {
    playerY--;
  }
  if (readButton(DOWN)) {
    playerY++;
  }
  if (readButton(RIGHT)) {
    playerX++;
  }
  if (readButton(LEFT)) {
    playerX--;
  }

  if (readButton(A)) {
    display.drawBitmap (targetX, targetY, target, 8, 8, WHITE);
  }

  display.drawBitmap (playerX, playerY, player, 8, 8, WHITE);
  //display.drawPixel(playerX, playerY, WHITE);
  display.display();
}

void testButton() {
  if (digitalRead(DOWN) == 0) {
    digitalWrite(LED, HIGH);
  }
  else {
    digitalWrite(LED, LOW);
  }
}

bool readButton(int button) {
  if (digitalRead(button) == 0) {
    // debounce
    delay(20);
    if (digitalRead(button) == 0) {
      return true;
    }
  } else {
    return false;
  }
}


