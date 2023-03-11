#include <SD.h>
#include <QTRSensors.h>
#include <AFMotor.h>
#include <Wire.h>
#include <Servo.h>

//RGB

//Variables de configuracion 
int serial=1;   // 1: escribe al serial 0: NO escribe al erial  

extern "C" {
  #include "utility/twi.h" // from Wire library, so we can do bus scanning
}
//                                                                                        #include <Adafruit_HMC5883_U.h>
#define TCAADDR 0x70
//------------------------- RGB
#include "Arduino.h"
#include "SparkFunISL29125.h"

// Global variables and defines
uint16_t RGB_sensorR1,RGB_sensorG1,RGB_sensorB1;
uint16_t RGB_sensorR2,RGB_sensorG2,RGB_sensorB2;
// object initialization

SFE_ISL29125 RGB_sensor1;
SFE_ISL29125 RGB_sensor2;

long time0;

 int Green1Max = 2450;
 int Green1Min = 2300;
 int GreenMax = 3400;
 int GreenMin = 3060;

void tcaselect(uint8_t i) {
    if (i > 7) return;
    
    Wire.beginTransmission(TCAADDR);
    
    Wire.write(1 << i);
    
    Wire.endTransmission();
}

//Servo
Servo mid;
Servo mit;
Servo mdd;
Servo mdt;

//lugar en donde se conectan los motores
const int pmdd=43;//43 motor delantero derecho 
const int pmdt=45;//45 motor trasero derecho
const int pmid=49;//49 motor delantero izquierdo
const int pmit=47;//47 motor trasero izquierdo

//infrarojo
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



//int bco = 500; //600

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


//calibracion de sensor infrarrojo

// 890 es la calibracion exacta en el salon de robotica 

int os =890;



//Ultrasonico

//conexiones para puertos del ultrasonico
int pinEcho = 6;
int pinTrig = 4;
int distance = 18;

//Leds y conexiones a puertos 
const int ledPin= 2;
const int ledPin1= 4;





void setup() {
// Servos
  mid.attach(pmid);
  mit.attach(pmit);
  mdd.attach(pmdd);
  mdt.attach(pmdt);
// Infrarojo
  pinMode(izq_1, INPUT);
  pinMode(izq_2, INPUT);
  pinMode(izq_3, INPUT);
  pinMode(centro_i, INPUT);
  pinMode(centro_d, INPUT);
  pinMode(der_6, INPUT);
  pinMode(der_7, INPUT);
  pinMode(der_8, INPUT);
// Ultra
  pinMode(pinTrig, OUTPUT);
  pinMode(pinEcho, INPUT);
// Leds
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin1, OUTPUT);
  digitalWrite(ledPin,HIGH);
  digitalWrite(ledPin1,HIGH);

  
//---------------RGB-----------
     //Puerto serial 
   Serial.println("entre setup");
   // Inicializa el 1er sensor RGB Izquierdo
    tcaselect(0);
    Serial.println("entre setup 1");
    if (RGB_sensor1.init())    //Iniciar 1° sensor RGB
       {
           Serial.println("Sensor 1 iniciado");
       }
    else 
       {
           Serial.println("Sensor 1 ERROR de iniciado");
       }
    
    // Inicializa el 2° sensor RGB Derecho
    tcaselect(1);
    if (RGB_sensor2.init())    //Iniciar 2° sensor RGB
       {
           Serial.println("Sensor 2 iniciado");
       }

     Serial.println("sali setup");
  

  Serial.begin(9600);
  
}

//Acciones

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
void derecha_45(){
  int i1 = 0;  
  int i2 = 180;
  int d1 = 45;   
  int d2 = 135;   
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

void izquierda_45(){
  int i1 = 180;  //135
  int i2 = 0; //0 45
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
  //leerinfra();
  serial=1;
  direccion();
  LeerRgb();
  RgbAcciones();
  moverse();
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
    Serial.print("S1 ");
    Serial.print(s_izq);
    Serial.print(" S2 ");
    Serial.print(s_iz);
    Serial.print(" S3 ");
    Serial.print(s_i);
    Serial.print(" S4 ");
    Serial.print(csc_i);
    Serial.print(" S5 ");
    Serial.print(csc_d);
    Serial.print(" S6 ");
    Serial.print(s_d);
    Serial.print(" S7 ");
    Serial.print(s_de);
    Serial.print(" S8 ");
    Serial.print(s_der);
    Serial.println("\t");
  }

}

void direccion(){
  //  s_izq  i_iz s_i csc_i  csc_d  s_d  s_de  s_der
  // --BNNB--
  if ( s_i == 1 && csc_i == 0 && csc_d == 0 && s_d == 1 ) { //adelante  // bla.nco 1
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
                          if (s_izq == 0 && s_iz == 0  && s_i == 1 && csc_i == 1 && csc_d == 1 && s_d == 1) { //izquierda 1
                              izquierda();
                          } else
                               //bbbnnnnn
                               if (s_izq == 1 && s_iz == 1  && s_i == 1 && csc_i == 0 && csc_d == 0 && s_d == 0 && s_de == 0 && s_der == 0){
                                   Serial.println(" d45");
                                   derecha_45();
                               } else
                                   //nnnnnbbb
                                   if (s_izq == 0 && s_iz == 0  && s_i == 0 && csc_i == 0 && csc_d == 0 && s_d == 1 && s_de == 1 && s_der == 1){
                                    Serial.println(" i45");
                                       izquierda_45();
                                       
                                   }
                                   
                               
                          
}


void ultra(){
  digitalWrite(pinTrig, LOW);
  delayMicroseconds(100);
  digitalWrite(pinTrig, HIGH);
  delayMicroseconds(100);
  long pulseDuration = pulseIn(pinEcho, HIGH, 10000);
  Serial.println(pulseDuration);
  
  // Una vez recibida la señal, se calculará la distancia en función de la velocidad
  //  del sonido 340 m/s
  int distance = (int)(0.034 * pulseDuration / 2);
  
 Serial.println(distance);
  Serial.print("test");

  if (distance >= 10) {
    // Mostrar el resultado por el monitor serie
    Serial.print("Distancia ");
    Serial.println(distance);
    Serial.println(" cm");
  } else {
    Serial.println("Distancia desconocida");
  }
  delay(200);


  
 }

void LeerRgb(){
  
    tcaselect(0);
    
    RGB_sensorR1 = RGB_sensor1.readRed();
    RGB_sensorG1 = RGB_sensor1.readGreen();
    RGB_sensorB1 = RGB_sensor1.readBlue();
    Serial.print(F("R11111111111111111111: "));    Serial.print(RGB_sensorR1);
    Serial.print(F("\tG111111111111111111: "));  Serial.print(RGB_sensorG1);
    Serial.print(F("\tB111111111111111111: "));  Serial.println(RGB_sensorB1);

    
    // Compare red value and blue value in RGB_sensor
    tcaselect(1);
    RGB_sensorR2 = RGB_sensor2.readRed();
    RGB_sensorG2 = RGB_sensor2.readGreen();
    RGB_sensorB2 = RGB_sensor2.readBlue();
    Serial.print(F("R22222222222222222222: "));    Serial.print(RGB_sensorR2);
    Serial.print(F("\tG222222222222222222: "));  Serial.print(RGB_sensorG2);
    Serial.print(F("\tB222222222222222222: "));  Serial.println(RGB_sensorB2);


  
}

void RgbAcciones(){

  if (RGB_sensorG1>=GreenMin && RGB_sensorG1<=GreenMax){
       Serial.println("Verde1");
       }else{
            Serial.println("Otro");
            }
    if (RGB_sensorG2>=Green1Min && RGB_sensorG2<=Green1Max){
        Serial.println("Verde2");
        }else{
              Serial.println("Otro1");
              }
              
 delay (5);
}
