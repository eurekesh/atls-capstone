// libray for motors
#include <AFMotor.h>
// librays for the transmitter/receiver
#include <SPI.h>

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3 

#define RIGHT 0
#define LEFT 1

#define CHECK_INTERVAL 1000
#define RIGHT_TURN_TIME 1100
#define LEFT_TURN_TIME 900
#define FORWARD_TIME 1000

#define WHEEL_SPEED 255

// declares all the motors
AF_DCMotor motor1(1); 
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);
AF_DCMotor all_wheels[] = {motor1, motor2, motor3, motor4};

bool upcomingTurnDirection = RIGHT;

int grid[5][5] = {{0,0,0,0,0},
                  {0,0,0,0,0},
                  {0,0,0,0,0},
                  {0,0,0,0,0},
                  {0,0,0,0,0}
                  };
                  
int curr_position[2] = {2,2};
int curr_direction = NORTH;

void allWheelForward();
void leftTurn();
void rightTurn();
void updatePosition();
bool checkPosition();
bool isAboutToBeOutOfBounds();
bool canTurnCurrentDirection();
void printPositionAndDirection();


void setup() {
  Serial.begin(9600);

  motor1.setSpeed(0);  
  motor2.setSpeed(0);
  motor3.setSpeed(0);
  motor4.setSpeed(0);
}

void loop() {
  static unsigned long lastRefreshTime = 0;

	allWheelForward();
  printPositionAndDirection();
  
	if(millis() - lastRefreshTime >= CHECK_INTERVAL)
	{
		lastRefreshTime += CHECK_INTERVAL;

    if(curr_position[0] == 0 || curr_position[0] == 4) // we're at the top or bottom of the grid
    {
      if (curr_position[1] == 0 || curr_position[1] == 4) // we're also at an edge
      {
        if (!canTurnCurrentDirection())
        {
          if (upcomingTurnDirection == LEFT)
          {
            rightTurn();
            allWheelForward();
            rightTurn();
            allWheelForward();
          } else if (upcomingTurnDirection == RIGHT) {
            leftTurn();
            allWheelForward();
            leftTurn();
            allWheelForward();
          }
        }
      } else {

        if (upcomingTurnDirection == LEFT)
        {
          leftTurn();
          allWheelForward();
          leftTurn();
          allWheelForward();
        } else if (upcomingTurnDirection == RIGHT) {
          rightTurn();
          allWheelForward();
          rightTurn();
          allWheelForward();
        }
        upcomingTurnDirection = !upcomingTurnDirection;
      }
    }
  }

}

bool canTurnCurrentDirection()
{
  if (upcomingTurnDirection == RIGHT)
  {
    if (curr_direction == NORTH)
    {
      return curr_position[1] != 4;
    }
    else if (curr_direction == SOUTH)
    {
      return curr_position[1] != 0;
    }
  }
  else if (upcomingTurnDirection == LEFT)
  {
    if (curr_direction == NORTH)
    {
      return curr_position[1] != 0;
    }
    else if (curr_direction == SOUTH)
    {
      return curr_position[1] != 4;
    }
  }
  return false;
}

void updatePosition()
{
  switch (curr_direction)
  {
    case NORTH:
      curr_position[0]--;
      break;
    case EAST:
      curr_position[1]++;
      break;
    case SOUTH:
      curr_position[0]++;
      break;
    case WEST:
      curr_position[1]--;
      break;
  }
}

bool isAboutToBeOutOfBounds() {
  int x = curr_position[0];
  int y = curr_position[1];
  switch (curr_direction) {
    case NORTH:
      return x == 1;
    case EAST:
      return y == 4;
    case SOUTH:
      return x == 4;
    case WEST:
      return y == 1;
    default:
      return false;
  }
}

void allWheelForward()
{
  updatePosition();
  unsigned long turning_time = FORWARD_TIME;
  unsigned long start_time = millis();
  unsigned long finish_time = start_time + turning_time;

  while (millis() < finish_time)
  {
    for(int i = 0; i < 4; i++)
    {
      all_wheels[i].setSpeed(WHEEL_SPEED);
      all_wheels[i].run(FORWARD);
    }
  }
  for(int i = 0; i < 4; i++)
  {
    all_wheels[i].setSpeed(0);
    all_wheels[i].run(BRAKE);
  }
  delay(2000);
}

void leftTurn()
{
  if (curr_direction == NORTH)
  {
    curr_direction = WEST;
  }
  else
  {
    curr_direction--;
  }

  unsigned long turning_time = LEFT_TURN_TIME;
  unsigned long start_time = millis();
  unsigned long finish_time = start_time + turning_time;

  while (millis() < finish_time)
  {
    for(int i = 0; i < 4; i++)
    {
      all_wheels[i].setSpeed(WHEEL_SPEED);
      all_wheels[i].run(i < 2 ? FORWARD : BACKWARD);
    }
  }
  for(int i = 0; i < 4; i++)
  {
    all_wheels[i].setSpeed(0);
    all_wheels[i].run(BRAKE);
  }
  delay(2000);
}

void rightTurn()
{
  curr_direction = (curr_direction + 1) % 4;

  unsigned long turning_time = RIGHT_TURN_TIME;
  unsigned long start_time = millis();
  unsigned long finish_time = start_time + turning_time;

  while (millis() < finish_time)
  {
    for(int i = 0; i < 4; i++)
    {
      all_wheels[i].setSpeed(WHEEL_SPEED);
      all_wheels[i].run(i > 2 ? FORWARD : BACKWARD);
    }
  }
  for(int i = 0; i < 4; i++)
  {
    all_wheels[i].setSpeed(0);
    all_wheels[i].run(BRAKE);
  }
  delay(2000);
}

void printPositionAndDirection() {
  Serial.print("Current position: ");
  Serial.print(curr_position[0]);
  Serial.print(", ");
  Serial.print(curr_position[1]);
  Serial.print(" | Current direction: ");

  switch(curr_direction) {
    case NORTH:
      Serial.println("NORTH");
      break;
    case EAST:
      Serial.println("EAST");
      break;
    case SOUTH:
      Serial.println("SOUTH");
      break;
    case WEST:
      Serial.println("WEST");
      break;
    default:
      Serial.println("UNKNOWN");
      break;
  }
}