#include <Servo.h>


  int mid;
  int mit;
  int mdd;
  int mdt;

  const int pmit=47;
  const int pmid=49;
  const int pmdd=43;//43
  const int pmdt=45;//45

void setup() {
// put your setup code here, to run once:
Serial.begin(9600);
Serial.println("Servo 360 - Arduino");
//servo1.attach(5); //Default
mid.motorattach (5); //motor 1
mid.write(90);
mit.setSpeed(5); //motor 2
mit.write(90);
mdd.setSpeed(5); //motor 3
mdd.write(90);
mdt.setSpeed(5); //motor 4
mdt.write(90);
}
