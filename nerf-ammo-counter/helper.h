//since we have three buttons, I don't want to type the exact same code 3 times. So I use this. 
//Here, each button has all its own values, all for itself, and I only have to type the code once
class Button {
    public:
        //a variable to store the value of the pin, so the computer knows which one to check
        int PIN;
    
    //constructors
    public:
        //initialze some stuff for the button when its created
        Button();
        Button(int);
    
    public:
        //some special values for checking if the button is pressed, called debouncing
        //simply checking if a button has been pressed isn't always so easy, so we do this. 
        unsigned long lastDebounceTime;   //keep track of when the button was pressed
        unsigned long debounceDelay = 50;  //create a delay between when to check. Here, its 50 milliseconds. 

        int btnState;   //keep track of the state of the button: pressed(HIGH), or not pressed(LOW)
        int lastBtnState = LOW;   //and the last state of the button

        bool isPressed = false;   //so we can check the state of the button in other places

        unsigned long numTimesPressed = 0;    //keep track of how many times the button is pressed

    public:
        //here, we actually check if the button is pressed, "debounce"
        bool isBtnPressed(bool isCheckHighVal) {
            bool returnVal = false;     //flag so can return at end of method

            //read the state of the button
            this -> btnState = digitalRead(this -> PIN);
            

            //check if button changes state
            if (this -> btnState != this -> lastBtnState) {
              //delay
              if (micros() >= (this -> lastDebounceTime) + (this -> debounceDelay)) {
                //check if btn acutally pressed
                if (this -> btnState == isCheckHighVal) {
                    returnVal = true;
                    isPressed = true;   //it is pressed, so we have to let outside code know as well
                    numTimesPressed++;  //when the button is pressed, add 1 to the variable storing how many times its pressed
                } else {
                    isPressed = false;    //it is not pressed, so we have to let outside code know as well
                }
              }
            }   
                
            //set some values so we know what to check next time
            this -> lastDebounceTime = micros();
            this -> lastBtnState = this -> btnState;
            
            return returnVal;
        }   //method

};

//constructors
//stuff to do when the buttons are created
Button::Button () {
    PIN = -1;
}

//stuff to do when the buttons are created
Button::Button (int pin) { 
    //set up stuff for the button's pin
    PIN = pin;  

    pinMode(pin, INPUT);
}

//keep track of which pins will be used 
//
//
//
//if you want to use different pins, change these. The first value = trigger, second = mag release, third = toggle mag
const byte pinArr[] = {3, 4, 5};

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
byte magSizeArr[] = {5, 6, 10, 12, 15, 18, 20, 22, 25, 36, 0};  //keep track of the magazine sizes
byte currentMagSize = 5;  //keep track of the current magazine size
byte currentAmmo = magSizeArr[currentMagSize];    //keep track of how much ammo there currently is
byte maxAmmo = magSizeArr[currentMagSize];    //keep track of what the max ammo is, for use when reloading 

//setting up the buttons
Button btnArr[5]; //keep track of all the buttons
//create buttons, using the code at the top of this file, so the microcontroller knows they exist and what to do with them
void initButtons (int numOfBtns) {
  btnArr[numOfBtns];

    //0 = trigger, 1 = mag release, 2 = toggle mag
    for (int i = 0; i < numOfBtns; i++) {
      btnArr[i] = Button(pinArr[i]);  
    }
  
}

//check if the magazine is instered
//when the magazine is inserted, the magazine detection switch is pressed, and the microcontroller sees this as LOW
//when the magazine is not inserted, the magazine detection switch is not pressed, and the microcontroller sees this as HIGH
bool isMagInserted() {
  //check if micro controller sees the value as LOW -> the button is pressed -> a magazine is inserted
  if (btnArr[1].btnState == LOW) {    
      return true;
    //check if micro controller sees the value as HIGH -> the button is not pressed -> a magazine is not inserted
    } else if (btnArr[1].btnState == HIGH) { 
      return false;
    }
}

//display text onto the display
void displayText(String text) {
  byte textSize = 8;  //set the size of the text
  display.clearDisplay(); //clear the display, so the stuff that was here before is no longer here
  display.setTextSize(textSize);  //set the size of the text
  display.setTextColor(WHITE);    //set the color of text text
  //tell the display where to draw the text
  display.setCursor( (SCREEN_WIDTH/2) - ((text.length()*2) * (textSize * 1.5)), (SCREEN_HEIGHT/2) - (textSize * 3) );  //center text
  display.print(text);    //print the text
  display.display();    //display the text
}

//display ammo onto the display
void displayAmmo(){
  String textToDisplay;    //create something to store what to print. This is empty now
  //if magazine not inserted, display '00'
    if (!isMagInserted()) {
        textToDisplay = "00";
    }
    else {  //make sure magazine is inserted before displaying ammo
        //if the ammo to print, current ammo, is less that 10, make it like '01' or '04'  
        if (currentAmmo < 10) {
          textToDisplay = "0" + (String)currentAmmo; //fill the thing we used to store what to print
        } else {    //if not, leave it as is
          textToDisplay = (String)currentAmmo;   //fill the thing we used to store what to print
        }
    } 

    displayText(textToDisplay);  //display the text, the ammo
}

//count ammo
void countAmmo() {
  //when the magazine is inserted AND the trigger switch is pressed
    if ( (btnArr[0].isBtnPressed(true)) && isMagInserted() ){
      //make sure that the ammo is less than 99 so it doesnt overflow the display
      //make sure it's in increment mode
      if ( (magSizeArr[currentMagSize] == 0) && (currentAmmo < 99) ) {
          currentAmmo++;    //increment ammo

          //make sure that the ammo is more than 0 so no negative numbers are displayed
        //make sure it's in increment mode
        } else if ( (currentAmmo > 0) && (magSizeArr[currentMagSize] != 0) ){
          currentAmmo--;    //decrement ammo
        }
    }

    //make sure a magazine is inserted before displaying the ammo
    if (isMagInserted()) {
      displayAmmo();    //display the ammo
    }
  
}

//change magazines
void changeMag() {
  //make sure the magazine insertion detection button is pressed from not being pressed
  if (btnArr[1].isBtnPressed(false) ) {
        currentAmmo = maxAmmo;  //set current ammo to the max amount of ammo
        displayAmmo();  //display ammo
    }
  
}

//toggle between the various magazine sizes
void toggleMags () {
  //check if the magazine toggle button is pressed
  if (btnArr[2].isBtnPressed(true)) {
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
    }

    //make sure a magazine is inserted before display ammo
    if (isMagInserted()) {
        displayAmmo();    //display the maxAmmo
    }
  
}








