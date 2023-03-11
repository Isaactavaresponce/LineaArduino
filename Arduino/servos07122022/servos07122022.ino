#include <Servo.h>


//---------------------------------
//*            MOTORES              *
//-----------------------------------*/
   Servo mid;
   Servo mit;
   Servo mdd;
   Servo mdt;

/*-----------------------------------
 *            VARIABLES            *
-----------------------------------*/

/////////// pines de conexion ////////////////////
/* Motores  */
  const int pmit=47;
  const int pmid=49;
  const int pmdd=43;//43
  const int pmdt=45;//45



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  /*  Motores  */
  mid.attach(pmid);
  mit.attach(pmit);
  mdd.attach(pmdd);
  mdt.attach(pmdt);


}

void moverse(){
  Serial.println(ciclo);
  int i1 = 0; 
  int i2 = 0;
  int d1 = 0;
  int d2 = 0;
  mid.write(i1);
  mit.write(i2);
  mdd.write(d1);
  mdt.write(d2);
  
}



void loop() {
  // put your main code here, to run repeatedly:
  moverse();
}
