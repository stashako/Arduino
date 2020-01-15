//See BareMinimum example for a list of library functions

//Includes required to use Roboclaw library
#include <SoftwareSerial.h>
#include "RoboClaw.h"

#define INPUT_SIZE 3
char input[INPUT_SIZE];

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
    
    int cmd = atoi(input); 
    Serial.println(cmd);  

  roboclaw.ForwardBackwardM1(address,cmd); //start Motor1 forward at half speed
  roboclaw.ForwardBackwardM2(address,cmd); //start Motor2 backward at half speed
  delay(2000);

  }

}
