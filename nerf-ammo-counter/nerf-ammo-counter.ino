//libraries, so the display can work
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//initialize stuff for display
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

//include a seperate file for the other code
#include "helper.h"

//this code will run when the Arduino turns on
void setup() {
  // put your setup code here, to run once:
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  //set up buttons
  initButtons(3);
  //show the ammo
  displayAmmo();

  //turn on an LED on the board
  digitalWrite(13, HIGH);

}

//this code loops many times a second
void loop() {
  //count ammo, constantly check for the trigger switch to be pressed to count
  countAmmo();
  //toggle between magazine sizes, constanly check for the magazine toggle switch to be pressed
  toggleMags();
  //change magazine, constantly check for the magazine switch to be pressed/not pressed
  changeMag();
  
}
