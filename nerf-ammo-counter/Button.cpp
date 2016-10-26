//for Button class

#include <iostream>
using namespace std;

#define ARRAY_SIZE(array) (sizeof((array))/sizeof((array[0])))

class Button {
    public:
        int PIN;
    
    //constructors
    public:
        Button();
        Button(int);
    
    public:
        unsigned long lastDebounceTime;
        unsigned long debounceDelay = 50;
        
        int btnState;
        int lastBtnState = LOW;
    
    public:
        bool isBtnPressed() {
            this -> btnState = digitalRead(this -> PIN);
            
            //delay
            if (micros() >= (this -> lastDebounceTime) + (this -> debounceDelay)) {
                //check if btn acutally pressed
                if (this -> btnState != this -> lastBtnState) {
                    if (this -> btnState == HIGH) {
                    
                    }
                }   
            }
            
            this -> lastBtnState = this -> btnState;
        }   //method

};

Button::Button () {
    PIN = 0;
}

Button::Button (int pin) { 
    PIN = pin;
}


int main () {
    //create and fill arr
    Button btnArr[5];
    
    for (int i = 0; i <  ARRAY_SIZE(btnArr); i ++) {
        btnArr[i] = Button(i);
    }

}

