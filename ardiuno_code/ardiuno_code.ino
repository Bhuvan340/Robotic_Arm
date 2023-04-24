#include <Servo.h> 
#include <math.h>   
#define PI 3.141
Servo baseServo;  
Servo shoulderServo;  
Servo elbowServo; 
Servo gripperServo;

int command;

struct jointAngle{
  int base;
  int shoulder;
  int elbow;
};

int desiredGrip;
int gripperPos;

int desiredDelay;

int servoSpeed = 15;
int ready = 0;

struct jointAngle desiredAngle; 

//+++++++++++++++FUNCTION DECLARATIONS+++++++++++++++++++++++++++

int servoParallelControl (int thePos, Servo theServo );
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void setup()
{ 
  Serial.begin(9600);
  baseServo.attach(9);        
  shoulderServo.attach(10);
  elbowServo.attach(11);
  gripperServo.attach(6);
  
  Serial.setTimeout(50);      
  Serial.println("started");
  baseServo.write(90);        
  shoulderServo.write(150);
  elbowServo.write(110);
  ready = 0;
} 


void loop() 
{ 
  if (Serial.available()){
    ready = 1;
    desiredAngle.base = Serial.parseInt();
    desiredAngle.shoulder = Serial.parseInt();
    desiredAngle.elbow = Serial.parseInt();
    desiredGrip = Serial.parseInt();
    desiredDelay = Serial.parseInt();

    if(Serial.read() == '\n'){              

        Serial.flush();                    
 
        Serial.print('d');      
    }
  }
  
  int status1 = 0;
  int status2 = 0;
  int status3 = 0;
  int status4 = 0;
  int done = 0 ; 
  
  while(done == 0 && ready == 1){  
    
    status1 = servoParallelControl(desiredAngle.base, baseServo, desiredDelay);
    status2 = servoParallelControl(desiredAngle.shoulder,  shoulderServo, desiredDelay);
    status3 = servoParallelControl(desiredAngle.elbow, elbowServo, desiredDelay);      
    status4 = servoParallelControl(desiredGrip, gripperServo, desiredDelay);  
    
    if (status1 == 1 & status2 == 1 & status3 == 1 & status4 == 1){
      done = 1;
      
    }
        
  }
  

  
  
}

//++++++++++++++++++++++++++++++FUNCTION DEFITNITIONS++++++++++++++++++++++++++++++++++++++++++

int servoParallelControl (int thePos, Servo theServo, int theSpeed ){
  
    int startPos = theServo.read();       
    int newPos = startPos;
   
    
    
    
    if (startPos < (thePos-5)){
          
       newPos = newPos + 1;
       theServo.write(newPos);
       delay(theSpeed);
       return 0;
           
    }
  
   else if (newPos > (thePos + 5)){
  
      newPos = newPos - 1;
      theServo.write(newPos);
      delay(theSpeed);
      return 0;
          
    }  
    
    else {
        return 1;
    }  
    
  
}
