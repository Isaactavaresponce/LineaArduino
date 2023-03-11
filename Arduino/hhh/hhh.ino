/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define mi1        3
#define mi2        4
#define pwmi       6
#define md1        8
#define md2        7
#define pwmd       5

void setup() 
{
  pinMode(mi1,OUTPUT);
  pinMode(mi2,OUTPUT);
  pinMode(md1,OUTPUT);
  pinMode(md2,OUTPUT);
}

void loop()
{
  motores(100,100);
}

void motores(int motor_izq, int motor_der)
{
  if( motor_izq >=0)
    {
      digitalWrite (mi1,HIGH);
      digitalWrite (mi2,LOW);
      analogWrite (pwmi,motor_izq);
    }
  else
    {
      digitalWrite(mi1,LOW);
      digitalWrite(mi2,HIGH);
      motor_izq = motor_izq*(-1);
      analogWrite(pwmi,motor_izq); 
    }
  if(motor_der>=0)
    {
      digitalWrite(md1,HIGH);
      digitalWrite(md2,LOW);
      analogWrite(pwmd,motor_der);
  }
  else
     {
      digitalWrite(md1,LOW);
      digitalWrite(md2,HIGH);
      motor_der=motor_der*(-1);
      analogWrite(pwmd,motor_der);    
     }
}
