//#include <Esplora.h>
#include <Wire.h>
#include <SparkFun_APDS9960.h>

// Global Variables
SparkFun_APDS9960 apds = SparkFun_APDS9960();
uint8_t proximity_data = 0;

#include <ENGG1500Lib.h>
#define Left 5
#define Right 6

#include <Servo.h> //makes the sonar magic happen
#define ECHO 12
#define TRIG 7
#define SERVO A5
Servo servo;
int servoAngle = 0; //Servo intial position
unsigned int SonarL = 100;
unsigned int SonarF = 100;
unsigned int SonarR = 100;
unsigned int SonarFR = 100;
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
//State 
float State1 = 0;

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
  Serial.begin(115200);
  Serial.println();
  Serial.println(F("------------------------------------"));
  Serial.println(F("SparkFun APDS-9960 - ProximitySensor"));
  Serial.println(F("------------------------------------"));
  
  // Initialize APDS-9960 (configure I2C and initial values)
  if ( apds.init() ) {
    Serial.println(F("APDS-9960 initialization complete"));
  } else {
    Serial.println(F("Something went wrong during APDS-9960 init!"));
  }
  
  // Adjust the Proximity sensor gain
  if ( !apds.setProximityGain(PGAIN_2X) ) {
    Serial.println(F("Something went wrong trying to set PGAIN"));
  }
  
  // Start running the APDS-9960 proximity sensor (no interrupts)
  if ( apds.enableProximitySensor(false) ) {
    Serial.println(F("Proximity sensor is now running"));
  } else {
    Serial.println(F("Something went wrong during sensor init!"));
  }
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//***********SERVO SETUP**************//
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

     
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
    if ( !apds.readProximity(proximity_data) ) {
    Serial.println("Error reading proximity value");
  } else {
    //Serial.print("Proximity: ");
    //Serial.println(proximity_data);
  }
    followLine();
}
