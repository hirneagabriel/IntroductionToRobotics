const int pushButton = 2;
const int ledRedPedestrian = 4;
const int ledGreenPedestrian = 7;

const int ledRedCar = 8;
const int ledYellowCar = 12;
const int ledGreenCar = 13;

const int buzzerPin = 11;
int buzzerTone = 62;
int toneDuration = 300;
int pauseBetweenTones = 1000;
int pauseBetweenTonesWhenBlinking = 500; 

bool ledRedPedestrianState = HIGH;
bool ledGreenPedestrianState = LOW;
bool ledRedCarState = LOW;
bool ledYellowCarState = LOW;
bool ledGreenCarState = HIGH;

bool buttonState = HIGH;
bool lastButtonState = HIGH;
bool readingButton = LOW;

unsigned long int timer = 0;
unsigned long int lastBeep = 0;

unsigned int stateTwoCountDown = 10000;
unsigned int stateTwoDuration = 3000;
unsigned int stateThreeDuration = 10000;
unsigned int stateFourDuration = 15000;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pushButton, INPUT_PULLUP);
  pinMode(ledRedPedestrian, OUTPUT);
  pinMode(ledGreenPedestrian, OUTPUT);
  pinMode(ledRedCar, OUTPUT);
  pinMode(ledYellowCar, OUTPUT);
  pinMode(ledGreenCar, OUTPUT);

}

void loop() {

    buttonState = digitalRead(pushButton);
    
    //start timer when the button is pressed if no timer is running
    if(buttonState == LOW && ledGreenCarState == HIGH && timer == 0) {
      timer = millis();
    }
    
    //if the timer has started initiate state 2 after 10 seconds
    if((millis() - timer) > stateTwoCountDown && ledGreenCarState == HIGH && timer != 0) {
      ledGreenCarState = LOW;
      ledYellowCarState = HIGH;
      timer = millis();
     }
     
    //if the state 2 time has ended initiate state 3
    if((millis() - timer) > stateTwoDuration && ledYellowCarState == HIGH ) {
      ledYellowCarState = LOW;
      ledRedCarState = HIGH;
      ledRedPedestrianState = LOW;
      ledGreenPedestrianState = HIGH;
      timer = millis();
    }

    // make an annoying beeping sound for 10 seconds
    if((millis() - timer) < stateThreeDuration && ledGreenPedestrianState == HIGH) {
      beep();
    }

    //make an annoying beeping sound for another 5 seconds but faster and blink the green light for pedestrians also
    if((millis() - timer) > stateThreeDuration && (millis() - timer) < stateFourDuration && ledRedCarState == HIGH) {
     beepAndBlink();
    }

    //reset to state one
    if((millis() - timer) > stateFourDuration && ledRedCarState == HIGH) {
     ledGreenPedestrianState = LOW;
     ledRedPedestrianState = HIGH;
     ledRedCarState = LOW;
     ledGreenCarState = HIGH; 
     timer = 0;
     lastBeep = 0;
    }

  digitalWrite(ledGreenPedestrian, ledGreenPedestrianState);
  digitalWrite(ledRedPedestrian, ledRedPedestrianState);
  digitalWrite(ledGreenCar, ledGreenCarState);
  digitalWrite(ledRedCar, ledRedCarState);
  digitalWrite(ledYellowCar, ledYellowCarState);
 
}

//funtion for beep sound
void beep(){
 if((millis() - lastBeep) > pauseBetweenTones) {
  tone(buzzerPin, buzzerTone, toneDuration);
  lastBeep = millis();
 }
}

//function for beep sound and blinking
void beepAndBlink(){
 if((millis() - lastBeep) > pauseBetweenTonesWhenBlinking) {
  tone(buzzerPin, buzzerTone, toneDuration);
  ledGreenPedestrianState = HIGH;
  lastBeep = millis();
 }
 
 if((millis() - lastBeep) > toneDuration) {
 ledGreenPedestrianState = LOW;
 }
}
