//libraries
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//init stuff for display
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

const byte PHOTO_RESISTOR_PIN = 1;

void setup() {
  // put your setup code here, to run once:
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

}

void loop() {
  // put your main code here, to run repeatedly:
  display.clearDisplay();
  
  int photoResistorRead = analogRead(PHOTO_RESISTOR_PIN);

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("val: ");
  display.print(photoResistorRead);
  display.display();
}
