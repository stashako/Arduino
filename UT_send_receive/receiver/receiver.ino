
#define sensePin 0
float distance;

void setup(){
Serial.begin(9600);
analogReference(INTERNAL1V1);
}


void loop(){

distance = analogRead(sensePin);
distance = (distance)*5;
Serial.print("Signal= ");
Serial.print(distance);
Serial.println(" mV");
  
}
