#include <Metro.h> 

#define trigPin 10
#define sensePin 0

float duration, distance;
boolean blink1State = false;
boolean blink2State = false;

Metro blink1Metro = Metro(1);
Metro blink2Metro = Metro(1);


void setup(){
Serial.begin(9600);
analogReference(INTERNAL);
pinMode(trigPin, OUTPUT);
}


void loop(){


  if(blink2Metro.check()){
    
    distance = analogRead(sensePin);
    distance = (distance / 1024)*5;
    Serial.print("Signal= ");
    Serial.print(distance);
    Serial.println(" V");

  }

  if(blink1Metro.check()){
    
    digitalWrite(trigPin, LOW);
    delayMicroseconds(100);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(2);
  }




  
}
