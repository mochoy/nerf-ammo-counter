#include "Arduino.h"
#include "SmartBlaster.h"

using namespace SmartBlaster;

SmartBlaster (bool[] modes, byte[] IOPins, byte[] buttons, init[] magSizes) {
	lastVoltageCheckTime = 0;
	delayTime = 500;

	chronoToPrint = "";
    ammoToPrint = "";
    voltageToPrint = "";
    firingModeToPrint = "";

    fireMode = 0;

    IR_MAP_TRIP_VAL = 95;
    DART_LEGNTH_FEET = 0.2362208333;

    R1 = 100000.0 
    R2 = 10000.0

	initModes().initIOPins().initButtons();
}

SmartBlaster& initModes (bool[] modes) {
	_isIRGate = modes[0];
	_isChrono = modes[1];
	_isVoltmeter = modes[2];
	_isSelectFire = modes[3];

	return *this;
}

SmartBlaster& initIOPins (byte[] pins) {
	_ammoCountingInputPin = pins[0];
	_magInsertionDetectionInputPin = pins[1];
	_magSizeToggleInputPin = pins[2];

	if (_isVoltmeter) {
		_voltMeterInputPin = pins[3];
	}

	if (_isSelectFire) {
		_toggleSelectFireInputPin = pins[4];
		_selectFireOutputPin = pins[5];
		pinMode(_selectFireOutputPin, OUTPUT);
	}

	_I2C-SDA-Pin = 4;
    _I2C-SCL-Pin = 5;

    return *this;	
}

SmartBlaster& initButtons () {
	if (!_isIRGate) {
		buttonArr[0] = Button(_ammoCountingInputPin);
	} else {
		buttonArr[0] = Button(-1);
	}

	buttonArr[1] = Button(_magInsertionDetectionInputPin);
	buttonArr[2] = Button(_magSizeToggleInputPin);

	if (_isSelectFire) {
		buttonArr[3] = Button(_toggleSelectFireInputPin);
	} else {
		buttonArr[3] = Button(-1);
	}


	return *this;
}

SmartBlaster& initMagSizes(int[] magSizes) {
	for (int i = 0; i < ((sizeof(magSizes)/sizeof(magSizes[0])) - 1), i++) {
		magSizeArr[i] = magSizes[i];
	}
    currentMagSize = 0;
    maxAmmo = magSizeArr[currentMagSize];
    curretAmmo = maxAmmo;

	return *this;
}

SmartBlaster& initDisplay(Adafruit_SSD1306 displayArg) {
	display = displayArg;

	return *this;
}

void displayValues () {
	//display ammo
	display.clearDisplay(); //clear the display, so the stuff that was here before is no longer here
	display.setTextSize(6);  //set the size of the text
	display.setTextColor(WHITE);    //set the color of text text
	//tell the display where to draw the text
	display.setCursor( (SCREEN_WIDTH/2) - ((ammoToPrint.length()*2) * 9) , (SCREEN_HEIGHT/2) - 30 );  //center text
	display.print(ammoToPrint);    //print the text

	display.setTextSize(1);

	//display chrono values
	if (_isChrono) {
		display.setCursor(0, 50);  
		display.print(chronoToPrint);
	}

	//display voltage values
	if (_isVoltmeter) {
		display.setCursor(60, 50);
		display.print(voltageToPrint);
	}

	//display fire mode
	if (_isSelectFire) {
		display.setCursor(80, 50);  
		display.print(firingModeToPrint);
	}	
  
	display.display(); //display the text
}

void initDisplayVoltage (Double voltage) {
	voltageToPrint = (String)voltage + " v";
	displayValues();
}

void initDisplayAmmo () {
	String textToDisplay = "00";    //create something to store what to print. This is empty now
    //if the ammo to print, current ammo, is less that 10, make it like '01' or '04'  
    if (currentAmmo < 10) {
      textToDisplay = "0" + (String)currentAmmo; //fill the thing we used to store what to print
    } else {    //if not, leave it as is
      textToDisplay = (String)currentAmmo;   //fill the thing we used to store what to print
    }

    ammoToPrint = textToDisplay;  //display the text, the ammo

	displayValues();
}

void initDisplayChrono (double fps) {
	if (fps == -1) {
	        chronoToPrint = ("ERR");
	    } else if (fps == -2) {
	        chronoToPrint = ("NO FPS");
	    } else {
	        chronoToPrint = ( (String)(fps)  + " fps" );
	}

	displayValues();	
}

void initDisplayFireMode() {
	//print text based on mode: 0 == S == Safety, 1 == SS == Single Shot, 2 == 3B == 3 Round Burst, 3 == A == Automatic
	if (fireMode == 0) {
	    modeToPrint = "S";
	} else if (fireMode == 1) {
	    modeToPrint = "SS";
	} else if (fireMode == 2) {
	    modeToPrint = "3B";
	} else if (fireMode == 3) {
	    modeToPrint = "A";
	}	

	displayValues();
}

void resetChronoVals() {
	tripTime = -10;
	exitTime = -10;
}

double calculateChronoReadings(double firstTime, double secondTime) {
	if ( (tripTime > -10) && (exitTime > -10) ) {
        resetChronoVals();
        return (DART_LEGNTH_FEET) / ((secondTime-firstTime)/1000000.0);
	}
}

void chrono() {
    //when tripped and expecting first value
    if ((map(analogRead(_ammoCountingInputPin), 0, 1023, 0, 100) > IR_MAP_TRIP_VAL) && (tripTime == -10) ) { 
        tripTime = micros();
    //when tripped and expecting second value
    } else if ( (tripTime != -10) && (exitTime == -10) && (map(analogRead(_ammoCountingInputPin), 0, 1023, 0, 100) < IR_MAP_TRIP_VAL) )  {
        exitTime = micros();
        initDisplayChronoValues(calculateChronoReadings(tripTime, exitTime));

        //count ammo stuff
        //make sure that the ammo is less than 99 so it doesnt overflow the display
        //make sure it's in increment mode
        if ( (magSizeArr[currentMagSize] == 0) && (currentAmmo < 99) ) {
            currentAmmo++;    //increment ammo
        
        //make sure that the ammo is more than 0 so no negative numbers are displayed
        //make sure it's in increment mode
        } else if ( (currentAmmo > 0) && (magSizeArr[currentMagSize] != 0) ){
            currentAmmo--;    //decrement ammo
        }
    
        displayAmmo();    //display the ammo    
        
    //when no second value within 1 second
    } else if ( (tripTime != -10) && (tripTime + 2000000) < micros() ) {
        resetChronoVals();
        initDisplayChronoValues(-1);
    } 
}

void changeMags() {
	//make sure the magazine insertion detection button is pressed from not being pressed
    if (btnArr[1].isBtnPressed(true) ) {   //when the magazine is inserted
        currentAmmo = maxAmmo;  //set current ammo to the max amount of ammo
        displayAmmo();  //display ammo
	}
}

void toggleMags() {
	//check if the magazine toggle button is pressed
  if (btnArr[2].isBtnPressed(false)) {
      //make sure the value doesn't overflow:
      //if the we're trying to access the 10th element of the array, but there are only 9 elements, the program will break
        //must keep the value trying to access is within the amount of values there are. 
        if (currentMagSize < ((sizeof(magSizeArr)/sizeof(magSizeArr[0])) - 1) ) {
            currentMagSize ++;  //change current magazine size
        } else {  
            currentMagSize = 0;
        }

        //there's a new max ammo, because there's a new magazine size
        maxAmmo = magSizeArr[currentMagSize];
        currentAmmo = maxAmmo;

        displayAmmo();    //display the maxAmmo

	} 
}

void voltMeter () {
	//make sure only prints every .5 sec
    if (millis() >= lastVoltageCheckTime + delayTime) {
        //calculate voltage
        float voltageIn = ((analogRead(VOLTMETER_PIN) * 5.0) / 1024.0) / (R2/ (R1 + R2));
    
        //make sure voltage is above 0.03, since it could be an error
        if (voltageIn < 0.5) {
            voltageIn = 0; 
        }

        displayVoltage(voltageIn);

        lastVoltageCheckTime = millis();
	}
}



