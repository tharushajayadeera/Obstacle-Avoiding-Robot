
#include <AFMotor.h> //import your motor shield library
#define trigPin 12 // define the pins of your sensor
#define echoPin 13 
AF_DCMotor motor1(1,MOTOR12_64KHZ); // set up motors.
AF_DCMotor motor2(2, MOTOR12_8KHZ);
int RED = 10;
int GREEN = 9;
 
void setup() {
  pinMode(RED,OUTPUT);
  pinMode(GREEN,OUTPUT);
  Serial.begin(9600); // begin serial communitication  
  Serial.println("Motor test!");
   pinMode(trigPin, OUTPUT);// set the trig pin to output (Send sound waves)
  pinMode(echoPin, INPUT);// set the echo pin to input (recieve sound waves)
  motor1.setSpeed(105); //set the speed of the motors, between 0-255
  motor2.setSpeed (105);  
}
 
void loop() {


  long duration, distance; // start the scan
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2); // delays are required for a succesful sensor operation.
  digitalWrite(trigPin, HIGH);

  delayMicroseconds(10); //this delay is required as well!
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;// convert the distance to centimeters.

  
  if (distance < 10)/*if there's an obstacle 25 centimers, ahead, do the following: */ { 
    digitalWrite(RED,HIGH);
    digitalWrite(GREEN,LOW);  
    goBack();
       
}else if(distance < 18 ){
    turnRight();
    turnRight();
  }else if(distance < 25){
    turnLeft();
    turnLeft();
    }else{
      
   digitalWrite(RED,LOW);
  digitalWrite(GREEN,HIGH);
   Serial.println ("No obstacle detected. going forward");
   delay (8);
   motor1.run(FORWARD); //if there's no obstacle ahead, Go Forward! 
    motor2.run(FORWARD);  
  }  
}

void turnLeft(){
    motor1.run(FORWARD);  
    motor2.run (BACKWARD);
  }
void turnRight(){
    motor2.run(FORWARD);  
    motor1.run (BACKWARD);
  }
void goBack(){
    motor2.run(BACKWARD);  
    motor1.run (BACKWARD);
  }

