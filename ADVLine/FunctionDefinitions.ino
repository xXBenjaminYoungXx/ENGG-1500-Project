void turnLeft(void){
     //Stop
     analogWrite(5, 0);
     analogWrite(6, 0);
     delay(300);
     
     //Reverse
     leftBackwards();
     rightBackwards();
     analogWrite(5, 100);
     analogWrite(6, 100);
     delay(300);

     //Stop
     analogWrite(5, 0);
     analogWrite(6, 0);
     delay(300);

     //Turn
     leftForwards();
     rightBackwards();
     analogWrite(5, 100);//Can use pcb here insted
     analogWrite(6, 100);
     delay(200);

     //Stop
     analogWrite(5, 0);
     analogWrite(6, 0);
     delay(300);

     //Forward
     rightForwards();
     leftForwards();
     analogWrite(5, 100);
     delay(50);
     analogWrite(6, 100);

     //While on white surface
     while(w2<400 && w3<400){//while line cant be seen
     }

     //Resume standars speed
     analogWrite(5, standardSpdLeft);//return to standard speed
     analogWrite(6, standardSpdRight);
     return;
}
void turnRight(void){
     //Stop
     analogWrite(5, 0);
     analogWrite(6, 0);
     delay(300);
     
     //Reverse
     leftBackwards();
     rightBackwards();
     analogWrite(5, 100);
     analogWrite(6, 100);
     delay(200);

     //Stop
     analogWrite(5, 0);
     analogWrite(6, 0);
     delay(300);

     //Turn
     rightForwards();
     leftBackwards();
     analogWrite(5, 100);//Can use pcb here insted
     analogWrite(6, 100);
     delay(300);

     //Stop
     analogWrite(5, 0);
     analogWrite(6, 0);
     delay(300);

     //Forward
     leftForwards();
     rightForwards();

     analogWrite(6, 100);
     delay(50);
     analogWrite(5, 100);
     

     //While on white surface
     while(w2<400 && w3<400){//while line cant be seen
     }

     //Resume standars speed
     analogWrite(5, standardSpdLeft);//return to standard speed
     analogWrite(6, standardSpdRight);
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
