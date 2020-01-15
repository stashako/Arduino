int sensorPin1 = A0;    // select the input pin for the potentiometer
int sensorPin2 = A1;    // select the input pin for the potentiometer
int X = 0;  // variable to store the value coming from the sensor
int Y = 0;  // variable to store the value coming from the sensor


void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
    X = analogRead(sensorPin1);
    Y = analogRead(sensorPin2);

  if (Serial.available())
  {
 
    Serial.println(X); 
    Serial.println(Y); 
    Serial.println('a');   

  delay(2000);

  }
}
