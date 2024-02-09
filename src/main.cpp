#include <Arduino.h>
#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>

#define HAenA A1
#define HAin1 0
#define HAin2 1
#define HAin3 2
#define HAin4 3
#define HAenB A2

#define HBenA A3
#define HBin1 4
#define HBin2 5
#define HBin3 6
#define HBin4 7
#define HBenB A4

#define button 13

int rotDirection = 0;
int pressed = false;

void setup() {
  pinMode(HAenA, OUTPUT);
  pinMode(HAin1, OUTPUT);
  pinMode(HAin2, OUTPUT);
  pinMode(HAenB, OUTPUT);
  pinMode(HAin3, OUTPUT);
  pinMode(HAin4, OUTPUT);

  pinMode(HBenA, OUTPUT);
  pinMode(HBin1, OUTPUT);
  pinMode(HBin2, OUTPUT);
  pinMode(HBenB, OUTPUT);
  pinMode(HBin3, OUTPUT);
  pinMode(HBin4, OUTPUT);

  pinMode(button, INPUT);

  // Set initial rotation direction
  digitalWrite(HAin1, HIGH);
  digitalWrite(HAin2, LOW);

  digitalWrite(HAin3, LOW);
  digitalWrite(HAin4, HIGH);

  digitalWrite(HBin1, LOW);
  digitalWrite(HBin2, HIGH);

  digitalWrite(HBin3, HIGH);
  digitalWrite(HBin4, LOW);
  

}

void loop() {
  int potValue = analogRead(A0); // Read potentiometer value
  int pwmOutput = map(potValue, 0, 1023, 0 , 255); // Map the potentiometer value from 0 to 255
  analogWrite(HAenA, pwmOutput); // Send PWM signal to L298N Enable pin
  analogWrite(HAenB, pwmOutput); // Send PWM signal to L298N Enable pin
  analogWrite(HBenA, pwmOutput); // Send PWM signal to L298N Enable pin
  analogWrite(HBenB, pwmOutput); // Send PWM signal to L298N Enable pin

  // Read button - Debounce
  if (digitalRead(button)) {
    pressed = !pressed;
  }
  while (digitalRead(button));
  delay(20);

  // If button is pressed - change rotation direction
  if (pressed && rotDirection == 0) {
    digitalWrite(HAin1, LOW);
    digitalWrite(HAin2, HIGH);

  digitalWrite(HAin3, HIGH);
  digitalWrite(HAin4, LOW);

  digitalWrite(HBin1, HIGH);
  digitalWrite(HBin2, LOW);

  digitalWrite(HBin3, LOW);
  digitalWrite(HBin4, HIGH);
    rotDirection = 1;
    delay(20);
  }
  // If button is pressed - change rotation direction
  if (!pressed && rotDirection == 1) {
    digitalWrite(HAin1, HIGH);
    digitalWrite(HAin2, LOW);

    digitalWrite(HAin3, LOW);
    digitalWrite(HAin4, HIGH);

    digitalWrite(HBin1, LOW);
    digitalWrite(HBin2, HIGH);

    digitalWrite(HBin3, HIGH);
    digitalWrite(HBin4, LOW);
    rotDirection = 0;
    delay(20);
  }
}