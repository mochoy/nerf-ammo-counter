//for Button class

#include <iostream>
using namespace std;



class Button {
    public:
        Button () {
            cout << "instantiated" << endl;
        }
    
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


int main () {
    Button btnArr[5];
    
}

