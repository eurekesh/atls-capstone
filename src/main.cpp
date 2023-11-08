// libray for motors
#include <AFMotor.h>
// librays for the transmitter/receiver
#include <SPI.h>

// declares all the motors
AF_DCMotor motor1(1); 
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);
AF_DCMotor all_wheels[] = {motor1, motor2, motor3, motor4};

// int Xpot;
// int Ypot;

// sets the pins for the radio

// sets the max speed and the joystick values
int speed = 255;

int grid[6][6] = {{0}};
int curr_position[2] = {3,3};

void allWheels(int);
void leftTurn(int);
void rightTurn(int);

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

  // allWheels(100);
  
}


void allWheels(int speed)
{
  for(int i = 0; i < 4; i++)
  {
    all_wheels[i].setSpeed(speed);
    all_wheels[i].run(FORWARD);
  }
}

void leftTurn(int speed)
{
  for(int i = 0; i < 4; i++)
  {
    int using_speed = speed;
    if (i < 2)
    {
      using_speed /= 3;
    }
    all_wheels[i].setSpeed(using_speed);
    all_wheels[i].run(FORWARD);
  }
}

void rightTurn(int speed)
{
  for(int i = 0; i < 4; i++)
  {
    int using_speed = speed;
    if (i > 2)
    {
      using_speed /= 3;
    }
    all_wheels[i].setSpeed(using_speed);
    all_wheels[i].run(FORWARD);
  }
}