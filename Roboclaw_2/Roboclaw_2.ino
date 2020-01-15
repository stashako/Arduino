#include "BMSerial.h" 
BMSerial mySerial(10,11); 

#define INPUT_SIZE 2
char input[INPUT_SIZE];

 void setup() {  
  
  mySerial.begin(115200);
  Serial.begin(115200);

 } 

 
 void loop() {  
 if (Serial.available())
  {
    memset(input, 0, sizeof(input));
    Serial.readBytes(input, INPUT_SIZE);
    

    int cmd = atoi(input);
    mySerial.write(cmd); 
    Serial.println(cmd);  

  }
 }
