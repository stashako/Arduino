
#define trigPin 10
#define sensePin 0


long previousMillis = 0;
float duration, distance;
boolean pwm = LOW;
void setup(){
Serial.begin(9600);
analogReference(INTERNAL);
pinMode(trigPin, OUTPUT);
}


void loop(){
unsigned long currentMillis = millis();

distance = analogRead(sensePin);
distance = (distance / 1024)*5;
Serial.print("Signal= ");
Serial.print(distance);
Serial.println(" V");

  if(currentMillis - previousMillis > 100){
    previousMillis = currentMillis;
    digitalWrite(trigPin, pwm);
    pwm = ! pwm;
    if(pwm == LOW){delay(10);}
    
  }




  
}
