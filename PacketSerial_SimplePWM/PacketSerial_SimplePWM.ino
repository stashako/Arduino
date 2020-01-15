//See BareMinimum example for a list of library functions

//Includes required to use Roboclaw library
#include <SoftwareSerial.h>
#include "RoboClaw.h"

//See limitations of Arduino SoftwareSerial
SoftwareSerial serial(10,11);	
RoboClaw roboclaw(&serial,10000);

#define address 0x80

void setup() {
  //Open roboclaw serial ports
  roboclaw.begin(38400);
}

void loop() {
  roboclaw.ForwardM1(address,0); //start Motor1 forward at half speed
  roboclaw.BackwardM2(address,0); //start Motor2 backward at half speed
  delay(2000);

  roboclaw.BackwardM1(address,0);
  roboclaw.ForwardM2(address,0);
  delay(2000);

  roboclaw.ForwardBackwardM1(address,64); //start Motor1 forward at half speed
  roboclaw.ForwardBackwardM2(address,64); //start Motor2 backward at half speed
  delay(2000);

  roboclaw.ForwardBackwardM1(address,64);
  roboclaw.ForwardBackwardM2(address,64);
  delay(2000);
}
