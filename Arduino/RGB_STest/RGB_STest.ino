// fecha 6/01/23

//---------------------------------------------------------------------------------------------------------------------
//                                                 Librerias
//---------------------------------------------------------------------------------------------------------------------

#include <QTRSensors.h>
#include <AFMotor.h>
#include <Wire.h>


//                                                                                        #include <Adafruit_HMC5883_U.h>
#define TCAADDR 0x70


//------------------------- RGB
#include "Arduino.h"
#include "SparkFunISL29125.h"


// Pin Definitions



// Global variables and defines
uint16_t RGB_sensorR1,RGB_sensorG1,RGB_sensorB1;
uint16_t RGB_sensorR2,RGB_sensorG2,RGB_sensorB2;
// object initialization

SFE_ISL29125 RGB_sensor1;
SFE_ISL29125 RGB_sensor2;


 int Green1Max = 500;
 int Green1Min = 400;




//---------------------------------------------------------------------------------------------------------------------
//                                      Variables de control para sensores
//---------------------------------------------------------------------------------------------------------------------


//---------RGB------------------------------------------------------------------------------------------------------------
long time0;

//------------------------------------------------------------------------------------------------------------------------------------------
//                                           Selecciona Puerto del Multiplexor
//------------------------------------------------------------------------------------------------------------------------------------------    
void tcaselect(uint8_t i) {
    if (i > 7) return;
    
    Wire.beginTransmission(TCAADDR);
    
    Wire.write(1 << i);
    
    Wire.endTransmission();
}








//------------------------------------------------------------------------------------------------------------------------------------------
//                                                              Setup
//------------------------------------------------------------------------------------------------------------------------------------------    
void setup() {
   
   //Puerto serial 
   Serial.begin(9600); 
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
    

     
}

//------------------------------------------------------------------------------------------------------------------------------------------
//                                                              Loop
//------------------------------------------------------------------------------------------------------------------------------------------    

void loop() {
   Serial.println("Hola");
   //-------------------------RGB
       // SparkFun ISL29125 - RGB Light Sensor - Test Code
    // Compare red value and blue value in RGB_sensor
    tcaselect(0);
    
    RGB_sensorR1 = RGB_sensor1.readRed();
    RGB_sensorG1 = RGB_sensor1.readGreen();
    RGB_sensorB1 = RGB_sensor1.readBlue();
    Serial.print(F("R11111111111111111111: "));    Serial.print(RGB_sensorR1);
    Serial.print(F("\tG111111111111111111: "));  Serial.print(RGB_sensorG1);
    Serial.print(F("\tB111111111111111111: "));  Serial.println(RGB_sensorB1);
    delay(1500);

    if (RGB_sensorG1>=Green1Min && RGB_sensorG1<=Green1Max){
       Serial.println("Verde");
    }else{
      Serial.println("Otro");
  
    }
    

    
  
}
