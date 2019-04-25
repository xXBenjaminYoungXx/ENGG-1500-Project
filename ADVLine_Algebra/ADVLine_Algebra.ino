float x1 = 31;
float x2 = 10;
float x3 = -10;
float x4 = -31;

float w1;
float w2;
float w3;
float w4;

int standardSpd = 80;
float adjSpeed = 80;

float w1Prev;
float w4Prev;

float State1 = 0;

float den;
float numer;
void setup() {
  pinMode(A0, INPUT);//IR front
  pinMode(A1, INPUT);//IR front
  pinMode(A2, INPUT);//IR front
  pinMode(A3, INPUT);//IR front
  pinMode(4, INPUT);//IR sensor right
  pinMode(5,OUTPUT); //set ENA as an output
  pinMode(6,OUTPUT); //set ENB as an output
  pinMode(8,OUTPUT); //set IN1 as an output
  pinMode(9,OUTPUT); //set IN2 as an output
  pinMode(10,OUTPUT); //set IN3 as an output
  pinMode(11,OUTPUT); //set IN4 as an output
  Serial.begin(115200);
  delay(5000);
}

void loop() {
  // put your main code here, to run repeatedly:
  // TODO: Take sensor measurements using "w1 = analogRead(pin)" (store sensor
  leftForwards();
  rightForwards(); 
  w1 = analogRead(A0);
  w2 = analogRead(A1);
  w3 = analogRead(A2);
  w4 = analogRead(A3);
  //...data in w1, w2, w3, w4)
  // TODO: Calculate numerator of weighted average, store in num
  //w1x1+w2x2+...+wnxn
  numer=w1*x1+w2*x2+w3*x3+w4*x4;
  den=w1+w2+w3+w4;
  // TODO: Calculate denominator of weighted average, store in den
  float lineDist = numer/den;
  Serial.println(lineDist);
  
   
   if(lineDist<0.6){
    adjSpeed = standardSpd + lineDist*8;
    analogWrite(5, adjSpeed);
    adjSpeed = standardSpd - lineDist*8;
    analogWrite(6, adjSpeed);
   }
   else if(lineDist<-0.6){
      adjSpeed = standardSpd + lineDist*8;
      if(lineDist*8>70){
        adjSpeed = 70;
      }
      analogWrite(5, adjSpeed);
      adjSpeed = standardSpd - lineDist*8;
      analogWrite(6, adjSpeed);
   }
  else{
    analogWrite(5, standardSpd);
    analogWrite(6, standardSpd);
  }
  

  if(w1>150 && w2>150 && w1Prev<40 &&w4Prev < 40){//lines on both sides
    State1+=1;
    
  }
    w1Prev = w1;
    w4Prev = w4;
    
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
 
  
}
void turnRight(void){
  analogWrite(5, 0);
  analogWrite(6, 0);
  delay(2000);
  leftBackwards();
  rightBackwards();
  analogWrite(5, 100);
  analogWrite(6, 100);
  delay(500);
  analogWrite(5, 0);
  analogWrite(6, 0);
  delay(500);
  leftForwards();
  rightBackwards();
  analogWrite(5, 100);//Can use pcb here insted
  analogWrite(6, 100);
  delay(800);
  rightForwards();
  while(w2<100 && w3<100){
  }
  analogWrite(5, 60);//return to standard speed
  analogWrite(6, 60);
  return;
}
void turnLeft(void){
  analogWrite(5, 0);
  analogWrite(6, 0);
  delay(2000);
  leftBackwards();
  rightBackwards();
  analogWrite(5, 100);
  analogWrite(6, 100);
  delay(500);
  analogWrite(5, 0);
  analogWrite(6, 0);
  delay(500);
  rightForwards();
  leftBackwards();
  analogWrite(5, 100);//Can use pcb here insted
  analogWrite(6, 100);
  delay(800);
  leftForwards();
  while(w2<100 && w3<100){//while line cant be seen
  }
  analogWrite(5, 60);//return to standard speed
  analogWrite(6, 60);
  return;
}

void leftBackwards(void) //This function sets IN1 = LOW and IN2 = HIGH in order to
//... set the direction to forwards for motor 1
{
digitalWrite(8,LOW); //IN1
digitalWrite(9,HIGH); //IN2
}
void leftForwards(void) //This function sets IN1 = HIGH and IN2 = LOW in order
//...to set the direction to backwards for motor 1
{
digitalWrite(8,HIGH); //IN1
digitalWrite(9,LOW); //IN2
}
void rightBackwards(void) //This function sets IN3 = LOW and IN4 = HIGH in order
//...to set the direction to forwards for motor 2
{
digitalWrite(10,LOW); //IN3
digitalWrite(11,HIGH); //IN4
}
void rightForwards(void) //This function sets IN3 = HIGH and IN4 = LOW in order
//...to set the direction to forwards for motor 2
{
digitalWrite(10,HIGH); //IN3
digitalWrite(11,LOW); //IN4
}
