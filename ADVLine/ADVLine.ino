/* Benjamin Young Task 2: Right turn obsticle
 *  Method list:
 *    -turnRight
 *      Once the bot detects a right turn, it will reverse and turn right ~60 degrees, will resume to fo.low line after
 *      Assumption: When the robot turns, the sensors will be over a white surface.
 *    -turnLeft
 *      Same as turn right except left... who would have guessed
 *   
 *   What i think may work:
 *    -Inorder for the robot to distinguish between distraction lines and right turns, we may use the rumble strip or have the analogue input of a sensor to identify.
 *      -Line value: As distraction lines and rumble strip lines are thin, the analog value doesnt exceed ~150. For the right turn value it can reach values of ~450
 *        This can be used to distinguish between distraction lines and rumble strips to actual paths. It also doesnt require as much conding
 *        DISADVANTAGES: The ardwino can easily mistake a fork in the road as a left/right turn. Solutions to this may include, and are not limited to:
 *          -Having it recognise a turn if and only if opposite sensor also does not detect a line. This may bu an unreliable solution, however it is simple in nature.
 *        Another huge issdue is that once the robot fined the line after the turn, the sensor values will go above 450 once more, hence a static variable condition must also be added.
 *      
 *      -Rumble strip(I Prefer this one out of the two): This method may be chalenging and flawed, but if executed correctly it will be reliable. Let the left most sensore be w1, and right most sensor be w4.
 *         The diffrence between distraction lines and rumble strips is that rumble strins have lines evenly on both sides, while distraction lines do not. 
 *        If we set up the following: w1 + w4 = wsum, we can use this to identify the presence of lines on both ends of the main line. As the sensor value of a thin distraction and rumble strip line
 *        doesnt exceed ~150, we can set up the following:
 *            if(wsum>~280&&w1<200&&w2<200){
 *              //We are going over a rumble strip
 *            }
 *           I have added w1<200 and w2<200 such that if a thick line is detected on one sensor, the progrem doesnt mistake that as a rumbl strip.
 *          The issue with this however road forks may be considered a rumble strip, giving false information, and it can be quite un-reliable
 *          Solutions to this may be:
 *            Have it detect forks as rumble strips But set up a static vatriable that increments by one every time this is detected, which then after 
 *            a particular value, sets the robot to look for a right turn. This will make the code more reliable, however there are probably easier solutions
 *            
 *          In addition to this every loop of cede executed, while the both sensors detect black,  will cause this static variable to increment, multiple times for one dual line.
 *          Inorder to compensate for this we can have the added condition that the previous value detected white.
 *          
 *  Pseudo for line
 *  float w1
 *  float w4
 *  
 *  w1 is left ir sensor
 *  w2 if right ir sensor
 *  
 *  int State = 0;, identifies if a right hand turn should be detected
 *  
 *    if(w1 >450 && w4<450&&State == 0){if you see a thick line to left of you not right
 *      turnLeft();
 *      State = 1;
 *    }
 *    if(w1<450 && w4>450 &&State == 0){
 *      turnRight();
 *      State = 1;
 *    }
 *    
 *    turn left/right:
 *      delay 100
 *      reverse
 *      delay 100
 *      turn left/right
 *      move forward till you see line again
 *      return
 *     
 * Pseudo for other method.
 * Note: It is simialar to first method however it utilises the rumble strip to change state value
 * 
 *  float w1, w4, w1Prev, w4Prev, 
 *  int state = 0;
 *  if black is detected on both sides && w1/w2Prev<50(Ie was white)
 *    sate = state+1;
 *    w1Prev = w1
 *    w4Prev = w4
 *  
 *  if(State >= 4)//4 in this case as there are five rumble strip lines, and potentially a fork prior to turn. It can be above 4 as sensors can determine difrence between right turn and distraction line/rumble strip.
 *    if(w1 >450 && w4<450&&State == 0){if you see a thick line to left of you not right
 *      turnLeft();
 *      State = 1;
 *    }
 *    if(w1<450 && w4>450 &&State == 0){
 *      turnRight();
 *      State = 1;
 *    }
 *    
 *    turn left/right:
 *      delay 100
 *      reverse
 *      delay 100
 *      turn left/right
 *      move forward till you see line again
 *      return
 *    
 *  
 *          
 *            
 */

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
  //Serial.print("w1: ");
  //Serial.println(w1);
  // Serial.print("w2: ");
  // Serial.println(w2);
  // Serial.print("w3: ");
  // Serial.println(w3);
 /* 
  Serial.print("w4: ");
  Serial.println(w4);
  */ 
  if(lineDist<-0.6&&lineDist>-1.5){//left
    analogWrite(5, 40);
    analogWrite(6, 90);
    Serial.println("left");
  }else if(lineDist>0.6&&lineDist<1.5){
    analogWrite(5, 90);
    analogWrite(6, 40);
    Serial.println("Right");
  }else if(lineDist<-1.5&&lineDist>-8){
    analogWrite(5, 30);
    analogWrite(6, 100);
    Serial.println("left");
  }else if(lineDist>1.5&&lineDist<8){
    analogWrite(5, 100);
    analogWrite(6, 30);
    Serial.println("Right");
  }else if(lineDist<-8&&lineDist>-10){
    analogWrite(5, 20);
    analogWrite(6, 110);
    Serial.println("left");
  }else if(lineDist>8&&lineDist<10){
    analogWrite(5, 110);
    analogWrite(6, 20);
    Serial.println("Right");
  } /*else if(lineDist>10){
    analogWrite(5, 200);
    analogWrite(6, 0);
    Serial.println("Right");
  }else if(lineDist<-10){
    analogWrite(5, 0);
    analogWrite(6, 200);
    Serial.println("left");
  }
  */else{
    analogWrite(5, 90);
    analogWrite(6, 90);
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
  delay(500);
  leftBackwards();
  rightBackwards();
  analogWrite(5, 100);
  analogWrite(6, 100);
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
  delay(500);
  leftBackwards();
  rightBackwards();
  analogWrite(5, 100);
  analogWrite(6, 100);
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
