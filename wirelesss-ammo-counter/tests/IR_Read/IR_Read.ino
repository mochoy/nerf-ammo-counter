#include <SoftwareSerial.h>

const byte IR_READ_PIN = 0;

void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);

    pinMode(IR_READ_PIN, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
    Serial.println(analogRead(IR_READ_PIN));
}
