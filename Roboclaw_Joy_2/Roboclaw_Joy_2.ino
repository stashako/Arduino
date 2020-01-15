#include <SoftwareSerial.h>
#include "RoboClaw.h"

//*****************************************
SoftwareSerial serial(10,11);  
RoboClaw roboclaw(&serial,10000);

#define address 0x80
//*******************************************
unsigned long curmillis = 0;
//**************************** MiniRover Motor ****************************************//

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
   //Open roboclaw serial ports
  roboclaw.begin(38400);
  Serial.begin(115200);
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
  
  if (Serial.available())
  {
    memset(input, 0, sizeof(input));
    Serial.readBytes(input, INPUT_SIZE);
    float cmd = atof(input); 
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

    //Serial.println(leftMotor);
    //Serial.println(abs(leftMotorScaled));
    //Serial.println(rightMotor);
    //Serial.println(abs(rightMotorScaled));

//*******************************************************
    if(abs(leftMotorScaled) > deadZone)
    {
        roboclaw.ForwardBackwardM1(address,(leftMotorScaled*44)+64);
        //Serial.println(leftMotorScaled);    
    }
    else
    {
      roboclaw.ForwardBackwardM1(address,64);
    }
    
    if(abs(rightMotorScaled) > deadZone)
    {
        roboclaw.ForwardBackwardM2(address,(rightMotorScaled*44)+64);
        //Serial.println(rightMotorScaled);
        
    }
    else
    {
      roboclaw.ForwardBackwardM2(address,64);
    }

    //delay(2000);
//**********************************************************
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
          Serial.println("exiting...");
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
