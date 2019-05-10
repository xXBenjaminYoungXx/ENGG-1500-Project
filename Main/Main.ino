
#include <SparkFun_APDS9960.h>

// Global Variables
SparkFun_APDS9960 apds = SparkFun_APDS9960();
uint8_t proximity_data = 0;

#include <ENGG1500Lib.h>
#define Left 5
#define Right 6

#include <Servo.h> //makes the sonar magic happen
#define SERVO A5
Servo servo;
int servoAngle = 0; //Servo intial position
int Approximation = 0;
int ApproximationConstant = 4;

//IR Distance values
float x1 = 31;
float x2 = 10;
float x3 = -10;
float x4 = -31;
//IR reading variables
float w1;
float w2;
float w3;
float w4;
//Right turn values
float w1Prev = 0;
float w4Prev = 0;

int standardSpd = 70;
int standardSpdLeft = 70;
int standardSpdRight = 70;
int speedDiff = 0;

float den;
float numer;


void setup() {
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//*****RGB SETUP********//
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

  // Initialize Serial port
  Serial.begin(9600);
  Serial.println();
  Serial.println(F("------------------------------------"));
  Serial.println(F("SparkFun APDS-9960 - ProximitySensor"));
  Serial.println(F("------------------------------------"));
  
  
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//***********SERVO SETUP**************//
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    servo.attach(SERVO);
     
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
    for (servoAngle = 0; servoAngle < 180; servoAngle ++){
      servo.write(servoAngle);
           
     
    }
    delay (2000);
    
    for (servoAngle = 180; servoAngle > 0; servoAngle --){
      servo.write(servoAngle);
           
      
    }
    delay (2000);
      
    //followLine();
}
