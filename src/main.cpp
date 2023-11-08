// libray for motors
#include <AFMotor.h>
// librays for the transmitter/receiver
#include <SPI.h>

// declares all the motors
AF_DCMotor motor1(1); 
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

// int Xpot;
// int Ypot;

// sets the pins for the radio

// sets the max speed and the joystick values
int speed = 255;

int grid[5][5] = {{0}};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // the motors will be stopped
  motor1.setSpeed(0);  
  motor2.setSpeed(0);
  motor3.setSpeed(0);
  motor4.setSpeed(0);
}

// might need an update function for joystick, example can be found in Lab 4 Part 5

void loop() {
  // put your main code here, to run repeatedly:
  // radio.startListening();

    // forwar
        motor1.setSpeed(speed);
        motor1.run(FORWARD);
        motor2.setSpeed(speed);
        motor2.run(FORWARD);
        motor3.setSpeed(speed);
        motor3.run(FORWARD);
        motor4.setSpeed(speed);
        motor4.run(FORWARD);
        Serial.println("forward");
   
}
