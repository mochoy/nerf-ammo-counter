# Smart Blaster

Arduino library to make ammo counters and more for highly modified NERF blasters. 

####Features Included:
1. **Ammo Counting:** Count your ammo. Whenever you fire a dart, it's detected using one of these methods:
	1. **Switch**: Detect shots every time the trigger is pressed. Orient a tactile switch to be pressed when the blaster's trigger is pressed, and wire it up to the microcontroller. May not be ideal for fully-automatic blasters.
	2. **Infrared (IR) Gate**: Using both an IR transmitter and IR receiver to detect dart passage rather than physical trigger pulls. The transmitter and receiver should be positioned so the transmitter shines directly on the receiver along the diameter of the barrel, forming a "gate". When a dart is fired, the gate is broken, which is detected with the microcontroller.
2. **Chronograph**: Using an IR gate, a chronograph can be implemented by recording the time it took for the dart to completely break through the gate, divided by the known length of the dart. Units are in feet per second (fps).
3. **Voltmeter**: Using a voltage divider, the Arduino can read the voltage of the battery used. Ideal for electronic-powered blasters, so you know when to switch out the batteries. Can detect the voltage of the battery powering the blaster, or of the battery powering the microcontroller.
4. **Select-Fire**:  Want to conserve ammo in your fully-automatic blaster? Toggle between safety, single-shot. three-round-burst, or fully-automatic with this feature. Requires a relay or MOSFET to control the pusher motor. IR gate required.
	

___

###Hardware and Parts Needed
All builds require some sort of Arduino-compatible microcontroller. I recommend the [Adafruit Pro Trinket](https://www.adafruit.com/product/2000). Also make sure to have the [Arduino IDE](https://www.arduino.cc/en/Main/Software) installed.




###Installation
`cd ../Arduino/libraries`
`git clone https://github.com/etnom/nerf-ammo-counter`
`git clone https://github.com/adafruit/Adafruit_SSD1306`
`git clone https://github.com/adafruit/Adafruit-GFX-Library.git`
`git clone https://github.com/adafruit/Adafruit_SSD1306`


> Written with [StackEdit](https://stackedit.io/).