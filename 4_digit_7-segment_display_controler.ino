#include <EEPROM.h>

//shift register pins
const int dataPin = 12; //DS
const int latchPin = 11; // STCP
const int clockPin = 10; // SHCP

//4 digits 7-segment display pins
const int segD1 = 7;
const int segD2 = 6;
const int segD3 = 5;
const int segD4 = 4;

const int displayCount = 4;
int displayDigits[] = {
  segD1, segD2, segD3, segD4
};

// variables used to select a digit and store the modified values of the digits
int currentDigit = 0;
int currentDigitsValues[] = {
  0, 0, 0, 0
};

//joystick pins
const int VRx = A0;
const int VRy = A1;
const int SW = 3;

//joystick variables
const int minThreshold = 300;
const int maxThreshold = 700;
int xPosition = 0;
int yPosition = 0;
bool isMoved = false;

//joystick button variables

// buttonIsPress is set to HIGH when a digit is selected
volatile bool buttonIsPress = LOW;
bool lastButtonState = LOW;
volatile unsigned long lastPress = 0;
const int debounceTime = 250;

//blinking DP variables
unsigned long blinkTimer = 0;
const int waitTime = 400;
const int resetBlinkTimer = 800;

//
const int eepromAddress = 0;

int digitArray[17] = {
  //A B C D E F G DP
  B11111100, // 0
  B01100000, // 1
  B11011010, // 2
  B11110010, // 3
  B01100110, // 4
  B10110110, // 5
  B10111110, // 6
  B11100000, // 7
  B11111110, // 8
  B11110110, // 9
  B11101110, // A
  B00111110, // b
  B10011100, // C
  B01111010, // d
  B10011110, // E
  B10001110, // F
};

void setup() {
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(SW, INPUT_PULLUP);
  for (int i = 0; i < displayCount; i++)
    pinMode(displayDigits[i], OUTPUT);

  attachInterrupt(digitalPinToInterrupt(SW), selectDigit, FALLING);
  readFromEEPROM(eepromAddress, currentDigitsValues, 4);

}

void loop() {
  xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);
  // if the button is not pressed we can change the digit selector
  if (buttonIsPress == LOW) {
    // if the button state is changed from press to unpressed save the modified values
    if (buttonIsPress != lastButtonState) {
      writeIntoEEPROM(eepromAddress, currentDigitsValues, 4);
      lastButtonState = buttonIsPress;
    }
    changeDisplayDigitPosition();
  }
  else {
    lastButtonState = HIGH;
    changeDisplayDigitValue();
  }

  displayData();

}

void writeReg(int digit) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, digit);
  digitalWrite(latchPin, HIGH);
}

void showDigit(int displayNumber) {
  for (int i = 0; i < displayCount; i++) {
    digitalWrite(displayDigits[i], HIGH);
  }
  digitalWrite(displayDigits[displayNumber], LOW);
}

void displayData() {
  for ( int i = 0; i < displayCount; i++) {
    showDigit(i);
    //show a blinking DP if the button is not press
    if (i == currentDigit && buttonIsPress == LOW) {
      if (millis() - blinkTimer < waitTime) {
        writeReg(digitArray[currentDigitsValues[i]]);
      }
      if (millis() - blinkTimer > waitTime) {
        // + 1 will set to HIGH the DP led of the current 7-segment display
        writeReg(digitArray[currentDigitsValues[i]] + 1);
      }
      if (millis() - blinkTimer > resetBlinkTimer) {
        blinkTimer = millis();
      }
    }
    else {
      writeReg(digitArray[currentDigitsValues[i]]);
    }
    // if the button is pressed, the DP led will be set to HIGH
    if (i == currentDigit && buttonIsPress == HIGH) {
      writeReg(digitArray[currentDigitsValues[i]] + 1);
    }
    delay(5);
  }
}

void changeDisplayDigitValue() {
  if (yPosition <= minThreshold && isMoved == false) {
    isMoved = true;
    currentDigitsValues[currentDigit]--;
    if (currentDigitsValues[currentDigit] < 0) {
      currentDigitsValues[currentDigit] = 9;
    }
  }

  if (yPosition >= maxThreshold && isMoved == false) {
    isMoved = true;
    currentDigitsValues[currentDigit]++;
    if (currentDigitsValues[currentDigit] > 9) {
      currentDigitsValues[currentDigit] = 0;
    }
  }

  if (yPosition >= minThreshold && yPosition <= maxThreshold) {
    isMoved = false;
  }
}


void changeDisplayDigitPosition() {
  if (xPosition <= minThreshold && isMoved == false) {
    isMoved = true;
    currentDigit--;
    if (currentDigit < 0) {
      currentDigit = 0;
    }
  }

  if (xPosition >= maxThreshold && isMoved == false) {
    isMoved = true;
    currentDigit++;
    if (currentDigit > 3) {
      currentDigit = 3;
    }
  }

  if (xPosition >= minThreshold && xPosition <= maxThreshold) {
    isMoved = false;
  }
}

void selectDigit() {
  if (millis() - lastPress > debounceTime) {
    buttonIsPress = !buttonIsPress;
  }
  lastPress = millis();
}

// function for writing an array into EEPROM

void writeIntoEEPROM(int address, int numbers[], int arraySize) {
  int addressIndex = address;
  for (int i = 0; i < arraySize; i++) {
    // shift to the right eight position and we get the higher 8 bits
    byte firstByte =  numbers[i] >> 8;
    // get the 8 least significants bits
    byte secondByte = numbers[i] & 0xFF;
    // write the bytes on consecutive address
    EEPROM.write(addressIndex, firstByte);
    EEPROM.write(addressIndex + 1, secondByte);
    addressIndex += 2;
  }
}

// function for reading an array from EEPROM

void readFromEEPROM(int address, int numbers[], int arraySize) {
  int addressIndex = address;
  for (int i = 0; i < arraySize; i++) {
    // get the first byte of the number and shift to the left 8 positions
    byte firstByte = EEPROM.read(addressIndex) << 8;
    // get the second byte of the number and sum the 2 bytes
    byte secondByte = EEPROM.read(addressIndex + 1);
    numbers[i] = firstByte + secondByte;
    // if the memory is not allocated initialize with 0
    if(numbers[i] < 0)
      numbers[i] = 0;
    addressIndex += 2;
  }
}
