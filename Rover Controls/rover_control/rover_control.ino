

#include <Wire.h>
#include <Adafruit_MotorShield.h>


#include "utility/Adafruit_MS_PWMServoDriver.h"


//*************************************************************************************//


unsigned long curmillis = 0;


//**************************** MiniRover Motor ****************************************//
// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *lMotor = AFMS.getMotor(1);
// You can also make another motor on port M2
Adafruit_DCMotor *rMotor = AFMS.getMotor(2);
// Motor for the cable reel- cable management system
Adafruit_DCMotor *cMotor = AFMS.getMotor(3);
// Motor for the cable management system active control
Adafruit_DCMotor *cMotor_s = AFMS.getMotor(4);

// "O|Snum1|Snum2|Snum3" 
// SnumX => S-> pos/neg, numX-> two digits (033 equals to 0.33, with max=1.00)
// Snum1 = forward/backward of joy (forward -> pos)
// Snum2 = left/right of joy (right -> pos)
// Snum3 = in/out of cable (out -> pos)
#define INPUT_SIZE 16
char input[INPUT_SIZE];
char *token;

float throttle = 0;
float direction = 0;
float maxMotorScale = 0;
float leftMotor = 0;
float rightMotor = 0;
float leftMotorScaled = 0;
float rightMotorScaled = 0;
float deadZone = 0.05; 
float cableCmd = 0;
float m3m4_ratio_in = 0.5; //m4 = m3m4_ratio * m3
float m3m4_ratio_out = 0.8; //m4 = m3m4_ratio * m3




//************** setup *******************//
void setup() {
  
  Serial.begin(115200);
  Serial1.begin(115200);
  Serial.println("loading ...");


}


//************** loop *******************//
void loop() {
  //update the current time in milli seconds, Do not remove it !!
  curmillis = millis();

  //perform motor control
  motorControl();


}



void motorControl()
{
  throttle = 0;
  direction = 0;
  
  if (Serial1.available())
  {
    memset(input, 0, sizeof(input));
    Serial1.readBytes(input, INPUT_SIZE);
    //Serial.println(input);
    processCommand(input);

    //mix throttle and direction
    leftMotor = throttle-direction;
    rightMotor = throttle+direction;
  
    //choose the max scale value if it is above 1
    maxMotorScale = max(leftMotor,rightMotor);
    maxMotorScale = max(1,maxMotorScale);

    //and apply it to the mixed values
    leftMotorScaled = constrain(leftMotor/maxMotorScale,-1,1);
    rightMotorScaled = constrain(rightMotor/maxMotorScale,-1,1);

    //Serial.print("throttle= ");
    //Serial.println(throttle);
    //Serial.print("dir= ");
    //Serial.println(direction);
    //Serial.print("left = ");
    //Serial.println(leftMotorScaled*100);
    //Serial.print("right = ");
    //Serial.println(rightMotorScaled*100);

    if(abs(leftMotorScaled) > deadZone)
    {
      if(leftMotorScaled < 0)
      {
        lMotor->setSpeed(leftMotorScaled*-255);
        lMotor->run(FORWARD);
      }
      else
      {
        lMotor->setSpeed(leftMotorScaled*255);
        lMotor->run(BACKWARD);
      }
    }
    else
    {
      lMotor->run(RELEASE);
    }
    
    if(abs(rightMotorScaled) > deadZone)
    {
      if(rightMotorScaled < 0)
      {
        rMotor->setSpeed(rightMotorScaled*-255);
        rMotor->run(BACKWARD);
      }
      else
      {
        rMotor->setSpeed(rightMotorScaled*255);
        rMotor->run(FORWARD);
      }
    }
    else
    {
      rMotor->run(RELEASE);
    }


  }
}

void processCommand(char* input) {
  token = strtok(input, "|");
  int cnt = 0;
  while( token != NULL ) 
   {
      //Serial.println(token);
      if (cnt == 0)
      {
        if (token[0] != 'O')
        {
          Serial1.println("exiting...");
          break;
        }
      }
      else
      {
        if(cnt == 1)
          throttle = processSubCmd(token);
        else if(cnt == 2)
          direction = processSubCmd(token);
        else if(cnt == 3)
          cableCmd = processSubCmd(token);
      }
      
      token = strtok(NULL, "|");
      cnt = cnt + 1;
   }
}

float processSubCmd(char* input) {
  char sign = input[0];
  float cmdNum = atof(++input)/100.0;
  if(sign == '-')
    return cmdNum*-1;
  else
    return cmdNum;
}
