// max value that can be read from an analog pin
const int maxInAnalogValue = 1023;
// max value that can be write on an analog pin
const int maxOutAnalogValue = 255;

// pins for each color of the RGB LED
const int redPin = 11;
const int greenPin = 9;
const int bluePin = 3;

// pins for each potentiometer
const int potRedPin = A0;
const int potGreenPin = A1;
const int potBluePin = A2;

// brightness for each LED color
int brightnessRed = 0;
int brightnessGreen = 0;
int brightnessBlue = 0;

// values read from potentiometers
int potRedValue = 0;
int potGreenValue = 0;
int potBlueValue = 0;



void setup() {
  
  //declare the output pins
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  //declare the input pins
  pinMode(potRedPin, INPUT);
  pinMode(potGreenPin, INPUT);
  pinMode(potBluePin, INPUT);

}

void loop() {
  
  //read values from potentiometers
  potRedValue = analogRead(potRedPin);
  potGreenValue = analogRead(potGreenPin);
  potBlueValue = analogRead(potBluePin);

  //map potentiometers value to the output analog values
  brightnessRed = map(potRedValue, 0, maxInAnalogValue, 0, maxOutAnalogValue);
  brightnessGreen = map(potGreenValue, 0, maxInAnalogValue, 0, maxOutAnalogValue);
  brightnessBlue = map(potBlueValue, 0, maxInAnalogValue, 0, maxOutAnalogValue);

  //transmit the brightness to each color of the RGB LED
  analogWrite(redPin,  brightnessRed);
  analogWrite(greenPin, brightnessGreen);
  analogWrite(bluePin, brightnessBlue);  
}
