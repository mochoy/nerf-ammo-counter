#include "Arduino.h"
#include "SmartBlaster.h"

using namespace SmartBlaster;

SmartBlaster (bool[] modes, byte[] IOPins, byte[] buttons, init[] magSizes) {
	lastVoltageCheckTime = 0;
	delayTime = 500;

	initModes();
}

SmartBlaster& initModes (bool[] modes) {
	_isIRGate = modes[0];
	_isChrono = modes[1];
	_isVoltmeter = modes[2];
	_isSelectFire = modes[3];

	return *this;
}

SmartBlaster& initIOPins (byte ammoCountingInputPin, byte magInsertionDetectionInputPin, byte magSizeToggleInputPin, byte voltMeterInputPin, byte toggleSelectFireInputPin, byte selectFireOutputPin) {

	_ammoCountingInputPin = ammoCountingInputPin;
	_magInsertionDetectionInputPin = magInsertionDetectionInputPin;
	_magSizeToggleInputPin = magSizeToggleInputPin;

	if (_isVoltmeter) {
		_voltMeterInputPin = voltMeterInputPin;
	}

	if (_isSelectFire) {
		_toggleSelectFireInputPin = toggleSelectFireInputPin;
		_selectFireOutputPin = selectFireOutputPin;
	}

	_I2C-SDA-Pin = 4;
    _I2C-SCL-Pin = 5;	
}

