//Roboclaw simple serial example.  Set mode to 5.  Option to 4(38400 bps) 
#include "BMSerial.h" 
 BMSerial mySerial(10,11); 
 void setup() {  
  mySerial.begin(38400); 
 } 
 void loop() { 
  

  

  mySerial.write(54);   
  delay(1000);
  mySerial.write(182); 
  delay(1000);


/*
  mySerial.write(96);  
  mySerial.write(224); 
  delay(2000);
*/

  }
