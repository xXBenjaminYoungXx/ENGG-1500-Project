#include <ENGG1500Lib.h>
void turnLeft(void){
     Halt();
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
     Halt();
     delay(1000);
     leftBackwards();
     rightBackwards();
     analogWrite(5, 90);
     analogWrite(6, 90);
     delay(210);
     leftForwards();
     rightBackwards();
     analogWrite(5, 170);
     analogWrite(6, 170);
     delay(210);
     leftForwards();
     rightForwards();
     analogWrite(5, 100);
     analogWrite(6, 100);
     delay(400);
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
   Serial.println("Garage");
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
  Serial.println("Corridor");
  ProxL = 30;
  ProxR = 30;
  Halt();
  servo.write(0);
  enc_clear();
  delay(500);
  apds.readProximity(proximity_data);
  while(proximity_data >80){
    if(enc_getLeft() < enc_getRight()){//More power needs to go to left
      analogWrite(5, 80 + 8*(enc_getRight()-enc_getLeft()));
      analogWrite(6, 80 - 8*(enc_getRight()-enc_getLeft()));
    }
    if(enc_getLeft() > enc_getRight()){
      analogWrite(5, 80 - 8*(enc_getLeft()-enc_getRight()));
      analogWrite(6, 80 + 8*(enc_getLeft()-enc_getRight()));
    }
    else{
      analogWrite(5, 80);
      analogWrite(6, 80);
    }
    apds.readProximity(proximity_data);
  }
  servo.write(90);
}
void StateMachineR (void){
        if (ProxR > 120){
              Halt();
              servo.write(90);
              delay (250);
              apds.readProximity(proximity_data);
              ProxF = proximity_data;
              Serial.print("ProxF: ");
              Serial.println(ProxF);
              delay (10);
              
              servo.write(180);
              delay (250);
              apds.readProximity(proximity_data);
              ProxL = proximity_data;
              Serial.print("ProxL: ");
              Serial.println(ProxL);
              delay (10);
              
              if (ProxL < 60 && ProxR > 240){
                Serial.println("WallR");
                turnLeft();
                ProxR = 30;
              }
              
              else if (ProxL > 60 && ProxF > 70){
                Serial.println("GarageR");
                Garage();
              }
              else if (ProxL > 60){
                Corridor();
              } 
            }     
}

void StateMachineF (void){
      if (ProxF > 140){
              Halt();
              servo.write(0);
              delay (380);
              apds.readProximity(proximity_data);
              ProxR = proximity_data;
              if (ProxR > 160){
                Serial.println("GarageF");
                Garage();
              }
              else {
                Serial.println("WallF");
                turnRight();
                ProxF = 30;
              }
      }     
}
