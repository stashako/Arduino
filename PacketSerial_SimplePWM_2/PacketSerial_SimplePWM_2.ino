//See BareMinimum example for a list of library functions

//Includes required to use Roboclaw library
#include <SoftwareSerial.h>
#include "RoboClaw.h"

#define INPUT_SIZE 2
char input[INPUT_SIZE];
int sensorPin1 = A0;    // select the input pin for the potentiometer
int sensorPin2 = A1;    // select the input pin for the potentiometer
float X = 0;  // variable to store the value coming from the sensor
float Y = 0;  // variable to store the value coming from the sensor
//See limitations of Arduino SoftwareSerial
SoftwareSerial serial(10,11);	
RoboClaw roboclaw(&serial,10000);

#define address 0x80

void setup() {
  //Open roboclaw serial ports
  roboclaw.begin(38400);

}

void loop() {
    X = analogRead(sensorPin1);
    Y = analogRead(sensorPin2);
    X=((X-505)/11.625)+63.5;
    Y=((Y-525)/11.625)+65.2;

  roboclaw.ForwardBackwardM1(address,X);
  roboclaw.ForwardBackwardM2(address,Y);

}
