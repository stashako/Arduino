#include "BMSerial.h" 
BMSerial mySerial(10,11);

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
  mySerial.begin(115200); 
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

    if(abs(leftMotorScaled) > deadZone)
    {
      if(leftMotorScaled < 0)
      {
        mySerial.write(leftMotorScaled*-10);
      }
      else
      {
        mySerial.write(leftMotorScaled*117);
      }
    }
    else
    {
      mySerial.write(64);
    }
    
    if(abs(rightMotorScaled) > deadZone)
    {
      if(rightMotorScaled < 0)
      {
        mySerial.write(leftMotorScaled*10);
      }
      else
      {
        mySerial.write(leftMotorScaled*-117);
      }
    }
    else
    {
      mySerial.write(64);
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
