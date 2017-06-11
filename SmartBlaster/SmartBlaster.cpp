#include "Arduino.h"
#include "SmartBlaster.h"

using namespace SmartBlaster;

SmartBlaster (bool[] modes, byte[] IOPins, byte[] buttons, init[] magSizes) {
	lastVoltageCheckTime = 0;
	delayTime = 500;

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

SmartBlaster& initDisplay() {

	return *this;
}
