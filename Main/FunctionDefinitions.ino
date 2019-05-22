//-------------------------------
void turnLeft(void){
     Stop();
     delay(1000);
     leftBackwards();
     rightForwards();
     analogWrite(5, 170);
     analogWrite(6, 170);
     delay(200);
     leftForwards();
     rightForwards();
     analogWrite(5, 100);
     analogWrite(6, 100);
     delay(500);
}
void turnRight(void){
     Stop();
     delay(1000);
     leftBackwards();
     rightBackwards();
     analogWrite(5, 170);
     analogWrite(6, 170);
     delay(200);
     leftForwards();
     rightBackwards();
     analogWrite(5, 170);
     analogWrite(6, 170);
     delay(200);
     leftForwards();
     rightForwards();
     analogWrite(5, 100);
     analogWrite(6, 100);
     delay(500);
}
//-------------------------------
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
    digitalWrite(11,LOW); //IN3
    digitalWrite(12,HIGH); //IN4
}
void rightForwards(void) 
{
    digitalWrite(11,HIGH); //IN3
    digitalWrite(12,LOW); //IN4
}
//-------------------------------
void Halt(void) 
{
    analogWrite(5,0); //Left
    analogWrite(6,0); //Right
}
void Stop(void)
{
    analogWrite(5,0); //Left
    analogWrite(6,0); //Right
    State = 0;
    return;
}
//-------------------------------
void Light (void){
  Halt();
  if(green_light > 450){
    delay (500);
    State = 1;
  }
}
//-------------------------------
void wall(void){
  if((w1Prev > 300) && (itteration == 0)){
    turnLeft();
    itteration = 1;
    analogWrite(5,70);
    analogWrite(6,70);
  }
  if((w4Prev > 300) && (itteration == 0)){
    turnRight();
    itteration = 1;
    analogWrite(5,70);
    analogWrite(6,70);
  }
  analogWrite(5,70);
  analogWrite(6,70);
  delay(3500);


  if(w1 > 70 || w2 > 70 || w3 > 70 || w4 > 70){
      State = 1;
      itteration = 0;
  }
}
//-------------------------------
void Garage(void){
   Serial.println("Garage");
   Halt();
   servo.write(90);
 
   analogWrite(5,70);
   analogWrite(6,70);
 
   if(proximity_data > 240)
   {
     Stop();
   }
}
//-------------------------------
void Corridor (void){
  if(itteration == 0){
    enc_clear();
    itteration+=1;
  }
  Serial.println("Corridor");
  
  if(enc_getLeft() > enc_getRight()){
    analogWrite(5, LPWM - 2*(enc_getLeft()-enc_getRight()));
    analogWrite(6, RPWM + 2*(enc_getLeft()-enc_getRight()));
  }
  if(enc_getLeft() < enc_getRight()){
    analogWrite(5, LPWM + 2*(enc_getRight()-enc_getLeft()));
    analogWrite(6, RPWM - 2*(enc_getRight()-enc_getLeft()));
  }

  if(w1 > 70 || w2 > 70 || w3 > 70 || w4 > 70){
      State = 1;
      itteration = 0;
  }
}
//-------------------------------
