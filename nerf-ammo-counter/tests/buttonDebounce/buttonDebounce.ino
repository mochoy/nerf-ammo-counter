//libraries
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//init stuff for display
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

const byte BTN_PIN = 2;
int btnState, lastBtnState = LOW; 

unsigned long lastDebounceTime = 0, debounceDelay = 50;

void setup() {
  // put your setup code here, to run once:
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  pinMode(BTN_PIN, INPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  display.clearDisplay();

  btnState = digitalRead(BTN_PIN);
  if (btnState != lastBtnState) {
      lastDebounceTime = millis();
  }

  if ((millis()-lastDebounceTime) > debounceDelay) {
    if (btnState == HIGH) {
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0, 0);
      display.print("Button Pressed!");
      display.display();
    } else if (btnState == LOW) {
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0, 0);
      display.print("Button Not Pressed!");
      display.display();
    }
  } 

  lastBtnState = btnState;
}
