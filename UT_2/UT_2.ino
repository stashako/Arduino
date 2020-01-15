#include "NewPing.h"

#define TRIGER_PIN   10
#define ECHO_PIN     13
#define MAX_DISTANCE 400

NewPing sonar(TRIGER_PIN, ECHO_PIN, MAX_DISTANCE);
float distance;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
distance = sonar.ping_cm();

Serial.print("Distance= ");
if (distance >= 400 || distance <= 2){
  Serial.println(" OUt of range");
}
else{
  Serial.print(distance);
Serial.println(" cm");
delay(500);
}
delay(500);
}
