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
    
    public:
        bool isBtnPressed() {
            bool returnVal = false;     //flag so can return at end of method
            
            this -> btnState = digitalRead(this -> PIN);
            

            //check if button changes state
            if (this -> btnState != this -> lastBtnState) {
              //delay
              if (micros() >= (this -> lastDebounceTime) + (this -> debounceDelay)) {
                //check if btn acutally pressed
                if (this -> btnState == HIGH) {
                    returnVal = true;
                    isPressed = true;
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
    if ( (btnArr[0].isBtnPressed()) && isMagInserted() ){
      if ( (currentMagSize == 9) && (currentAmmo < 99) ) {
        currentAmmo++;
      } else if ( (currentAmmo > 0) && (currentMagSize != 9) ){
        currentAmmo--;
      }
    }
    displayAmmo();  
  
}

void changeMag() {
  if ( (btnArr[1].isBtnPressed()) && (true) ) {
    currentAmmo = maxAmmo;
    displayAmmo();
  }
  
}

void toggleMags () {
  if (btnArr[2].isBtnPressed()) {
    if (currentMagSize < 9) {
      currentMagSize ++;
    } else {
      currentMagSize = 0;
    }

    maxAmmo = magSizeArr[currentMagSize];
    currentAmmo = maxAmmo;
    displayAmmo();
  }
  
}
