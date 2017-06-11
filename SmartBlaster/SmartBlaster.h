#ifndef AmmoCounter_h
#define AmmoCounter_h

#include "Arduino.h"

//stuff to help keep track of magazine stuff
//
//
//
//if you want to add/remove magazine sizes, do that here. Remember, they go in order when you toggle between them, from left to right in this.
//
//when you change the value, the "currentMagSize"(several lines below) has to be less than the number of different magazines sizes, 
//the number of different magazine size values in the "magSizeArr" you can change "currentMagSize" to whatever you want. 
//When it program first starts, when the microcontroller turns on, the 5th element of "magSizeArr" is the current magazine size,
//starting from 0. 
//Ex: byte array = {1(0), 2(1), 3(2), 4(3)} - the numbers without parenthesis are the values this array/list 
//stores, and the number between the parenthesis indicates which place they are, their "index", where they are in the list/array. 
//If I want to access the value 1, which is the first value of the array/list, which the computer sees as the 
//"zeroith" value, I would do array[0]. If I want to access the value 3, the third value of the array, I would do array[2]
class SmartBlaster {
	public:
        //stuff to help keep track of magazine stuff
        //
        //
        //
        //if you want to add/remove magazine sizes, do that here. Remember, they go in order when you toggle between them, from left to right in this.
        //
        //when you change the value, the "currentMagSize"(several lines below) has to be less than the number of different magazines sizes, 
        //the number of different magazine size values in the "magSizeArr" you can change "currentMagSize" to whatever you want. 
        //When it program first starts, when the microcontroller turns on, the 5th element of "magSizeArr" is the current magazine size,
        //starting from 0. 
        //Ex: byte array = {1(0), 2(1), 3(2), 4(3)} - the numbers without parenthesis are the values this array/list 
        //stores, and the number between the parenthesis indicates which place they are, their "index", where they are in the list/array. 
        //If I want to access the value 1, which is the first value of the array/list, which the computer sees as the 
        //"zeroith" value, I would do array[0]. If I want to access the value 3, the third value of the array, I would do array[2]
        byte magSizeArr[];
        byte currentMagSize;
        byte maxAmmo;
        byte curretAmmo;

    private: 
        //stuff for dealing with pins
        byte _ammoCountingInputPin;
        byte _magInsertionDetectionInputPin;
        byte _magSizeToggleInputPin; 
        byte _voltMeterInputPin;
        byte _toggleSelectFireInputPin;

        byte _I2C-SPA-Pin;
        byte _I2C-SCK-Pin;   

        byte _selectFireOutputPin; 

        //stuff for dealing with modes: chrono, voltmeter, etc.
        bool _isIRGate;  
        bool _isChrono;
        bool _isVoltmeter;
        bool _isSelectFire;

        //stuff for dealing with chrono calculations
        double tripTime;
        double exitTime;

        //values for dealing with voltmeter stuff
        double lastVoltageCheckTime;
        int delayTime;

    //methods
    public:
        //init stuff
        SmartBlaster initModes();
        SmartBlaster initButtons();

        //display stuff
        void displayValues();
        void displayVoltage();
        void displayAmmo();

        //crhono stuff
        void resetChronoVals();
        double calculateChronoReadings(double firstTime, double secondTime);
        void initDisplayChronoValues(double fps);
        void chrono();

        //mag stuff
        void changeMags();
        void toggleMags();

        void voltmeter();

        void ammoCounter();
};

#endif