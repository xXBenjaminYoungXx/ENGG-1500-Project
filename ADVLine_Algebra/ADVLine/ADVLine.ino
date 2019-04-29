float x1 = 31;
float x2 = 10;
float x3 = -10;
float x4 = -31;

float w1;
float w2;
float w3;
float w4;

float w1Prev;
float w4Prev;

float State1 = 0;

int standardSpd = 80;

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

     //THE BELOW SERIES OF IF STATEMENTS NEED TO BE ADJUSTED ACCORDINLY TO STANDARD SPEED (Which is 80. we need to decide what speed we will base it off)
     //THE CURRENT SPEEDS ARE JUST AN EXAMPLE
     //Example pseudo:
     /*
      * if distance is 0.5/-0.5,
      *     standard wheel speed will be adjusted by 10
      * else if distance is 1/-1
      *     standard wheel speed will be adjusted by 20
      * else if distance is 1.5/-1.5
      *     standard wheel speed will be adjusted by 30
      *     
      * Exmple code below:
      */
     //analogWrite(5, StandardSpd + 10);
     if(lineDist<-1&&lineDist>-2){//left
           analogWrite(5, 40);
           analogWrite(6, 90);
      }
      else if(lineDist>1&&lineDist<2){
           analogWrite(5, 90);
           analogWrite(6, 40);
      }
      else if(lineDist<-2&&lineDist>-3){
           analogWrite(5, 30);
           analogWrite(6, 100);
      }
      else if(lineDist>2&&lineDist<3){
           analogWrite(5, 100);
           analogWrite(6, 30);
      }
      else if(lineDist<-3&&lineDist>-4){
           analogWrite(5, 20);
           analogWrite(6, 110);
      }
      else if(lineDist>3&&lineDist<4){
           analogWrite(5, 110);
           analogWrite(6, 20);
      }
      else if(lineDist>4){
           analogWrite(5, 200);
           analogWrite(6, 0);
      }
      else if(lineDist<-4){
           analogWrite(5, 0);
           analogWrite(6, 200);
      }
    
      if(w1>150 && w2>150 && w1Prev<40 &&w4Prev < 40){//lines on both sides
           State1+=1;
           w1Prev = w1;
           w4Prev = w4;
      }
    
      if(State1 >=5){//We can change value depending on course. Sate >=5 means we passed rumble strip, and need to look for turn
           if(w1>450){
               turnLeft();
               State1 = 0;
           }
           if(w4 > 450){
               turnRight();
               State1 = 0;
           }
      }
      else{
           analogWrite(5, 60);
           analogWrite(6, 60);
      }
      
}
void turnRight(void){
     //Stop
     analogWrite(5, 0);
     analogWrite(6, 0);
     delay(100);
     
     //Reverse
     leftBackwards();
     rightBackwards();
     analogWrite(5, 100);
     analogWrite(6, 100);
     delay(100);

     //Stop
     analogWrite(5, 0);
     analogWrite(6, 0);
     delay(100);

     //Turn
     leftForwards();
     rightBackwards();
     analogWrite(5, 100);//Can use pcb here insted
     analogWrite(6, 100);
     delay(200);

     //Stop
     analogWrite(5, 0);
     analogWrite(6, 0);
     delay(100);

     //Forward
     rightForwards();

     //While on white surface
     while(w2<100 && w3<100){//while line cant be seen
     }

     //Resume standars speed
     analogWrite(5, standardSpd);//return to standard speed
     analogWrite(6, standardSpd);
     return;
}
void turnLeft(void){
     //Stop
     analogWrite(5, 0);
     analogWrite(6, 0);
     delay(100);
     
     //Reverse
     leftBackwards();
     rightBackwards();
     analogWrite(5, 100);
     analogWrite(6, 100);
     delay(100);

     //Stop
     analogWrite(5, 0);
     analogWrite(6, 0);
     delay(100);

     //Turn
     rightForwards();
     leftBackwards();
     analogWrite(5, 100);//Can use pcb here insted
     analogWrite(6, 100);
     delay(200);

     //Stop
     analogWrite(5, 0);
     analogWrite(6, 0);
     delay(100);

     //Forward
     leftForwards();

     //While on white surface
     while(w2<100 && w3<100){//while line cant be seen
     }

     //Resume standars speed
     analogWrite(5, standardSpd);//return to standard speed
     analogWrite(6, standardSpd);
     return;
}

void leftBackwards(void) 
{
    digitalWrite(8,LOW); //IN1
    digitalWrite(9,HIGH); //IN2
}
void leftForwards(void) 
{
    digitalWrite(8,HIGH); //IN1
    digitalWrite(9,LOW); //IN2
}
void rightBackwards(void) 
{
    digitalWrite(10,LOW); //IN3
    digitalWrite(11,HIGH); //IN4
}
void rightForwards(void) 
{
    digitalWrite(10,HIGH); //IN3
    digitalWrite(11,LOW); //IN4
}
