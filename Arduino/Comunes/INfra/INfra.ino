 #include <QTRSensors.h>


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

    
const int ledPin= 2;
const int ledPin1= 3;


int os = 320;

 
void setup() {
    pinMode(ledPin, OUTPUT);
    pinMode(ledPin1, OUTPUT);
  
    pinMode(izq_1,INPUT);
    pinMode(izq_2,INPUT);
    pinMode(izq_3,INPUT);
    pinMode(centro_i,INPUT);
    pinMode(centro_d,INPUT);
    pinMode(der_6,INPUT);
    pinMode(der_7,INPUT);
    pinMode(der_8,INPUT);
    Serial.begin(9600);
}

void loop() {
    digitalWrite(ledPin,HIGH);
  digitalWrite(ledPin1,HIGH);
  fondo();
  leerinfra(); 
  linea();
}
void fondo(){
  
}
void linea(){
  
}
void leerinfra(){
 // 0 blanco 1 negro
    if (l1 >= os) {s_izq = 0;}else{s_izq = 1;}
    if (l2 >= os) {s_iz = 0;}else {s_iz = 1;}
    if (l3 >= os) {s_i = 0;}else{s_i = 1;}
    if (l4 >= os) {csc_i = 0;}else{csc_i = 1;}
    if (l5 >= os) {csc_d = 0;}else{csc_d = 1;}
    if (l6 >= os) {s_d = 0;}else{s_d = 1;}
    if (l7 >= os) {s_de = 0;}else{s_de = 1;}
    if (l8 >= os) {s_der = 0;}else{s_der = 1;}

    l1=analogRead(izq_1);
    l2=analogRead(izq_2);
    l3=analogRead(izq_3);
    l4=analogRead(centro_i);
    l5=analogRead(centro_d);
    l6=analogRead(der_6);
    l7=analogRead(der_7);
    l8=analogRead(der_8);



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

}

   
