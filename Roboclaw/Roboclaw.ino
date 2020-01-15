//Set mode to 7(packet serial address 0x80) and option to 4(38400) 
 //Includes required to use Roboclaw library 
 #include "BMSerial.h" 
 #include "RoboClaw.h" 
 //Roboclaw Address 
 #define address 0x80 
 //Setup communcaitions with roboclaw. Use pins 10 and 11 with 10ms timeout 
 RoboClaw roboclaw(10,11,10000); 
 void setup() {   
  //Communciate with roboclaw at 38400bps   
  roboclaw.begin(38400);   
  roboclaw.ForwardMixed(address, 0);   
  roboclaw.TurnRightMixed(address, 0); 
  } 
 void loop() {   
  //Using independant motor Forward and Backward commands   
  roboclaw.ForwardM1(address,64); //start Motor1 forward at half speed   
  roboclaw.BackwardM2(address,64); //start Motor2 backward at half speed   
  delay(2000);   
  roboclaw.BackwardM1(address,64);   
  roboclaw.ForwardM2(address,64);   
  delay(2000);   
  roboclaw.BackwardM1(address,0);   
  roboclaw.ForwardM2(address,0);   
  delay(2000); 
 }
   //Using independant motor combined forward/backward commands    
  roboclaw.ForwardBackwardM1(address,96); //start Motor1 forward at half speed   
  roboclaw.ForwardBackwardM2(address,32); //start Motor2 backward at half speed   
  delay(2000);   
  roboclaw.ForwardBackwardM1(address,32);   
  roboclaw.ForwardBackwardM2(address,96);   
  delay(2000);   
  roboclaw.ForwardM1(address,0); //stop   
  roboclaw.BackwardM2(address,0); //stop   
  delay(2000); 
   //Using Mixed commands   
  roboclaw.ForwardMixed(address, 127);  //full speed forward   
  roboclaw.TurnRightMixed(address, 0);  //no turn   delay(2000);   
  roboclaw.TurnRightMixed(address, 64);  //half speed turn right   
  delay(2000);   
  roboclaw.TurnLeftMixed(address, 64);  //half speed turn left   
  delay(2000); 
  roboclaw.TurnLeftMixed(address, 0);  //stop turn   
  roboclaw.BackwardMixed(address, 127);  //half speed backward   
  delay(2000);   
  roboclaw.TurnRightMixed(address, 64);  //half speed turn right   
  delay(2000);   
  roboclaw.TurnLeftMixed(address, 64);  //half speed turn left   
  delay(2000);      
  roboclaw.ForwardMixed(address, 0);    //stop going backward   
  roboclaw.TurnRightMixed(address, 64);  //half speed right turn   
  delay(2000);   
  roboclaw.TurnLeftMixed(address, 64);  //half speed left turn   
  delay(2000);   
  roboclaw.TurnRightMixed(address, 0);  //stop turn(full stop)   
  delay(2000); 
  }
