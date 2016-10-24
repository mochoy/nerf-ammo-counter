//for Button class

#include <iostream>
using namespace std;



class Button {
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
    
    cout << "hello" << endl;
    Button btn1;
}

