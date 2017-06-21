# Smart Blaster

Arduino library to make ammo counters and more for highly modified NERF blasters. 

___

## Contents:
- [Features Included](#features-included)
- [Parts and Tools Needed](#parts-and-tools-needed)
- [Installation](#installation)


## Features Included:
1. **Ammo Counting:** Count your ammo. Whenever you fire a dart, it's detected using one of these methods:
	1. **Switch**: Detect shots every time the trigger is pressed. Orient a tactile switch to be pressed when the blaster's trigger is pressed, and wire it up to the microcontroller. May not be ideal for fully-automatic blasters.
	2. **Infrared (IR) Gate**: Using both an IR transmitter diode and IR receiver diode to detect dart passage rather than physical trigger pulls. The transmitter and receiver should be positioned so the transmitter shines directly on the receiver along the diameter of the barrel, forming a "gate". When a dart is fired, the gate is broken, which is detected with the microcontroller.
2. **Chronograph**: Using an IR gate, a chronograph can be implemented by recording the time it took for the dart to completely break through the gate, divided by the known length of the dart. Units are in feet per second (fps).
3. **Voltmeter**: Using a voltage divider, the Arduino can read the voltage of the battery used. Ideal for electronic-powered blasters, so you know when to switch out the batteries. Can detect the voltage of the battery powering the blaster, or of the battery powering the microcontroller.
4. **Select-Fire**:  Want to conserve ammo in your fully-automatic blaster? Toggle between safety, single-shot. three-round-burst, or fully-automatic with this feature. Requires a relay or MOSFET to control the pusher motor. IR gate required.
5. **Magazine Insertion Detection**:  Check if magazine is inserted in blaster, and when magazine is swapped out, the ammo will reset.
6. **Different Magazine Sizes**: Toggle between various magazines sizes with the press of a button. All NERF-compatible magazines can be configured: 5, 6, 10, 12, 15, 18, 20, 21, 25, and 36.
7. **Count-Up Mode**: Instead of counting down, it can count up every time a shot is fired.
___

## Parts and Tools Needed:
All builds require some sort of Arduino-compatible microcontroller. I recommend the [Adafruit Pro Trinket](https://www.adafruit.com/product/2000). Also make sure to have the [Arduino IDE](https://www.arduino.cc/en/Main/Software) installed.

### Parts:
|Features vs Parts Required | Ammo Counter - Switch | Ammo Counter - IR Gate| Chronograph | Voltmeter| Select - Fire | Usages| Notes |
|:--------------------------|:---------------------:|:---------------------:|:-----------:| :-------:|:-------------:|:-----:|:-----:|
| Microcontroller           | X                     | X | X | X | X | Brains of everything. | Microcontroller recommendation above |
| [Slider Switch](https://www.amazon.com/Uxcell-a13042200ux0676-Solder-Position-Switch/dp/B00CQNQN4Q/ref=sr_1_7?ie=UTF8&qid=1498072224&sr=8-7&keywords=slider+switch) | X | X | X | X | X | Used to toggle power/on of microcontroller | Can be replaced by rocker switch |
| [I2C OLED Display](https://www.amazon.com/Diymall-Yellow-Serial-Arduino-Display/dp/B00O2LLT30/ref=sr_1_1?ie=UTF8&qid=1498070241&sr=8-1&keywords=i2c+oled+display)                  | X | X | X | X |X | Used for displaying ammo, and if applicable, mode, voltage, and chrono readings |
| [Lever Switch](https://www.amazon.com/Gikfun-Micro-Switch-Arduino-EK1713/dp/B015W8S8NA/ref=sr_1_2?ie=UTF8&qid=1498070421&sr=8-2&keywords=arduino+switch)                       | X (2)           | X | X | X | X | Used for magazine insertion detection. If switch varient of ammo counter is selected, then another switch will be used for ammo counting.
| [Momentary Push Button](https://www.amazon.com/Gikfun-Micro-Switch-Arduino-EK1713/dp/B015W8S8NA/ref=sr_1_2?ie=UTF8&qid=1498070421&sr=8-2&keywords=arduino+switch)                     | X | X      | X | X | X (2) | Used for toggling between the various magazines sizes. If Select-Fire mode setup, then another button will be used to toggle through the various fire modes.
| [IR Transmitter and Receiver Diode](https://www.amazon.com/Gikfun-Infrared-Emitter-Receiver-Arduino/dp/B01HGIQ8NG/ref=pd_sim_60_2?_encoding=UTF8&pd_rd_i=B01HGIQ8NG&pd_rd_r=M28XT7S0DNCFMEJPPKXT&pd_rd_w=INV1r&pd_rd_wg=61093&psc=1&refRID=M28XT7S0DNCFMEJPPKXT)                   | | X | X | | X | Used for IR gate |
| Resistors (10K and 100k) |  |  |  | X | | Used for voltage divider to drop the voltage to a safe level for the microcontroller. | Resistors can be different values, just make sure the battery being checked has its voltage dropped to a voltage safe for the microcontroller. |
| [Relay](https://www.amazon.com/Tolako-Arduino-Indicator-Channel-Official/dp/B00VRUAHLE/ref=sr_1_2?ie=UTF8&qid=1498071951&sr=8-2&keywords=arduino+relay)| | | | | X | Used to control the NERF blaster's motors through the microcontroller |

### Tools:
1. Phillips Head Screwdriver
2. Drill
3. Soldering Iron and Solder + soldering materials/tools (flux, shrink wrap, helping hands, etc.)
3. Dremel or rotary tool (recommended, not required)
4. Hot glue and/or Epoxy putty (recommended, not required)
5. Sandpaper and/or files (recommened, not required)


**Extra Notes on Parts and Tools**: 
 1. Most of the parts can be bought cheaper from EBay or Digikey or other electronics stores.
 2. Microcontroller will need a battery to power it. A 9v will work fine. If the blaster is an electronic blaster, the microcontroller can be powered off the same batttery as the blaster, at the cost of a slight decrease in the blaster's performance.


___

## Installation
`cd ../Arduino/libraries`

`git clone https://github.com/etnom/nerf-ammo-counter`

`git clone https://github.com/adafruit/Adafruit_SSD1306`

`git clone https://github.com/adafruit/Adafruit-GFX-Library.git`

`git clone https://github.com/adafruit/Adafruit_SSD1306`

