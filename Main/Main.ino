
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//***********Librarys**************//
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include <SparkFun_APDS9960.h>//RGB sensor
#include <ENGG1500Lib.h>//Encoder stuff
#include <Servo.h> //makes the sonar magic happen
#include <Wire.h>

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//***********Servo variables**************//
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define SERVO 10
Servo servo;
int servoAngle = 0; //Servo intial position
int Time;
uint8_t ProxF = 30;
uint8_t ProxL = 30;
uint8_t ProxR = 30;

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//***********RGB variables**************//
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

SparkFun_APDS9960 apds = SparkFun_APDS9960();
uint8_t proximity_data = 0;
uint16_t ambient_light = 0;
uint16_t red_light = 0;
uint16_t green_light = 0;
uint16_t blue_light = 0;

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//***********IR reading variables**************//
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

float w1;
float w2;
float w3;
float w4;

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//***********PWM Controll Variables**************//
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int standardSpd = 70;
int speedDiff = 0;
int State = 1;
float den;
float numer;
const int LPWM = 82;
const int RPWM = 85;

void setup() {
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//***********RGB SETUP**************//
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    Serial.begin(9600);
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

    // Start running the APDS-9960 light sensor (no interrupts)
    if ( apds.enableLightSensor(false) ) {
      Serial.println(F("Light sensor is now running"));
    } else {
      Serial.println(F("Something went wrong during light sensor init!"));
    }
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
    pinMode(11,OUTPUT); //set IN3 as an output
    pinMode(12,OUTPUT); //set IN4 as an output
    
    delay(5000);
}

void loop() {
  if ( !apds.readProximity(proximity_data) ) {
    Serial.println("Error reading proximity value");
  }
  
  if (State == 1){
      
      for (servoAngle = 0; servoAngle < 91; servoAngle ++){
        servo.write(servoAngle);
        
        switch (servoAngle) {
          case 0:                 //Reading at 0 degrees
            apds.readProximity(proximity_data);
            ProxR = proximity_data;            
            
                    Serial.print("1ProxL: ");
        Serial.println(ProxL);
        Serial.print("1ProxF: ");
        Serial.println(ProxF);
        Serial.print("1ProxR: ");
        Serial.println(ProxR);
            break;
          case 90:                //Reading at 90 degrees
            apds.readProximity(proximity_data);
            ProxF = proximity_data;
            
                    Serial.print("1ProxL: ");
        Serial.println(ProxL);
        Serial.print("1ProxF: ");
        Serial.println(ProxF);
        Serial.print("1ProxR: ");
        Serial.println(ProxR);
            break;
          default:
            break;
        }

      StateMachine();
        
      followLine();
      }

      
      for (Time = 0; Time < 185; Time ++){
        followLine();
        delay(1);
      }
    
      for (servoAngle = 90; servoAngle > -1; servoAngle --){
        servo.write(servoAngle);
        
        switch (servoAngle) {
            case 0:                 //Reading at 0 degrees
                apds.readProximity(proximity_data);                
                ProxR = proximity_data;


                        Serial.print("2ProxL: ");
        Serial.println(ProxL);
        Serial.print("2ProxF: ");
        Serial.println(ProxF);
        Serial.print("2ProxR: ");
        Serial.println(ProxR);
                break;
            case 90:                //Reading at 90 degrees
                apds.readProximity(proximity_data);
                ProxF = proximity_data;


                        Serial.print("2ProxL: ");
        Serial.println(ProxL);
        Serial.print("2ProxF: ");
        Serial.println(ProxF);
        Serial.print("2ProxR: ");
        Serial.println(ProxR);
                break;
          default:
              break;
        }
        StateMachine();
        followLine();
      }
            
      for (Time = 0; Time < 185; Time ++){
          followLine();
          delay(1);
      } 
  } 
}
