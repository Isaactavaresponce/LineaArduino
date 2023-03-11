#include <QTRSensors.h>

#include <AFMotor.h>

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);




int color_negro =0; //negro
int color_blanco =1; //blanco

int s_izq=0;
int s_iz=0;
int s_i=0;
int csc_i=0;
int csc_d=0;
int s_d=0;
int s_de=0;
int s_der=0;

    int izq_1=A8;
    int izq_2=A9;
    int izq_3=A10;
    int centro_i=A11;
    int centro_d=A12;
    int der_6=A13;
    int der_7=A14;
    int der_8=A15;

    int bco=500;//600

    int l1=0;
    int l2=0;
    int l3=0;
    int l4=0;
    int l5=0;
    int l6=0;
    int l7=0;
    int l8=0;

    int dl1=0;
    int dl2=0;
    int dl3=0;
    int dl4=0;
    int dl5=0;
    int dl6=0;
    int dl7=0;
    int dl8=0;

void setup() {

  
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
 motor1.run(FORWARD);
  motor2.run(BACKWARD);
  
  leerinfra(); 
}


void leerinfra(){

    l1=analogRead(izq_1);
    l2=analogRead(izq_2);
    l3=analogRead(izq_3);
    l4=analogRead(centro_i);
    l5=analogRead(centro_d);
    l6=analogRead(der_6);
    l7=analogRead(der_7);
    l8=analogRead(der_8);
    
    
      
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
    Serial.println(l3);
    Serial.print("S4  ");
    Serial.println(l4);
    Serial.print("S5  ");
    Serial.println(l5);
    Serial.print("S6  ");
    Serial.println(l6);
    Serial.print("S7  ");
    Serial.println(l7);
    Serial.print("S8  ");
    Serial.println(l8);

if (l1>=810){
  s_izq=0;
}else{
  s_izq=1;
}
    
if (l2>=810){
  s_iz=0;
}else{
  s_iz=1;
}
   
if (l3>=810){
  s_i=0;
}else{
  s_i=1;
}

if (l4>=810){
  csc_i=0;
}else{
  csc_i=1;
}

if (l5>=810){
  csc_d=0;
}else{
  csc_d=1;
}

if (l6>=810){
  s_d=0;
}else{
  s_d=1;
}

if (l7>=810){
  s_de=0;
}else{
  s_de=1;
}

if (l8>=810){
  s_der=0;
}else{
  s_der=1;
}

   

if (csc_i==0 && csc_d== 0 && s_i== 1 && s_d ==1){  //adelante  // blanco 1
  motor1.setSpeed(70);
  motor2.setSpeed(90);
}
else
   if (csc_i==1 && csc_d==0 && s_i==1 && s_d==0){ //derecha 0
  motor1.setSpeed(70);
   motor2.setSpeed(0);  
}
else
   if (csc_i==1 && csc_d==1 && s_i==1 && s_d==0){ //derecha 1
  motor1.setSpeed(90);
   motor2.setSpeed(0);
}
else
   if (s_der==1 && s_de==1 && s_d==0 && csc_d==0 && csc_i==0 && s_i==1 && s_iz== 1 && s_izq==1){ //derecha 1
  motor1.setSpeed(90);
   motor2.setSpeed(0);
}


else
   if (csc_i==1 && csc_d==1 && s_i==0 && s_d==1){ //izquierda 1
   motor1.setSpeed(0);
   motor2.setSpeed(110);
}
else
   if (csc_i==0 && csc_d==1 && s_i==0&& s_d==1){ // izquierda 0
  motor2.setSpeed(90);
  motor1.setSpeed(0);
}



else
   if (s_der==1 && s_de==1 && s_d==1 && csc_d==0 && csc_i==0 && s_i==0 && s_iz== 1 && s_izq==1){ // izquierda 02
  motor2.setSpeed(90);
  motor1.setSpeed(0);
}

//else
 //  if (csc_i==0 && csc_d==0 && s_i==0 && s_d==0){ //adelante
  //motor1.setSpeed(80);
  //motor2.setSpeed(100);
   //}
  
// 90 GRados

else
   if (s_de==1 && s_d==0 && csc_d==0 && csc_i==0 && s_i==0 && s_iz== 0){         //derecha 2 // 2 (s_i==1 && s_d==1 && s_de==1 && s_iz==0)
     motor2.setSpeed(90);  // 100
     motor1.setSpeed(70); // 80
   motor1.run(BACKWARD); 
   delay (100);
   }
else
   if (s_de==1 && s_d==1 && csc_d==0 && csc_i==0 && s_i==0 && s_iz== 0){         //derecha 2 // 2 (s_i==1 && s_d==1 && s_de==1 && s_iz==0)
     motor2.setSpeed(90);  // 100
     motor1.setSpeed(70); // 80
   motor1.run(BACKWARD); 
   delay (100);
   }
else
   if (s_der==1 && s_de==1 && s_d==0 && csc_d==0 && csc_i==0 && s_i==0 && s_iz== 0){         //derecha 2 // 2 (s_i==1 && s_d==1 && s_de==1 && s_iz==0)
     motor2.setSpeed(90);  // 100
     motor1.setSpeed(70); // 80
   motor1.run(BACKWARD); 
   delay (100);
   }
else
   if (s_der==1 && s_de==0 && s_d==0 && csc_d==0 && csc_i==0 && s_i==0 && s_iz== 0 && s_izq==0 ){         //derecha 2 // 2 (s_i==1 && s_d==1 && s_de==1 && s_iz==0)
     motor2.setSpeed(90);  // 100
     motor1.setSpeed(70); // 80
   motor1.run(BACKWARD); 
   delay (100);
   }
else
   if (s_der==1 && s_de==1 && s_d==0 && csc_d==0 && csc_i==0 && s_i==0 && s_iz== 0 && s_izq==0 ){         //derecha 2 // 2 (s_i==1 && s_d==1 && s_de==1 && s_iz==0)
     motor2.setSpeed(90);  // 100
     motor1.setSpeed(70); // 80
   motor1.run(BACKWARD); 
   delay (100);
   }
else
   if (s_der==1 && s_de==1 && s_d==0 && csc_d==0 && csc_i==0 && s_i==0 && s_iz== 0 && s_izq==0 ){         //derecha 2 // 2 (s_i==1 && s_d==1 && s_de==1 && s_iz==0)
     motor2.setSpeed(90);  // 100
     motor1.setSpeed(70); // 80
   motor1.run(BACKWARD); 
   delay (100);
   }
else
   if (s_der==1 && s_de==1 && s_d==1 && csc_d==0 && csc_i==0 && s_i==0 && s_iz== 0 && s_izq==0 ){         //derecha 2 // 2 (s_i==1 && s_d==1 && s_de==1 && s_iz==0)
     motor2.setSpeed(90);  // 100
     motor1.setSpeed(70); // 80
   motor1.run(BACKWARD); 
   delay (100);
   }





else
   if(s_iz==1 && s_i==0 && csc_i==0 && csc_d==0 && s_d==0 && s_de==0 ) {               //izquierda 2 // 2
    motor2.setSpeed(90); 
   motor1.setSpeed(70); 
    motor2.run(FORWARD);
    delay (100);
   }
else
   if(s_iz==1 && s_i==1 && csc_i==0 && csc_d==0 && s_d==0 && s_de==0 ) {               //izquierda 2 // 2
    motor2.setSpeed(90); 
   motor1.setSpeed(70); 
    motor2.run(FORWARD);
    delay (100);
   }
else
   if(s_izq==1 && s_iz==1 && s_i==0 && csc_i==0 && csc_d==0 && s_d==0 && s_de==0 ) {               //izquierda 2 // 2
    motor2.setSpeed(90); 
   motor1.setSpeed(70); 
    motor2.run(FORWARD);
    delay (100);
   }
else
   if(s_izq==1 && s_iz==0 && s_i==0 && csc_i==0 && csc_d==0 && s_d==0 && s_de==0 && s_der==0 ) {               //izquierda 2 // 2
    motor2.setSpeed(90); 
   motor1.setSpeed(70); 
    motor2.run(FORWARD);
    delay (100);
   }
else
   if(s_izq==1 && s_iz==1 && s_i==0 && csc_i==0 && csc_d==0 && s_d==0 && s_de==0 && s_der==0 ) {               //izquierda 2 // 2
    motor2.setSpeed(90); 
   motor1.setSpeed(70); 
    motor2.run(FORWARD);
    delay (100);
   }
else
   if(s_izq==1 && s_iz==1 && s_i==0 && csc_i==0 && csc_d==0 && s_d==0 && s_de==0 && s_der==0 ) {               //izquierda 2 // 2
    motor2.setSpeed(90); 
   motor1.setSpeed(70); 
    motor2.run(FORWARD);
    delay (100);
   }
else
   if(s_izq==1 && s_iz==1 && s_i==1 && csc_i==0 && csc_d==0 && s_d==0 && s_de==0 && s_der==0 ) {               //izquierda 2 // 2
    motor2.setSpeed(90); 
   motor1.setSpeed(70); 
    motor2.run(FORWARD);
    delay (100);
   }
   
else
   if(s_izq==0 && s_iz==0 && s_i==0 && csc_i==0 && csc_d==0 && s_d==0 && s_de==0 && s_der==0 ) {               //izquierda 2 // 2
    
    motor1.run(BACKWARD);
    motor2.run(FORWARD);
    
   }




   
//   else
 //  if (csc_i==1 && csc_d==1 && s_i==1 && s_d==1){ //blanco detener
//  motor1.setSpeed(0);
//  motor2.setSpeed(0);
  // }

delay(10);
}