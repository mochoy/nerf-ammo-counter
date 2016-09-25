//libraries
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//init stuff for display
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

const byte DISPLAY_SDA_PIN = 4, DISPLAY_SCK_PIN = 5;

void setup() {
  // put your setup code here, to run once:
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("Hello, world!");
  display.display();
}

void loop() {
  // put your main code here, to run repeatedly:

}
