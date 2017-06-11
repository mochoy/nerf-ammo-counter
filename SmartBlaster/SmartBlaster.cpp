#include "Arduino.h"
#include "SmartBlaster.h"

using namespace SmartBlaster;

SmartBlaster () {
	lastVoltageCheckTime = 0;
	delayTime = 500;
}

initModes (bool isIRGate, bool isChrono, bool isVoltmeter, bool isSelectFire) {
	_isIRGate = isIRGate;
	_isChrono = isChrono;
	_isVoltmeter = isVoltmeter;
	_isSelectFire = isSelectFire;

	return 
}

