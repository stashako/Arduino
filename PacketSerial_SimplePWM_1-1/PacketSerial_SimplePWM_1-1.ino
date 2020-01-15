//See BareMinimum example for a list of library functions

//Includes required to use Roboclaw library
#include <SoftwareSerial.h>
#include "RoboClaw.h"

#define INPUT_SIZE 4
char input[INPUT_SIZE];
float deadZone = 0.05;
//int cmd = 64;
//See limitations of Arduino SoftwareSerial
SoftwareSerial serial(10,11);	
RoboClaw roboclaw(&serial,10000);

#define address 0x80

void setup() {
  //Open roboclaw serial ports
  roboclaw.begin(38400);
  Serial.begin(115200);
}

void loop() {

  if (Serial.available())
  {
    memset(input, 0, sizeof(input));
    Serial.readBytes(input, INPUT_SIZE);
    
    float cmd = atof(input); 
    Serial.println(cmd);


      if(abs(cmd) > deadZone)
    {
        roboclaw.ForwardBackwardM1(address,(cmd*44)+64);
        Serial.println(cmd);
        delay(200);
    }
    else
    {
      roboclaw.ForwardBackwardM1(address,64);
    }
    
    if(abs(cmd) > deadZone)
    {
        roboclaw.ForwardBackwardM2(address,(cmd*44)+64);
        Serial.println(cmd);
        delay(200);
    }
    else
    {
      roboclaw.ForwardBackwardM2(address,64);
    }

 
  }

}
