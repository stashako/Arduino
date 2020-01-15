#include "NewPing.h"

#define TRIGER_PIN   10
int val = 0;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(TRIGER_PIN, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
val = digitalRead(TRIGER_PIN);

Serial.print("light= ");
if (val == HIGH){
  Serial.println(" ON");
}
else{
Serial.println("OFF");
delay(500);
}
delay(500);
}
