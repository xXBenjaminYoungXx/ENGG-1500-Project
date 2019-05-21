void followLine(){
     leftForwards();
     rightForwards(); 

     // Serial.println(w1);
     // Serial.println(w2);
     // Serial.println(w3);
     // Serial.println(w4);

     //IR Distance values
     const int x1 = 31;
     const int x2 = 10;
     const int x3 = -10;
     const int x4 = -31;
    
     numer=w1*x1+w2*x2+w3*x3+w4*x4;
     den=w1+w2+w3+w4;
     
     float lineDist = numer/den;
     
     
     speedDiff = lineDist*8;

    /* if(w4 > 370){
        turnLeft();
     }
     else if(w1 > 370){
       turnRight();
     }*/
     if(lineDist>10||lineDist<-10){
      standardSpd = 50;
     }
     else if(lineDist>6||lineDist<-6){
      standardSpd = 60;
     }else{
      standardSpd = 70;
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
}
