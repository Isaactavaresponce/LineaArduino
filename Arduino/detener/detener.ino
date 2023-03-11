#include <QTRSensors.h>

#include <AFMotor.h>

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);


boolean True;
    int incrementar(int &variable) {
    variable++;
    if ( variable > 1400 ) variable=0;
    return variable;
  }
    int decrementar(int &variable) {
    variable--;
    if ( variable < 0 ) variable=1400;
    return variable;
}


//puertos de conección de sensor infrarojo
    int izq_1=A8;
    int izq_2=A9;
    int izq_3=A10;
    int centro_i=A11;
    int centro_d=A12;
    int der_6=A13;
    int der_7=A14;
    int der_8=A15;

//valores de blanco y negro
    int bco=500;
    int digitalWrite_black= 900;
    int digitalWrite_white= 650;
//Variables donde se guardan las lecuturas analogas del sensor infrarojo
    int l1=0;
    int l2=0;
    int l3=0;
    int l4=0;
    int l5=0;
    int l6=0;
    int l7=0;
    int l8=0;
//Variables para valor digital de lectura del sensor infrarojo
    int dl1=0;
    int dl2=0;
    int dl3=0;
    int dl4=0;
    int dl5=0;
    int dl6=0;
    int dl7=0;
    int dl8=0;




void setup() {
  // put your setup code here, to run once:
  motor1.setSpeed(75);
  motor2.setSpeed(75);
  Serial.begin(9600);
  // put your setup code here, to run once:
    //inicia puertos digitales para sensores infrarojos 
    pinMode(izq_1,INPUT);
    pinMode(izq_2,INPUT);
    pinMode(izq_3,INPUT);
    pinMode(centro_i,INPUT);
    pinMode(centro_d,INPUT);
    pinMode(der_6,INPUT);
    pinMode(der_7,INPUT);
    pinMode(der_8,INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
   // put your main code here, to run repeatedly:
  leerinfra(); 
}


void leerinfra(){
    // Lectura analogica de los senores Infrarrojos 
    l1=analogRead(izq_1);
    l2=analogRead(izq_2);
    l3=analogRead(izq_3);
    l4=analogRead(centro_i);
    l5=analogRead(centro_d);
    l6=analogRead(der_6);
    l7=analogRead(der_7);
    l8=analogRead(der_8);
    
    //Conversion de datos analogos a Digitales  a 0 1  1=blanco 0=negro
      
    if (l1<=bco){dl1=1;} else {dl1=0;}
    if (l2<=bco){dl2=1;} else {dl2=0;}
    if (l3<=bco){dl3=1;} else {dl3=0;}
    if (l4<=bco){dl4=1;} else {dl4=0;}
    if (l5<=bco){dl5=1;} else {dl5=0;}
    if (l6<=bco){dl6=1;} else {dl6=0;}
    if (l7<=bco){dl7=1;} else {dl7=0;}
    if (l8<=bco){dl8=1;} else {dl8=0;}

    Serial.print("S1  ");
    Serial.println(l1);
    Serial.print("S2  ");
    Serial.println(l2);
    Serial.print("S3  ");
    Serial.println(l2);
    Serial.print("S4  ");
    Serial.println(l2);
    Serial.print("S5  ");
    Serial.println(l2);
    Serial.print("S6  ");
    Serial.println(l2);
    Serial.print("S7  ");
    Serial.println(l2);
    Serial.print("S8  ");

if (digitalWrite_white>=digitalWrite_black){
  Serial.println("robot avanza");
  motor1.setSpeed (75);
  motor2.setSpeed (75);
  motor1.run (FORWARD);
  motor2.run (BACKWARD);
  }
else
   if (digitalWrite_black<=digitalWrite_white){
    Serial.println("stop");
    motor1.run (RELEASE);
    motor1.setSpeed (0);
    motor2.run (RELEASE);
    motor2.setSpeed (0);
  }
  else
 
 delay(250);

  
 }
 
