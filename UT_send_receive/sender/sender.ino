
#define trigPin 10

void setup(){
Serial.begin(9600);
}


void loop(){
    pinMode(trigPin, OUTPUT);
    digitalWrite(trigPin, LOW);
    delay(10000);
    digitalWrite(trigPin, HIGH);
    delay(100);
    pinMode(trigPin, INPUT);

}
