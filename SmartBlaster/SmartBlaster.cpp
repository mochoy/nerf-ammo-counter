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

