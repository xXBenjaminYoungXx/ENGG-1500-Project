#include <SparkFun_APDS9960.h>
#include <ENGG1500Lib.h>
#define Left 5
#define Right 6

#include <Servo.h> //makes the sonar magic happen
#define SERVO A5
Servo servo;
int servoAngle = 0; //Servo intial position
unsigned int ProximityL = 100;
unsigned int ProximityF = 100;
unsigned int ProximityR = 100;
unsigned int ProximityFR = 100;
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
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void setup() {
    //servo pin
    servo.attach(SERVO); // Servo motor
    Serial.begin(9600);
     
     //IR sensors
     pinMode(A0, INPUT);//IR front
     pinMode(A1, INPUT);//IR front
     pinMode(A2, INPUT);//IR front
     pinMode(A3, INPUT);//IR front
     //Unknown
     pinMode(4, INPUT);//IR sensor right
     //Motor Speeds
     pinMode(5,OUTPUT); //set ENA as an output
     pinMode(6,OUTPUT); //set ENB as an output
     //Motor directions
     pinMode(8,OUTPUT); //set IN1 as an output
     pinMode(9,OUTPUT); //set IN2 as an output
     pinMode(10,OUTPUT); //set IN3 as an output
     pinMode(11,OUTPUT); //set IN4 as an output
     
     Serial.begin(115200);
     delay(5000);
}

void loop() {
     /*for(servoAngle = 0; servoAngle < 90; servoAngle++){  //move the micro servo from 0 degrees to 90 degrees
                                   
    servo.write(servoAngle);              
    switch (servoAngle) {
      case 0:                 //Reading at 0 degrees
        ProximityR = ;  //
        break;
      case 45:                //Reading at 90 degrees
        ProximityFR = ; //
        break;
      case 90:                //Reading at 90 degrees
        ProximityF = ;  //
        break;
      default:
        break;
    }
    
    if (ProximityF < 15 || ProximityFR < 15 || ProximityR < 15){
      servo.write(180);
      ProximityL = ;  //
      
      if (-(ApproximationConstant) < (ProximityL - ProximityR) && (ProximityL - ProximityR) < ApproximationConstant){   //This checks to see if Left and Right are approximately equal 
        Approximation = 1;
      }
        
      if (ProximityF < ProximityR || ProximityFR < ProximityR){              //If there is something in front but not to the right
        turnRight();
      }
      else if (2 * ProximityR < ProximityL|| 2 * ProximityFR < ProximityL){  //If there is something to the right but not in front
        turnLeft();
      }
      else if (Approximation == 1 && ProximityF < 3 * ProximityL){   //If there is nothing in front but there is stuff to the left and right at roughly equal distances
        //Corridor ();
        Approximation = 0;
      }
    }
    else {
      followLine();
    }
    delay(20);                  
  }

  for(servoAngle = 90; servoAngle > 0; servoAngle--){  //now move back the micro servo from 90 degrees to 0 degrees
                                    
      servo.write(servoAngle);          
      switch (servoAngle) {
        case 0: //Reading at 0 degrees
          ProximityR = ;  //
          break;
        case 45: //Reading at 45 degrees
          ProximityFR = ; //
          break;
        case 90: //Reading at 90 degrees
          ProximityF = ;  //
          break;
        default:
          break;
      }
      
      if (ProximityF < 15 || ProximityFR < 15 || ProximityR < 15){
        servo.write(180);
        ProximityL = ;  //
      
        if (-(ApproximationConstant) < (ProximityL - ProximityR) && (ProximityL - ProximityR) < ApproximationConstant){   //This checks to see if Left and Right are approximately equal 
          Approximation = 1;
        }
        
        if (ProximityF < ProximityR || ProximityFR < ProximityR){              //If there is something in front but not to the right
          turnRight();
        }
        else if (2 * ProximityR < ProximityL|| 2 * ProximityFR < ProximityL){  //If there is something to the right but not in front
          turnLeft();
        }
        else if (Approximation == 1 && ProximityF < 3 * ProximityL){   //If there is nothing in front but there is stuff to the left and right at roughly equal distances
          //Corridor ();
          Approximation = 0;
        }
      }
      else {
        followLine();
      }
      
      delay(20);      
  }*/
  followLine();
}
