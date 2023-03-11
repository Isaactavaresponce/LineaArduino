#include <AFMotor.h>

#include <QTRSensors.h>

int csc_i=0;
int csc_d=0;

int s_i=0;
int s_d=0;




AF_DCMotor motor1(1);
AF_DCMotor motor2(2);

void setup() {
  // put your setup code here, to run once:
motor1.setSpeed(150);
motor2.setSpeed(150);


}

void loop() {
  // put your main code here, to run repeatedly:

if (csc_i<=500){
  csc_i=0;
}else{
  csc_i=1;
}
if (csc_d<=500){
  csc_d=0;
}else{
  csc_d=1;
}
if(s_i<=500){
  s_i=0;
}else{
  s_i=1;
}
if (s_d<=500){
  s_d=0;
}
else{
  s_d=1;
}


if (csc_i==0 && csc_d==0 && s_i==1 && s_d==1){
  

  motor1.run(FORWARD);
  motor2.run(FORWARD);
}
