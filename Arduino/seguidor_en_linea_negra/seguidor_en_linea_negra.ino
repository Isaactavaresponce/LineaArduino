#include <AFMotor.h>

#include <QTRSensors.h>

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);

int color_negro =0; //negro
int color_blanco =1; //blanco

int csc_i=0;
int csc_d=0;
int s_i=0;
int s_d=0;


int bco=500;
int izq_3=A10;
int centro_i=A11;
int centro_d=A12;
int der_6=A13;


int l3=0;
int l4=0;
int l5=0;
int l6=0;

int dl3=0;
int dl4=0;
int dl5=0;
int dl6=0;

void setup() {
  // put your setup code here, to run once:
  motor1.setSpeed(100);
  motor2.setSpeed(100);
  Serial.begin(9600);

pinMode(izq_3,INPUT);
pinMode(centro_i,INPUT);
pinMode(centro_d,INPUT);
pinMode(der_6,INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  motor1.run(FORWARD);
  motor2.run(BACKWARD);

  leerinfra();

}

void leerinfra(){
    // Lectura analogica de los senores Infrarrojos 

    l3=analogRead(izq_3);
    l4=analogRead(centro_i);
    l5=analogRead(centro_d);
    l6=analogRead(der_6);



if (l3<=bco){dl3=1;} else {dl3=0;}
    if (l4<=bco){dl4=1;} else {dl4=0;}
    if (l5<=bco){dl5=1;} else {dl5=0;}
    if (l6<=bco){dl6=1;} else {dl6=0;}



    Serial.print("S1  ");
    Serial.println(l3);
    Serial.print("S2  ");
    Serial.println(l4);
    Serial.print("S3  ");
    Serial.println(l5);
    Serial.print("S4  ");
    Serial.println(l6);
    Serial.print("S5  ");

if (l4<=500){
  csc_i=0;
}else{
  csc_i=1;
}

if (l5<=500){
  csc_d=0;
}else{
  csc_d=1;
}

if (l3<=500){
  s_i=0;
}else{
  s_i=1;
}

if (l6<=500){
  s_d=0;
}else{
  s_d=1;
}


if (csc_i==0 && csc_d==0 && s_i==1 && s_d==1){ //inicio 
  motor1.run(FORWARD);
  motor2.run(FORWARD);

}else{
   if (csc_i==0 && csc_d==0 && s_i==1 && s_d==0){ //inicio 
  motor1.setSpeed(0);
  motor2.run(FORWARD);
}else{
   if (csc_i==1 && csc_d==0 && s_i==0 && s_d==1){ //inicio 
  motor1.run(FORWARD);
  motor2.setSpeed(0);
   }

   }
delay(250);
}

}




  
        
     
    
