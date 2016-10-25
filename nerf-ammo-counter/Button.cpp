//for Button class

#include <iostream>
using namespace std;



class Button {
    public:
        Button (int);
    
    public:
        unsigned long lastDebounceTime;
        unsigned long debounceDelay = 50;
        
        int btnState;
        int lastBtnState = 0;
    
    public:
        void initPin (int pin) {
            const int PIN = pin;
        }

};

Button::Button (int pin) { 
    cout << "instantiated" << endl;
}




int main () {
    Button(2);
    
}

