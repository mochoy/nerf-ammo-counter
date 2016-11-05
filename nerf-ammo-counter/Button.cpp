class Button {
    public:
        int PIN;
        int lastBtnState;
    
    //constructors
    public:
        Button();
        Button(int, int);
    
    public:
        unsigned long lastDebounceTime;
        unsigned long debounceDelay = 50;
        
        int btnState;
        int LOW = lastBtnState;
    
    public:
        bool isBtnPressed(int reading, long micros, unsigned int HIGH) {
            bool returnVal = false;     //flag so can return at end of method
            
            this -> btnState = reading;
            
            //delay
            if (micros >= (this -> lastDebounceTime) + (this -> debounceDelay)) {
                //check if button changes state
                if (this -> btnState != this -> lastBtnState) {
                    //check if btn acutally pressed
                    if (this -> btnState == HIGH) {
                        returnVal = true;
                    }
                }   
                
            }
            
            this -> lastDebounceTime = micros;
            this -> lastBtnState = this -> btnState;
            
            return returnVal;
        }   //method

};

//constructors
Button::Button () {
    PIN = -1;
}

Button::Button (int pin, int low) { 
    PIN = pin;
    lastBtnState = low;
//    HIGH = high;  //for some reason, this doesnt work. Life would be so much easier if it did

}

int main () {
  return 0;
}

