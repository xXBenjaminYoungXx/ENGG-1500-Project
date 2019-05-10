#include <Esplora.h>

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
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void setup() {
    //sonar pins
    servo.attach(SERVO); // Sonar motor
    pinMode(ECHO,INPUT); //set pin 12 as an input
    pinMode(TRIG,OUTPUT); //set pin 7 as an output
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
    followLine();
}
