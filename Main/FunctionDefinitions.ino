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
     return;
}
void turnRight(void){
     Stop();
     delay(1000);
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
    digitalWrite(11,LOW); //IN3
    digitalWrite(12,HIGH); //IN4
}
void rightForwards(void) 
{
    digitalWrite(11,HIGH); //IN3
    digitalWrite(12,LOW); //IN4
}
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
}
void Light (void){
  if (  !apds.readAmbientLight(ambient_light) || !apds.readRedLight(red_light) || !apds.readGreenLight(green_light) || !apds.readBlueLight(blue_light) ) {
      Serial.println("Error reading light values");
  }
  
  if(red_light >500){
      digitalWrite(5,LOW);
      digitalWrite(6,LOW);
    }
  else if(green_light > 500){
    delay (500);
    followLine();
  }
}
void Garage(void){
   Halt();
   servo.write(90);
   delay(185);
 
   analogWrite(5,70);
   analogWrite(6,70);

   if (!apds.readProximity(proximity_data)){
     Serial.println("Error reading proximity value");
   }
 
  if(proximity_data > 240)
  {
     Stop();
  }
}
void Corridor (void){
  analogWrite(5, LPWM);
  analogWrite(6, RPWM);
  ProxL = 30;
  ProxR = 30;
  delay (3000);
}
