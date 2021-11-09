const int pinA = 2;
const int pinB = 4;
const int pinC = 5;
const int pinD = 6;
const int pinE = 7;
const int pinF = 8;
const int pinG = 9;
const int pinDP = 11;

const int buzzerPin = 12;

const int antenaPin = A0;

const int buzzerTone = 2000;
const int toneDuration = 500;
const int toneMultiplier = 100;
const int refreshRate = 300;

const int segSize = 8;
const int noOfDigits = 11;
const int senseLimit = 9;
bool state = HIGH;
int antenaRead = 0;

int segments[segSize] = {
  pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP
};

byte digitMatrix[noOfDigits][segSize - 1] = {
// a  b  c  d  e  f  g
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}  // 9
};

void displayNumber(byte digit) {
  for(int i = 0; i < segSize-1;i++)
   digitalWrite(segments[i],digitMatrix[digit][i]);
  digitalWrite(segments[segSize-1],state);
}

void setup() {
  // put your setup code here, to run once:
  for( int i = 0; i< segSize; i++){
    pinMode(segments[i], OUTPUT);
  }
  pinMode(buzzerPin, OUTPUT);
  pinMode(antenaPin, INPUT);
  Serial.begin(9600);
}

void loop() {

  antenaRead = analogRead(antenaPin);
  
  if(antenaRead >= 1){
    antenaRead = constrain(antenaRead, 1, senseLimit);
    displayNumber(antenaRead);
    tone(buzzerPin, buzzerTone + antenaRead * toneMultiplier, toneDuration);
}
else{
  displayNumber(0);
}
delay(refreshRate);
}
