void turnLeft(void){
     analogWrite(5, 55 - 15);
     analogWrite(6, 55 + 15);
     delay(500);
     return;
}
void turnRight(void){
     analogWrite(5, 55 + 15);
     analogWrite(6, 55 - 15);
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

