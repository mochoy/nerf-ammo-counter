//libraries, so the display can work
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//initialize stuff for display
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

//set the height and width of the screen
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

//keep track of button information
const byte BTN_PIN = 2;   //which pin the button is connected to
int btnState, lastBtnState = LOW, cntr = 0;   //button states

//delay and timing of the button presses
unsigned long lastDebounceTime = 0, debounceDelay = 50;

//this code will run when the Arduino turns on
void setup() {
    //begin stuff for the display
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();   //clear the display

    pinMode(BTN_PIN, INPUT);    //initialize the pin the button is connected to as an input pin

}

//this code loops many times a second
void loop() {
    btnState = digitalRead(BTN_PIN);    //read the value of the button

    //make sure button state changed
    if (btnState != lastBtnState) {
        //make sure button is pressed
        if (btnState == HIGH) {
            cntr++;     //add one to the value of how many times the button is pressed
            printToScreen(0, 10, "Pressed!");   //the button is pressed, so print "Pressed!" to the display
        } else {
            printToScreen(0, 10, "Not Pressed!");       //the button is not pressed, so print "Not Pressed!" to the display 
        }
      
    }
    
    printToScreen(0, 0, String(cntr));  //print how many times the button was pressed to the display
    
    lastBtnState = btnState;        //reset the previous state of the button
}

//pring stuff to the screen
void printToScreen (int x, int y, String text, bool toClearScreen) {
    display.clearDisplay();     //clear the display
    display.setTextSize(1);     //set the size of text to 1
    display.setTextColor(WHITE);    //set the color to white
    display.setCursor(x, y);        //tell the display where to draw
    display.print(text);    //print the text
    display.display();  //display the text
  }

