#define trigPin 10
#define sensePin 0

float duration, distance;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
analogReference(INTERNAL);
distance = analogRead(sensePin);

}

void loop() {
pinMode(trigPin, OUTPUT);
digitalWrite(trigPin, LOW);
delay(10);
digitalWrite(trigPin, HIGH);
delay(100);
digitalWrite(trigPin, LOW);

//pinMode(trigPin, INPUT);
//duration = pulseIn(trigPin, HIGH);

distance = (distance / 1024)*5;
//distance = (duration / 2) * 0.343;

Serial.print("Signal= ");
Serial.print(distance);
Serial.println(" V");

//delayMicroseconds(500);
}
