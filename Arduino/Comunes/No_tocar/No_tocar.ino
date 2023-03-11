#include <QTRSensors.h>
#include <Servo.h>

Servo mid;
Servo mit;
Servo mdd;
Servo mdt;


//Variables de configuracion 
int serial=1;   // 1: escribe al serial 0: NO escribe al erial  

const int pmdd=43;//43
const int pmdt=45;//45
const int pmid=49;
const int pmit=47;
boolean bucle=true;

int color_negro = 0; //negro
int color_blanco = 1; //blanco

int s_izq = 0;
int s_iz = 0;
int s_i = 0;
int csc_i = 0;
int csc_d = 0;
int s_d = 0;
int s_de = 0;
int s_der = 0;

int izq_1 = A8;
int izq_2 = A9;
int izq_3 = A10;
int centro_i = A11;
int centro_d = A12;
int der_6 = A13;
int der_7 = A14;
int der_8 = A15;

int bco = 10; //600

int l1 = 0;
int l2 = 0;
int l3 = 0;
int l4 = 0;
int l5 = 0;
int l6 = 0;
int l7 = 0;
int l8 = 0;

int dl1 = 0;
int dl2 = 0;
int dl3 = 0;
int dl4 = 0;
int dl5 = 0;
int dl6 = 0;
int dl7 = 0;
int dl8 = 0;

int os =330;
int rd = 2750;

 int pinEcho = 6;
int pinTrig = 4;
int distance = 18;

const int ledPin= 2;
const int ledPin1= 3;





void setup() {
  
   pinMode(ledPin, OUTPUT);
   pinMode(ledPin1, OUTPUT);



  mid.attach(pmid);
  mit.attach(pmit);
  mdd.attach(pmdd);
  mdt.attach(pmdt);

  pinMode(izq_1, INPUT);
  pinMode(izq_2, INPUT);
  pinMode(izq_3, INPUT);
  pinMode(centro_i, INPUT);
  pinMode(centro_d, INPUT);
  pinMode(der_6, INPUT);
  pinMode(der_7, INPUT);
  pinMode(der_8, INPUT);

  pinMode(pinTrig, OUTPUT);
  pinMode(pinEcho, INPUT);
  digitalWrite(ledPin,HIGH);
  digitalWrite(ledPin1,HIGH);
  Serial.begin(9600);
  
}

void detenerse(){
  int i1 = 90;  
  int i2 = 90;
  int d1 = 90;   
  int d2 = 90;   
  mid.write(i1);
  mit.write(i2);
  mdd.write(d1);
  mdt.write(d2); 
  delay(100);
}

void moverse(){
  int i1 = 0;  
  int i2 = 180;
  int d1 = 180;   
  int d2 = 0;   
  mid.write(i1);
  mit.write(i2);
  mdd.write(d1);
  mdt.write(d2); 
  delay(100);
}
void derecha(){
  int i1 = 0;  
  int i2 = 180;
  int d1 = 90;   
  int d2 = 90;   
  mid.write(i1);
  mit.write(i2);
  mdd.write(d1);
  mdt.write(d2); 
  delay(100);
}

void izquierda(){
  int i1 = 90;  
  int i2 = 90;
  int d1 = 180;   
  int d2 = 0;   
  mid.write(i1);
  mit.write(i2);
  mdd.write(d1);
  mdt.write(d2); 
  delay(100);

}
void derecha_90() {
  int i1 = 0;  
  int i2 = 180;
  int d1 = 0;   
  int d2 = 180;   
  mid.write(i1);
  mit.write(i2);
  mdd.write(d1);
  mdt.write(d2); 
  delay(100);

}

void izquierda_90() {
  int i1 = 180;  
  int i2 = 0;
  int d1 = 180;   
  int d2 = 0;   
  mid.write(i1);
  mit.write(i2);
  mdd.write(d1);
  mdt.write(d2); 
  delay(100);
}

void loop() {
  //ultra();
  leerinfra();
  serial=1;
  direccion();
}

//lectura de sensor infrarojo 
void leerinfra() {

  // lecturas analogas del senssor 
  l1 = analogRead(izq_1);
  l2 = analogRead(izq_2);
  l3 = analogRead(izq_3);
  l4 = analogRead(centro_i);
  l5 = analogRead(centro_d);
  l6 = analogRead(der_6);
  l7 = analogRead(der_7);
  l8 = analogRead(der_8);

  // verificar para eliminar 

  /*
  if (l1 <= bco) {
    dl1 = 1;
  } else {
    dl1 = 0;
  }
  if (l2 <= bco) {
    dl2 = 1;
  } else {
    dl2 = 0;
  }
  if (l3 <= bco) {
    dl3 = 1;
  } else {
    dl3 = 0;
  }
  if (l4 <= bco) {
    dl4 = 1;
  } else {
    dl4 = 0;
  }
  if (l5 <= bco) {
    dl5 = 1;
  } else {
    dl5 = 0;
  }
  if (l6 <= 630) {
    dl6 = 1;
  } else {
    dl6 = 0;
  }
  if (l7 <= 630) {
    dl7 = 1;
  } else {
    dl7 = 0;
  }
  if (l8 <= 630) {
    dl8 = 1;
  } else {
    dl8 = 0;
  }*/

  

  if (l1 >= os) {
    s_izq = 0;
  } else {
    s_izq = 1;
  }

  if (l2 >= os) {
    s_iz = 0;
  } else {
    s_iz = 1;
  }

  if (l3 >= os) {
    s_i = 0;
  } else {
    s_i = 1;
  }

  if (l4 >= os) {
    csc_i = 0;
  } else {
    csc_i = 1;
  }

  if (l5 >= os) {
    csc_d = 0;
  } else {
    csc_d = 1;
  }

  if (l6 >= os) {
    s_d = 0;
  } else {
    s_d = 1;
  }

  if (l7 >= os) {
    s_de = 0;
  } else {
    s_de = 1;
  }

  if (l8 >= os) {
    s_der = 0;
  } else {
    s_der = 1;
  }

  
  if (serial==1){
    Serial.print("S1  ");
    Serial.println(s_izq);
    Serial.print("S2  ");
    Serial.println(s_iz);
    Serial.print("S3  ");
    Serial.println(s_i);
    Serial.print("S4  ");
    Serial.println(csc_i);
    Serial.print("S5  ");
    Serial.println(csc_d);
    Serial.print("S6  ");
    Serial.println(s_d);
    Serial.print("S7  ");
    Serial.println(s_de);
    Serial.print("S8  ");
    Serial.println(s_der);
  }

}

void direccion(){
  //  s_izq  i_iz s_i csc_i  csc_d  s_d  s_de  s_der
  // --BNNB--
  if ( s_izq == 1 && csc_i == 0 && csc_d == 0 && s_d == 1 ) { //adelante  // bla.nco 1
      moverse();
  } else 
       //--bbnn--
       if ( s_i == 1 && csc_i == 1 && csc_d == 0 && s_d == 0 && s_de == 1 ) { //derecha 0
         derecha();
      } else 
           //--bbbnn-
           if ( s_i == 1 && csc_i == 1 && csc_d == 1 && s_d == 0 && s_de == 0 ) { //derecha 1
              derecha();
           } else 
                //--nnbb--
                if ( s_i == 0 && csc_i == 0 && csc_d == 1 && s_d == 1) { //derecha 3
                   izquierda();
                } else 
                     //-nnbbb--
                     if ( s_iz == 0 && s_i == 0 && csc_i == 1 && csc_d == 1 && s_d == 1) { // izquierda 0
                        izquierda();
                     } else 
                          //nnbbbb--
                          if (s_izq == 0 && s_iz == 0  && s_i == 1 && csc_i == 1 && csc_d == 1 && s_d == 1 ) { //izquierda 1
                              izquierda();
                          } 
}


void ultra(){
  digitalWrite(pinTrig, LOW);
  delayMicroseconds(100);
  digitalWrite(pinTrig, HIGH);
  delayMicroseconds(100);
  long pulseDuration = pulseIn(pinEcho, HIGH, 10000);
//  Serial.println(pulseDuration);
  
  // Una vez recibida la señal, se calculará la distancia en función de la velocidad
  //  del sonido 340 m/s
  int distance = (int)(0.034 * pulseDuration / 2);
  
 // Serial.println(distance);
 // Serial.print("test");

  if (distance > 10) {
    // Mostrar el resultado por el monitor serie
    Serial.print("Distancia ");
    Serial.println(distance);
    Serial.println(" cm");
  } else {
    Serial.println("Distancia desconocida");
  }
  delay(200);

/*

  if (distance<=10 && distance >1){
  delay(200);
  Serial.println("90");
  derecha_90();
  delay(1500);
  Serial.println("m0");
   moverse();
  delay(4500);
  Serial.println("90");
  izquierda_90();
  delay(3300);
  Serial.println("m0");
   moverse();
  delay(2500);
  while (bucle= true){
  if(l3>= 620 || l4 >= 620){
    Serial.println("d0");
   detenerse(); 
   delay(1999);
   bucle=false;
  }else{
    Serial.println("m0");
    moverse();
    }
   }
  }
  */
 }
