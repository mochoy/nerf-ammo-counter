//yay done! Now just need to test...


class Button {
    public:
        int PIN;
    
    //constructors
    public:
        Button();
        Button(int);
    
    public:
        unsigned long lastDebounceTime;
        unsigned long debounceDelay = 50;
        
        int btnState;
        int lastBtnState = LOW;
    
    public:
        bool isBtnPressed() {
            bool returnVal = false;     //flag so can return at end of method
            
            this -> btnState = digitalRead(this -> PIN);
            
            //delay
            if (micros() >= (this -> lastDebounceTime) + (this -> debounceDelay)) {
                //check if button changes state
                if (this -> btnState != this -> lastBtnState) {
                    //check if btn acutally pressed
                    if (this -> btnState == HIGH) {
                        returnVal = true;
                    }
                }   
                
            }
            
            this -> lastDebounceTime = micros();
            this -> lastBtnState = this -> btnState;
            
            return returnVal;
        }   //method

  public:
    bool isOpen() {
        if (digitalRead(this -> PIN) == LOW) {
          return true;
        } else {
          return false;
        }
    }

};

//constructors
Button::Button () {
    PIN = -1;
}

Button::Button (int pin) { 
    PIN = pin;

    pinMode(pin, INPUT);
}

const byte pinArr[] = {3, 4, 5};  //first = trigger, second = mag release, third = toggle mag

long int lastDelayTime = 0;

byte magSizeArr[9] = {5, 6, 10, 12, 15, 18, 22, 25, 36};
byte currentMagSize = 5;
byte currentAmmo = magSizeArr[currentMagSize]; 
byte maxAmmo = magSizeArr[currentMagSize];

Button btnArr[5];
void initButtons (int numOfBtns) {
  btnArr [numOfBtns];

  //0 = trigger, 1 = mag release, 2 = toggle mag
  for (int i = 0; i < numOfBtns; i++) {
    btnArr[i] = Button(pinArr[i]);  
  }
  
}

void displayText(String text) {
  byte textSize = 8;
  display.clearDisplay();
  display.setTextSize(textSize);
  display.setTextColor(WHITE);
  display.setCursor( (SCREEN_WIDTH/2) - ((text.length()*2) * (textSize * 1.5)), (SCREEN_HEIGHT/2) - (textSize * 3) );  //center text
  display.print(text);
  display.display();
}

void displayAmmo(){
  String text;
  
  if (currentAmmo < 10) {
    text = "0" + (String)currentAmmo;
  } else {
    text = (String)currentAmmo;
  }
  
  displayText(text);

  lastDelayTime = 0;
}

void flashAmmo() {
  bool toDisplay = false;
  String text = "00";
  
  if ( (lastDelayTime == 0) || (lastDelayTime + 500 > micros()) ) {
    toDisplay = true;
    lastDelayTime = micros();
  } else {
    toDisplay = false;
  }

  if (toDisplay) {
    displayText(text);
  } else {
    display.clearDisplay();
  }
  
}

void countAmmo() {
  if (btnArr[0].isBtnPressed()) {
    if (currentAmmo > 0) {
      currentAmmo--;
    }
  }
  displayAmmo();
  
}

void changeMag() {
  if ( (btnArr[1].isBtnPressed()) && (!btnArr[1].isOpen()) )  {
    currentAmmo = maxAmmo;
    displayAmmo();
  } else if (btnArr[1].isOpen()) {
    
  }

  
}

void toggleMags () {
  if (btnArr[2].isBtnPressed()) {
    if (currentMagSize < 8) {
      currentMagSize ++;
    } else {
      currentMagSize = 0;
    }

    maxAmmo = magSizeArr[currentMagSize];
    currentAmmo = maxAmmo;
    displayAmmo();
  }
  
}








