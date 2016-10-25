//for Button class

#include <iostream>
using namespace std;

#define ARRAY_SIZE(array) (sizeof((array))/sizeof((array[0])))

class Button {
    //constructors
    public:
        Button();
        Button(int);
    
    public:
        unsigned long lastDebounceTime;
        unsigned long debounceDelay = 50;
        
        int btnState;
        int lastBtnState = 0;
    
    public:
        void printPin() {
            cout << this -> PIN << endl;
        }

};

Button::Button () {
    cout << "instantiated" << endl;
}

Button::Button (int pin) { 
    const int PIN = pin;
}


int main () {
    //create and fill arr
    Button btnArr[5];
    
    for (int i = 0; i <  ARRAY_SIZE(btnArr); i ++) {
        btnArr[i] = Button(i);
    }
    
    for (int i = 0; i <  ARRAY_SIZE(btnArr); i ++) {
        btnArr[i].printPin();
    }    
}

