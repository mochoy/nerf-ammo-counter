//By Monty C

/*Here's how it will work:
 * It's simple. When the trigger is pulled, count down 1 from the ammo. When a magazine is inserted, refill the ammo. A button can be 
 * used to toggle through the different magazine sizes: 5, 6, 10, 12, 15, 18, 22, 25, and 36. The last mode is counts up, starting from 0, 
 * which can be accessed from the toggling the magazine sizes. The magazine sizes will increment, with the press of the button, from 0, 
 * 5, 6, 12 … 36 and will not decrement, for the sake of simplicity.  
 * 
 * 
 * I am aware that the code isn't that good. It's not my best, not my neatest, and it's not too efficient for working with micro controllers, but it should be fine.
 */

//libraries, so the display can work
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//initialize stuff for display
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

//set the height and width of the screen
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

//include a seperate file for the other code
#include "helper.h"

//this code will run when the Arduino turns on
void setup() {
  //begin stuff for the display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  //set up buttons
  initButtons(3);
  //show the ammo
  displayAmmo();

  //turn on an LED on the board. This will make the red LED an indicator that the board is powered up and all. 
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
