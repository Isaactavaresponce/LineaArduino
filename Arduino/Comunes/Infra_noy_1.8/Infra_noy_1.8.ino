#include <QTRSensors.h>
#include <Servo.h>
#define BOTON    13
#define AI  A4
#include <Wire.h>
QTRSensors qtr;

const uint8_t SensorCount = 8;
uint16_t sensorValues[SensorCount];

unsigned int Negro[8];
unsigned int Blanco[8];
unsigned int umbral[8];
int digital[8];

long int sumap, suma, pos, poslast, position;
//Servo
Servo mid;
Servo mit;
Servo mdd;
Servo mdt;


const int pmdd=43;//43
const int pmdt=45;//45
const int pmid=49;
const int pmit=47;

int s_izq = 0;
int s_iz = 0;
int s_i = 0;
int csc_i = 0;
int csc_d = 0;
int s_d = 0;
int s_de = 0;
int s_der = 0;
//Leds
const int ledPin= 2;
const int ledPin1= 3;

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
 // RGB Izquierdo
 int RedMaxI = 1300;
 int RedMinI = 1150;
 int GreenMaxI = 2900; 
 int GreenMinI = 2750;
 int BlueMaxI = 2100;      
 int BlueMinI = 2000;

 
 // RGB Derecho
 int RedMaxD = 1000 ;       
 int RedMinD = 900;
 int GreenMaxD = 2300; 
 int GreenMinD = 2150;
 int BlueMaxD = 1900;  
 int BlueMinD = 1800;

void tcaselect(uint8_t i) {
    if (i > 7) return;
    
    Wire.beginTransmission(TCAADDR);
    
    Wire.write(1 << i);
    
    Wire.endTransmission();
}




void calibrate(){
  // Calibrar valor negro
  while(digitalRead(BOTON));
  for (int i = 0; i < 20; i++)
  {
    blanco();
//negro();
  Serial.println("\t");
  }

  
  // Calibrar valor blanco
  while(digitalRead(BOTON));
  for (int i = 0; i < 20; i++)
  {
    negro();
 //blanco();
   Serial.println("\t");
  }
promedio();
while(digitalRead(BOTON));

}

void setup()
{

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
       }0
    
    // Inicializa el 2° sensor RGB Derecho
    tcaselect(1);
    if (RGB_sensor2.init())    //Iniciar 2° sensor RGB
       {
           Serial.println("Sensor 2 iniciado");
       }
       else 
       {
           Serial.println("Sensor 2 ERROR de iniciado");
       }

     Serial.println("sali setup"); 

  // Servos
  mid.attach(pmid);
  mit.attach(pmit);
  mdd.attach(pmdd);
  mdt.attach(pmdt);
  // configure the sensors
  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){A8, A9, A10, A11, A12, A13, A14, A15}, SensorCount);
  qtr.setEmitterPin(5);
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin1, OUTPUT);
  digitalWrite(ledPin,HIGH);
  digitalWrite(ledPin1,HIGH);

  Serial.begin(9600);
    calibrate();
}
void promedio(){
  for(int i=0;i<8;i++){
  umbral[i]=(Negro[i]+Blanco[i])/2;
  Serial.print(umbral[i]);
  Serial.println("\t");
}
}
void blanco(){
  for(int i=0;i<8;i++){
     qtr.read(sensorValues);
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  // Blanco[i]=analogRead(AI);
    Blanco[i] =  (sensorValues[i]);
  }
}
void negro(){
    for(int i=0;i<8;i++){
     qtr.read(sensorValues);
   Serial.print(sensorValues[i]);
  Serial.print('\t');
  //  Negro[i]=analogRead(AI);
    Negro[i] =    (sensorValues[i]);
    }
}


void loop(){
lectura();
direccion();
leerrgb();
dirrgb();
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

int lectura(void){

    // read raw sensor values
  qtr.read(sensorValues);

  for (uint8_t i = 0; i < SensorCount; i++)
  {
    //  if (sensorValues[i]>= umbral[i]){sensorValues[i] = 0;}else{sensorValues[i] = 1;}
      
 //   Serial.print(sensorValues[i]);
   // Serial.print('\t');
  if(sensorValues[i]<=umbral[i]){digital[i]=1;}else{digital[i]=0;
  Serial.print(digital[i]);
  Serial.print("\t");
  }
  }
}
/*
sumap=(700*digital[0]+600*digital[1]+500*digital[2]+400*digital[3]+300*digital[4]+200*digital[5]+100*digital[6]+0*digital[7]);
suma=(digital[0]+digital[1]+digital[2]+digital[3]+digital[4]+digital[5]+digital[6]+digital[7]);
pos=(sumap/suma);
if(poslast<=100 && pos==-1){
  pos=0;
}
if(poslast>=600 && pos==-1){
  pos=700;
  poslast=pos;
return pos;
*/



void direccion(){
  //   negro 0  blanco 1
  //   [0]    [1]  [2]  [3]    [4]   [5]   [6]   [7]
  //  s_izq  i_iz  s_i csc_i  csc_d  s_d  s_de  s_der
  // --BNNB--
   if(digital[2] == 1 && digital[3] == 0 && digital[4] == 0 && digital[5] == 1){
     moverse();
     }else
        //--BBNN--
        if(digital[2] == 1 && digital[3] == 1 && digital[4] == 0 && digital[5] == 0){
          derecha();
          }else
             //--BBNNN-
             if(digital[2] == 1 && digital[3] == 1 && digital[4] == 0 && digital[5] == 0  && digital[6] == 0){
                derecha_45();//
                }else
                   //--BBBNN-
                   if(digital[2] == 1 && digital[3] == 1 && digital[4] == 1 && digital[5] == 0  && digital[6] == 0){
                     derecha();
                     }else
                        //BBBNNNNN
                        if(digital[0] == 1 && digital[1] == 1 && digital[2] == 1 && digital[3] == 0 && digital[4] == 0 && digital[5] == 0  && digital[6] == 0 && digital[7] == 0 ){ //Derecha
                           derecha_45();
                           }else
                              //--NNBB--
                              if(digital[2] == 0 && digital[3] == 0 && digital[4] == 1 && digital[5] == 1){
                                 izquierda();
                                 }else
                                    //-NNNBB--
                                    if(digital[1] == 0 && digital[2] == 0 && digital[3] == 0 && digital[4] == 1 && digital[5] == 1){
                                      izquierda_45();                                
                                      }else
                                         //-NNBBB--
                                         if(digital[1] == 0 && digital[2] == 0 && digital[3] == 1 && digital[4] == 1 && digital[5] == 1){
                                           izquierda();
                                           }else
                                              //NNNNNBBB
                                              if(digital[0] == 0 && digital[1] == 0 && digital[2] == 0 && digital[3] == 0 && digital[4] == 0 && digital[5] == 1  && digital[6] == 1 && digital[7] == 1){ //Izquierda
                                                izquierda_45();
                                                }
}

void leerrgb(){
  

      tcaselect(0);
    
    RGB_sensorR1 = RGB_sensor1.readRed();
    RGB_sensorG1 = RGB_sensor1.readGreen();
    RGB_sensorB1 = RGB_sensor1.readBlue();
    Serial.print(F("R11111111111111111111: "));    Serial.print(RGB_sensorR1);
    Serial.print(F("\tG111111111111111111: "));  Serial.print(RGB_sensorG1);
    Serial.print(F("\tB111111111111111111: "));  Serial.println(RGB_sensorB1);
    delay(700);
    
    // Compare red value and blue value in RGB_sensor
    tcaselect(1);
    RGB_sensorR2 = RGB_sensor2.readRed();
    RGB_sensorG2 = RGB_sensor2.readGreen();
    RGB_sensorB2 = RGB_sensor2.readBlue();
    Serial.print(F("R22222222222222222222: "));    Serial.print(RGB_sensorR2);
    Serial.print(F("\tG222222222222222222: "));  Serial.print(RGB_sensorG2);
    Serial.print(F("\tB222222222222222222: "));  Serial.println(RGB_sensorB2);

    delay(700);
}

void dirrgb(){
  
    if ((RGB_sensorR1<=RedMaxD && RGB_sensorR1>=RedMinD  )||
       (RGB_sensorG1<=GreenMaxD && RGB_sensorG1>=GreenMinD)||
       (RGB_sensorB1<=BlueMaxD && RGB_sensorB1>=BlueMaxD)){
       Serial.println("Stop");
       }else{
            Serial.println("Otro");
            }
     if ((RGB_sensorR2<=RedMaxI && RGB_sensorR2>=RedMinI  )||
        (RGB_sensorG2<=GreenMaxI && RGB_sensorG2>=GreenMinI)||
        (RGB_sensorB2<=BlueMaxI && RGB_sensorB2>=BlueMaxI)){
        Serial.println("Stop1");
        }else{
              Serial.println("Otro1");
              }
}
