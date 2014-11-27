/*
  Converts the servo output pulses to separate pins by measuring the length of the PWM-pulse
  Possible improvement might be to convert the digitial writes to raw port writes.
  
  Copyright Erik Zachrisson 2014
  
 */

int ailPwmLen, elevPwmLen;

const int forwardPin = 4;
const int backwardPin = 5;
const int leftPin = 6;
const int rightPin = 7;

// the setup routine runs once when you press reset:
void setup() {
  ailPwmLen = 0;
  elevPwmLen = 0;
  //Serial.begin(9600);
  
  digitalWrite(forwardPin, 0);
  digitalWrite(backwardPin, 0);
  digitalWrite(leftPin, 0);
  digitalWrite(rightPin, 0);
}

//Ail filters
//Left = 51, 52
//Right = 87, 88
//Middle = 69, 70

// the loop routine runs over and over again forever:
void loop() {  
  if (digitalRead(2)) {
    ailPwmLen++;  
  } else {
    if (ailPwmLen > 0) {
      if (ailPwmLen < 65) {
        digitalWrite(leftPin, 1);
        digitalWrite(rightPin, 0);
      } else if (ailPwmLen > 75) {
        digitalWrite(leftPin, 0);
        digitalWrite(rightPin, 1);
      } else {
        digitalWrite(leftPin, 0);
        digitalWrite(rightPin, 0);           
      }
      ailPwmLen = 0; 
    }
  }
  
  //Elev filters
//Middle 67 - 68
//Forward 84 - 85
//Backward 49 - 50
  if (digitalRead(3)) {
    elevPwmLen++;  
  } else {
    if (elevPwmLen > 0) {
      if (elevPwmLen < 60) {
          digitalWrite(forwardPin, 0);
          digitalWrite(backwardPin, 1);
          //Serial.println("backward");
      } else if (elevPwmLen > 70) {
          digitalWrite(forwardPin, 1);
          digitalWrite(backwardPin, 0);
          //Serial.println("forward");
      } else {
          digitalWrite(forwardPin, 0);
          digitalWrite(backwardPin, 0);
          //Serial.println("middle");
      }  
      elevPwmLen = 0; 
    }
  }
}
