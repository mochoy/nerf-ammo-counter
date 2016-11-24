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

        bool isPressed = false;

        unsigned long numTimesPressed = 0;
    
    public:
        bool isBtnPressed(bool isCheckHighVal) {
            bool returnVal = false;     //flag so can return at end of method
            
            this -> btnState = digitalRead(this -> PIN);
            

            //check if button changes state
            if (this -> btnState != this -> lastBtnState) {
              //delay
              if (micros() >= (this -> lastDebounceTime) + (this -> debounceDelay)) {
                //check if btn acutally pressed
                if (this -> btnState == isCheckHighVal) {
                    returnVal = true;
                    isPressed = true;
                    numTimesPressed++;
                } else {
                    isPressed = false;
                }
              }
            }   
                
            
            this -> lastDebounceTime = micros();
            this -> lastBtnState = this -> btnState;
            
            return returnVal;
        }   //method

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

byte magSizeArr[10] = {5, 6, 10, 12, 15, 18, 22, 25, 36, 0};
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
}

bool isMagInserted() {
  if (btnArr[1].btnState == LOW) {
    return true;
  } else if (btnArr[1].btnState == HIGH) {
    return false;
  }
}

void countAmmo() {
    if ( (btnArr[0].isBtnPressed(true)) && isMagInserted() ){
      if ( (currentMagSize == 9) && (currentAmmo < 99) ) {
        currentAmmo++;
      } else if ( (currentAmmo > 0) && (currentMagSize != 9) ){
        currentAmmo--;
      }
    }

    if (isMagInserted()) {
      displayAmmo();  
    }
  
}

void changeMag() {
  if (btnArr[1].isBtnPressed(false) ) {
      currentAmmo = maxAmmo;
      displayAmmo();
  }
  
}

void toggleMags () {
  if (btnArr[2].isBtnPressed(true)) {
    if (currentMagSize < 9) {
      currentMagSize ++;
    } else {
      currentMagSize = 0;
    }

    maxAmmo = magSizeArr[currentMagSize];
    currentAmmo = maxAmmo;
  }

   if (isMagInserted()) {
      displayAmmo();  
    }
  
}

unsigned long lastFlashTime;
int flashDelay = 300;
void flashEmptyMag () {
  if (!isMagInserted()) {
    currentAmmo = 00;

    displayAmmo();
    delay(1000);
    display.clearDisplay();
    delay(1000);
  
    lastFlashTime = millis();
  }
  
}



  


