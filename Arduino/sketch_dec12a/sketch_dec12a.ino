#include <Servo.h>
#include <Servo.h>
#include <NewPing.h>
#include <Wire.h>
#include <HCSR04.h>

#define TRIG A2 // PIN TRIGGER connectado al pin analogico A2
#define ECHO A3 // PIN ECHO conectado al pin analogico A3
#define MAX_DISTANCE 100 // Define la Maxima Distancia

NewPing sonar(TRIG, ECHO, MAX_DISTANCE); 

Servo mid;
Servo mit;
Servo mdd;
Servo mdt;

const int pmid=47;
const int pmit=49;
const int pmdd=43;
const int pmdt=45;


void setup() {
  mid.attach (pmid);
  mit.attach (pmit);
  mdd.attach (pmdd);
  mdt.attach (pmdt);
}

void loop() {

 delay(70);
int distance = sonar.ping_cm();
if (distance == 0) {
  distance = 15;
}
if(distance <=15) {   // Se define la distancia para detectar un obstaculo y las acciones a tomar
  delay(100);
  turnRight();
  delay(580);
  moveForward();
  delay(450);
  turnLeft();
  delay(550);
  moveForward();
  delay(700);
  turnLeft();
  delay(500);
  moveForward();
  delay(480);
  turnRight();
  delay(500);
 
}

}
