#include <SparkFun_APDS9960.h>
#include <ENGG1500Lib.h>
#include <Servo.h> //makes the sonar magic happen

#define SERVO A5
Servo servo;

// Global Variables
SparkFun_APDS9960 apds = SparkFun_APDS9960();
uint8_t proximity_data = 0;

//IR reading variables
float w1;
float w2;
float w3;
float w4;

int standardSpd = 70;
int speedDiff = 0;

float den;
float numer;


void setup() {

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//***********SERVO SETUP**************//
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    servo.attach(SERVO);
    int servoAngle = 0; //Servo intial position
    int Approximation = 0;
    int ApproximationConstant = 4;
     
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//***********IR SENSOR SETUP**************//
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    //IR sensors
    pinMode(A0, INPUT);//IR front
    pinMode(A1, INPUT);//IR front
    pinMode(A2, INPUT);//IR front
    pinMode(A3, INPUT);//IR front
     
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//***********MOTOR SETUP**************//
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
     
    //Motor Speeds
    pinMode(5,OUTPUT); //set ENA as an output
    pinMode(6,OUTPUT); //set ENB as an output
    //Motor directions
    pinMode(8,OUTPUT); //set IN1 as an output
    pinMode(9,OUTPUT); //set IN2 as an output
    pinMode(10,OUTPUT); //set IN3 as an output
    pinMode(11,OUTPUT); //set IN4 as an output
    
    delay(5000);
}

void loop() {
  
    /*for (servoAngle = 0; servoAngle < 180; servoAngle ++){
      servo.write(servoAngle);
           
     
    }
    
    for (servoAngle = 180; servoAngle > 0; servoAngle --){
      servo.write(servoAngle);
           
      
    }*/
    followLine();
}
