#include <ENGG1500Lib.h>
#define Left 5
#define Right 6
float x1 = 31;
float x2 = 10;
float x3 = -10;
float x4 = -31;

float w1;
float w2;
float w3;
float w4;

float w1Prev = 0;
float w4Prev = 0;

float State1 = 0;

int standardSpd = 80;
int standardSpdLeft = 70;
int standardSpdRight = 70;
int speedDiff = 0;

float den;
float numer;
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void setup() {
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
     
     leftForwards();
     rightForwards(); 
     
     w1 = analogRead(A0);
     w2 = analogRead(A1);
     w3 = analogRead(A2);
     w4 = analogRead(A3);
   
     numer=w1*x1+w2*x2+w3*x3+w4*x4;
     den=w1+w2+w3+w4;
     
     float lineDist = numer/den;

     Serial.println(lineDist);
     
    
     
     speedDiff = lineDist*8;
     if(lineDist>10||lineDist<-10){
      standardSpd = 50;
     }
     else if(lineDist>6||lineDist<-6){
      standardSpd = 60;
     }else{
      standardSpd = 80;
     }
     if(speedDiff<0){
          speedDiff = -speedDiff;
     }
     if(speedDiff>standardSpd){
          speedDiff = standardSpd;
     }
     
     if(lineDist>-0.5){//right
          analogWrite(5, standardSpd + speedDiff);
          analogWrite(6, standardSpd - speedDiff);
     }
     else if(lineDist<0.5){
          analogWrite(5, standardSpd - speedDiff);
          analogWrite(6, standardSpd + speedDiff);
     }
     else{
     
          analogWrite(5, standardSpd);
          analogWrite(6, standardSpd);
     }
      
     if((w1+w4)>75 && w1Prev<40 &&w4Prev < -2){//lines on both sides
          State1+=1;
     }
     w1Prev = w1;
     w4Prev = w4;
     if(State1 >=5){//We can change value depending on course. Sate >=5 means we passed rumble strip, and need to look for turn
          if(w1>450){
              turnLeft();
              State1 = -60;
          }
          else if(w4 > 450){
              turnRight();
              State1 = -60;
          }
     }       
}
