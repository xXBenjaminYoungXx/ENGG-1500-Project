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

     //Resume standars speed
     analogWrite(5, standardSpd);//return to standard speed
     analogWrite(6, standardSpd);
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
unsigned int sonar_mm(void){
long duration = 0;
const float speed_sound = 340.29;
// m/s, "const" makes the compiler able to optimise the program where this variable is used, cool!
// Read in a distance from the ultrasonic distance sensor The ultrasonic burst is triggered by a HIGH pulse of 10 microseconds.
digitalWrite(TRIG, HIGH);
delayMicroseconds(10);
digitalWrite(TRIG, LOW);
//read length of time pulse
duration = pulseIn(ECHO, HIGH); 
// This function measures a pulsewidth and returns the width in microseconds convert the time into a distance
// the code "(unsigned int)" turns the result of the distance calculation into an integer instead of a floating point.
return (unsigned int)(0.5 * duration * 1e-6 * speed_sound * 1e3);
//"unsigned" ensures we are returning an unsigned number, remember that there is no such thing as negative distance.
}
