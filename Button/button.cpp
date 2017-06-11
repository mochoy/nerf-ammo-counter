#include "Arduino.h"
#include "Button.h"

Button::Button(int pin){
  	pinMode(pin, INPUT);
  	_pin = pin;

    debounceDelay = 50;
    lastBtnState = LOW;
    numTimesPressed = 0;
}

bool Button::isButtonPressed(bool isCheckHighVal){
	//here, we actually check if the button is pressed, "debounce"
    bool returnVal = false;     //flag so can return at end of method

    //read the state of the button
    this -> btnState = digitalRead(this -> PIN);
        

    //check if button changes state
    if (this -> btnState != this -> lastBtnState) {
        //delay
        if (micros() >= (this -> lastDebounceTime) + (this -> debounceDelay)) {
        	//check if btn acutally pressed
        	if (this -> btnState == isCheckHighVal) {
            	returnVal = true;
            	isPressed = true;   //it is pressed, so we have to let outside code know as well
            	numTimesPressed++;  //when the button is pressed, add 1 to the variable storing how many times its pressed
        	} else {
            	isPressed = false;    //it is not pressed, so we have to let outside code know as well
        	}
    	}
    }   
            
    //set some values so we know what to check next time
    this -> lastDebounceTime = micros();
    this -> lastBtnState = this -> btnState;
        
    return returnVal;
}