
#include <Servo.h>

Servo s;


const int thermistorPin = A0;  
const float R1 = 10000.0;      
const float BETA = 3950;       
const float T0 = 298.15;       


const int smokePin = 2;
const int rainPin = 3;
const int evalPin = 4;


const int motorPWM = 6;
const int motorIN1 = 7;
const int motorIN2 = 8;

// Servo control pin
const int servoPin = 11;

void setup() {
  Serial.begin(9600);

  pinMode(motorIN1, OUTPUT);
  pinMode(motorIN2, OUTPUT);
  pinMode(smokePin, INPUT);
  pinMode(rainPin, INPUT);
  pinMode(evalPin, INPUT);

  s.attach(servoPin, 1000, 2000);
}

void loop() {

  int analogValue = analogRead(thermistorPin);
  float voltage = analogValue * 5.0 / 1023.0;
  float resistance = R1 * (5.0 / voltage - 1.0);
  float tempK = 1.0 / (1.0 / T0 + log(resistance / R1) / BETA);
  float tempC = tempK - 273.15;


  bool smoke = digitalRead(smokePin);
  bool rain = digitalRead(rainPin);
  bool evalution = digitalRead(evalPin);

  String fanStatus;
  String canopyStatus;

 
  if (smoke == HIGH) {
    
    analogWrite(motorPWM, 255);
    digitalWrite(motorIN1, HIGH);
    digitalWrite(motorIN2, LOW);
    fanStatus = "Reverse";
  } else if (tempC >= 30) {
 
    analogWrite(motorPWM, 255);
    digitalWrite(motorIN1, LOW);
    digitalWrite(motorIN2, HIGH);
    fanStatus = "High Speed";
  } else if (tempC >= 20 && tempC < 30) {
    
    analogWrite(motorPWM, 100);
    digitalWrite(motorIN1, LOW);
    digitalWrite(motorIN2, HIGH);
    fanStatus = "Low Speed";
  } else {
   
    analogWrite(motorPWM, 0);
    digitalWrite(motorIN1, LOW);
    digitalWrite(motorIN2, LOW);
    fanStatus = "Off";
  }


  if (rain) {
    s.write(180);
    canopyStatus = "Closed";
  } else if (!rain && evalution) {
    s.write(90);
    canopyStatus = "Half Open";
  } else {
    s.write(0);
    canopyStatus = "Fully Open";
  }

  Serial.print("Temperature: ");
  Serial.print(tempC);
  Serial.print(" °C | Fan Status: ");
  Serial.print(fanStatus);
  Serial.print(" | Canopy Position: ");
  Serial.println(canopyStatus);

  delay(500);
}

