#include "Arduino.h"
#include "SmartBlaster.h"

using namespace SmartBlaster;

SmartBlaster (bool[] modes, byte[] IOPins, byte[] buttons, init[] magSizes) {
	lastVoltageCheckTime = 0;
	delayTime = 500;

	initModes().initIOPins();
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
	}

	_I2C-SDA-Pin = 4;
    _I2C-SCL-Pin = 5;

    return *this;	
}

