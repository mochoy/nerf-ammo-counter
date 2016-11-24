//libraries
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//init stuff for display
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#include "helper.h"

void setup() {
  // put your setup code here, to run once:
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  initButtons(3);
  displayAmmo();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  countAmmo();
  toggleMags();
  changeMag();
//  flashEmptyMag();
  
}
