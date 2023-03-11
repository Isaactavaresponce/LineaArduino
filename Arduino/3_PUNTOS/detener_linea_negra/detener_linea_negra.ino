#include <AFMotor.h>
AF_DCMotor motor(1);
AF_DCMotor motor1(2);
int pasos=1;

void setup()
{
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor party!");
 
  motor.setSpeed(150);
  motor.run(RELEASE);
  motor1.setSpeed(150);
  motor1.run(RELEASE);
 
}

void loop()

{
  Serial.println(pasos);
  if (pasos<=4) {
      motor.run(FORWARD); //AVANSAR 1
      motor1.run(BACKWARD);
  }
  else
      if (pasos<=6){
           
            motor.run(FORWARD); // VUELTA IZQUIERDA 2
            motor1.run(FORWARD);
         
      }
      else
        if  (pasos<=9){    // 3
            motor.run(FORWARD);
            motor1.run(BACKWARD);
                 
      }
      else
        if  (pasos<=10){  // 4
             motor.setSpeed(100);
             motor1.setSpeed(100);
             motor.run(FORWARD);
             motor1.run(FORWARD);
     
                 
      }
      else
        if  (pasos<=13){  // 5
       
            motor.run(FORWARD);
            motor1.run(BACKWARD);
     
                 
      }
      else
        if  (pasos<=15){  // 6
           
            motor.run(BACKWARD); // VUELTA A LA DERECHA
            motor1.run(BACKWARD);
     
                 
      }
      else
        if  (pasos<=18){  
           
            motor.run(FORWARD);
            motor1.run(BACKWARD);
     
                 
      }
      else
        if  (pasos<=20){  
            motor.run(BACKWARD);
            motor1.run(BACKWARD);
     
                 
      }
      else
        if  (pasos<=23){  
           
            motor.run(FORWARD);
            motor1.run(BACKWARD);
     
                 
      }
      else
      if (pasos<=26){
           
            motor.run(FORWARD); // VUELTA IZQUIERDA
            motor1.run(FORWARD);  
           
         
      }
      else
        if  (pasos<=29){  
            motor.run(FORWARD);
            motor1.run(BACKWARD);
     
                 
      }
      else
      if (pasos<=32){
           
            motor.run(FORWARD); // VUELTA IZQUIERDA
            motor1.run(FORWARD);  
           
         
      }
      else
        if  (pasos<=42){  
            motor.run(FORWARD);
            motor1.run(BACKWARD);
     
                 
      }
      else
        if  (pasos<=47){  
            Serial.println("stop");
            motor.run(RELEASE);
            motor1.run(RELEASE);
     
                 
      }
     
     
  pasos=pasos+1;
  delay (250);
}
