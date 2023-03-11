

#include <NewPing.h>

#include <Servo.h>

int TRIG = 10;      // trigger en pin 10
int ECO = 9;      // echo en pin 9
int LED = 3;      // LED en pin 3
int DURACION;
int DISTANCIA;

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
  pinMode(TRIG, OUTPUT);  // trigger como salida
  pinMode(ECO, INPUT);    // echo como entrada
  pinMode(LED, OUTPUT);   // LED como salida
  Serial.begin(9600); 

  


}




void moverse(){
  //Serial.println(ciclo);
  int i1 = 0; 
  int i2 = 0;
  int d1 = 180;
  int d2 = 180;
  mid.write(i1);
  mit.write(i2);
  mdd.write(d1);
  mdt.write(d2);
  
}

void detenerse(){
void  moverse(0,0);
}

void loop() {
  // put your main code here, to run repeatedly:
  moverse();

  digitalWrite(TRIG, HIGH);     // generacion del pulso a enviar
  delay(1);       // al pin conectado al trigger
  digitalWrite(TRIG, LOW);    // del sensor
  
  DURACION = pulseIn(ECO, HIGH);  // con funcion pulseIn se espera un pulso
            // alto en Echo
  DISTANCIA = DURACION / 58.2;    // distancia medida en centimetros
  Serial.println(DISTANCIA);    // envio de valor de distancia por monitor serial
  delay(200);       // demora entre datos

  if (DISTANCIA <= 20 && DISTANCIA >= 0){ // si distancia entre 0 y 20 cms.
    detenerse();     // apaga LED
    }
}
