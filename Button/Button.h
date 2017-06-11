#ifndef Button_h
#define Button_h

#include "Arduino.h"

//since we have three buttons, I don't want to type the exact same code 3 times. So I use this.
//Here, each button has all its own values, all for itself, and I only have to type the code once
class Button {
	private:
	    //a variable to store the value of the pin, so the computer knows which one to check
		int _pin;

		//some special values for checking if the button is pressed, called debouncing
        //simply checking if a button has been pressed isn't always so easy, so we do this. 
        unsigned long lastDebounceTime;   //keep track of when the button was pressed
        unsigned long debounceDelay;  //create a delay between when to check. Here, its 50 milliseconds. 

        int btnState;   //keep track of the state of the button: pressed(HIGH), or not pressed(LOW)
        int lastBtnState;   //and the last state of the button


	public:
        bool isPressed;   //so we can check the state of the button in other places

        unsigned long numTimesPressed;    //keep track of how many times the button is pressed


       	//initialze some stuff for the button when its created
        Button(int pin);

        bool isButtonPressed (bool isCheckHighVal);

};

#endif