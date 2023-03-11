#include <Servo.h>
//---------------------------------
 //*            MOTORES              *
//-----------------------------------*/
  Servo mid;
  Servo mit;
  Servo mdd;
  Servo mdt;

//*-----------------------------------
// *            VARIABLES            *
//-----------------------------------*/

/////////// pines de conexion ////////////////////
/* Motores  */
  const int pmit=47;
  const int pmid=49;
  const int pmdd=43;//43
  const int pmdt=45;//45


//Variables de duracion de los movimientos/

  int imp = 40;                     //Tiempo impulso luego de giro izquierda
  int giros_I = 15; //16
  int giros_ISF = 15; //16
  int giros_D = 23; //20               //Tiempo de giros izquierda y derecha
  int gir_u =54;                    //Tiempo de giro en u
  int avance_ISF = 0;
  long MIT,MIF,MFT,MDF,MDT;        // Mediciones de sensores ultrasonicos en centimetros 
  long MMIT,MMIF,MMFT,MMDF,MMDT;   // Mediciones de sensores ultrasonicos en milimetros
  int  LIT,LIF,LFT,LDF,LDT;        // Valores logicos de lectura de sensores ultrasonicos

void setup(){
  Serial.begin(9600);
  /*  Motores  */
  mid.attach(pmid);
  mit.attach(pmit);
  mdd.attach(pmdd);
  mdt.attach(pmdt);
}

//--------------------------------------------------------------------------------
//*                            FUNCIONES Y PROCESOS                                *
//--------------------------------------------------------------------------------

//*****************
//*     Lectura de Sensores                         *
//*****************

void direccion(){
  mensaje="";
  if(color != "NEGRO" && con_vi==0){
    if (inercia=="FT"){
      //Con pared al frente
      if (LFT==0){
        // NO HAY PARED A LA IZQUIERDA Y HAY PAREDA AL FRENTE
        if (LIT ==1 && LIF==1){
          izquierda();
        }else{
          // NO HAY PARED A LA DERECHA Y HAY PAREDA AL FRENTE
          if ((LDF==1 && LDT==1) && (LIT ==0 && LIF==0)){
            derecha();
          }else{
            //HAY PARED EN TODAS LAS DIRECCIONES
             if ((LDF==0 && LDT==0) && (LIF==0 && LIT==0) ){
               giro_u();
             }else{
              //SI HAY UNA INDETERMINACION
                adelante();
             }
          
          }
        }
      }else{
         //No hay pared a la izquierda y no hay pared al frente
         if (inercia=="IM"){
            impulso();
         }else{
            if (LIT ==1 && LIF==1){
              izquierda_sin_fte();
           }else{
            adelante(); 
           }
         }
      }
    }else{
      if (inercia=="IZ"){
        izquierda();
      }else{
        if (inercia=="IZF"){
          izquierda_sin_fte();
        }else{
          if(inercia=="DER"){
            derecha();
          }else{
            if (inercia=="GU"){
              giro_u();
            }else{
              if (inercia=="IM"){
                impulso();
              }
            }
          }
        }
      }
    }
  }else{
    if(color == "NEGRO"){
      giro_u();
    }else{
      if (con_vi>0 && con_vi<5){
          Serial.print("victima ");
          Serial.println(con_vi);
          moverse(0,0);
          digitalWrite(led_vi,HIGH);
          con_vi=con_vi+1;
      }else{
          if (con_vi>=5){
              Serial.print("sali de victima");
              con_vi=0;
              digitalWrite(led_vi,LOW);
              adelante();
           }
      }
    }
  }
}

//*****************
//* Función para controlar Servo motores            *
//*****************

void adelante(){
  if(LDF==1){
      // ESTA PEGADO A LA PARED IZQUIERDA AJUSTA A LA DERECHA 
      if (MMIF<=60){
        moverse(2,3);
      }else{
        // ESTA ALEJADO DE LA PARED IZQUIERDA AJUSTA A LA IZQUIERDA 
        if (MMIF>=70){ //80
          moverse(3,2);
        }else{
          // SIGUE DE FRENTE 
          moverse(1,1);
        }
      }
  }else{
    if (MMIF==MMDF){
      moverse(1,1);
    }else{
      if(MMIF>MMDF){
        moverse(3,2);
      }else{
        if(MMDF>MMIF){
        moverse(2,3);
          }
        }
  }

  }
  /*
  // ESTA PEGADO A LA PARED IZQUIERDA AJUSTA A LA DERECHA 
  if (MMIF<=60){
    moverse(2,3);
  }else{
    // ESTA ALEJADO DE LA PARED IZQUIERDA AJUSTA A LA IZQUIERDA 
    if (MMIF>=70){ //80
      moverse(3,2);
    }else{
      // SIGUE DE FRENTE 
      moverse(1,1);
    }
  }*/
  
}


void detenerse(){
  moverse(0,0);
}



void izquierda(){
  if (ciclo<=giros_I){
    moverse(-1,1);
    inercia="IZ";
    ciclo++;
  }else{
    if (MDT>MDF){  
        moverse(-1,1);
        inercia="IZ";
        }
        else{
        if (MDT==MDF){
          moverse(1,1);
          inercia="IZ";
        }else{
          ciclo=0;
          moverse(1,1);
          inercia="IM";
        }
    /*}else{
        moverse(-1,1);
        inercia="IZ";
        ciclo+1;
    }*/
    }
  }
}

void izquierda_sin_fte(){
  if(avance_ISF < 4){
    if(LFT == 0){
      inercia="FT";
      avance_ISF=0;
      ciclo=0;
      }
      else{
        inercia="IZF";
        moverse(1,1);
        avance_ISF++;
        }
    }
    else{
      if (ciclo<=giros_ISF){
        moverse(-1,1);
        inercia="IZF";
        ciclo++;
      }else{
            ciclo=0;
            avance_ISF=0;
            moverse(1,1);
            inercia="IM";
        }
    }
}

void derecha(){ 
  if (ciclo<=giros_D){
    moverse(1,-1);
    inercia="DER";
    ciclo++;
  }else{
     if (MIT>MIF){
        moverse(1,-1);
        inercia="DER";
      }
      else{
        if (MIT==MIF){
          moverse(1,1);
          inercia="DER";
        }
        else{
          ciclo=0;
          moverse(1,1);
          inercia="FT";
        }
      }
    /*
    if (MIT<=MIF){   
        ciclo=0;
        moverse(1,1);
        inercia="IM";
        //inercia="FT"; 
    }else{
        moverse(-1,1);
        inercia="IZ";
        ciclo++;
    }
    */
  }
}

void giro_u(){
  if (ciclo<=54){
    moverse(-1,1);
    inercia="GU";
    ciclo++;
  }else{
    //if (MDT>=MDF+dif && MDT<=MDF+dif){
        ciclo=0;
        moverse(1,1);
        inercia="FT";
    /*}else{
        moverse(-1,1);
        inercia="IZ";
        ciclo+1;
    }*/
  }
}

void impulso(){
  if (ciclo<=imp){
    if(LFT==0){
      ciclo=0;
      inercia="FT";
    }else{
      if(LDT ==0 && LDF==0){
          // ESTA PEGADO A LA PARED IZQUIERDA AJUSTA A LA DERECHA 
          if (MMDF<=60){
            moverse(3,2);
          }else{
            // ESTA ALEJADO DE LA PARED IZQUIERDA AJUSTA A LA IZQUIERDA 
            if (MMDF>=70){ //80
              moverse(2,3);
            }else{
              // SIGUE DE FRENTE 
              moverse(1,1);
            }
         }
      }else{
         moverse(1,1);
        }
      inercia="IM";
   }
      ciclo++;
  }else{
    //moverse(0,0);
    //delay(5000);
    inercia="FT";
    ciclo=0;
    }
 }


  Serial.println(ciclo);
  int i1 = 90; //90 se detienen los motores 
  int i2 = 90;
  int d1 = 90;
  int d2 = 90;
  //vi = velocidad iquierda
  if (vi==0){
      int i1 = 90; //90 se detienen los motores 
      int i2 = 90;
  }else{
    if (vi==1){
      i1=48;         // para que giren en sentidos contrarios  a las manecillas del reloj
      i2=48;         // los valores se  ajustan para que giren parejos los motores 
    }else{
      if (vi==-1){
         i1=132;          // menor a 90 para motores derechos y mayor a 90 en izquierdos 
         i2=132;  
      }else{
         if (vi==2){
            mensaje="ajuste a la derecha ";
            i1=30;         // para que giren en sentidos contrarios  a las manecillas del reloj
            i2=30;         // los valores se  ajustan para que giren parejos los motores           
         }else{
          if (vi==3){
             i1=70;          // menor a 90 para motores derechos y mayor a 90 en izquierdos
             i2=70;         //  e impulsen el robot hacia adelant          
          }    
        }
      }
    }
  }
  
  //vd = velocidad derecha
  if (vd==0){
      int d1 = 90; //90 se detienen los motores 
      int d2 = 90;
  }else{
    if (vd==1){
      d1=132;          // menor a 90 para motores derechos y mayor a 90 en izquierdos
      d2=132;          //  e impulsen el robot hacia adelante
    }else{
      if (vd==-1){
        d1=48;         // para que giren en sentidos contrarios  a las manecillas del reloj
        d2=48;         // los valores se  ajustan para que giren parejos los motores        
      }else{
        if (vd==2){
          mensaje="ajuste a la izquierda ";
          d1=140;          // menor a 90 para motores derechos y mayor a 90 en izquierdo
          d2=140;          //  e impulsen el robot hacia adelant          
        }else{
          if (vd==3){
             d1=110;          // menor a 90 para motores derechos y mayor a 90 en izquierdos
             d2=110;          //  e impulsen el robot hacia adelant          
          }    
        }
      }
    }
  }

  mid.write(i1);
  mit.write(i2);
  mdd.write(d1);
  mdt.write(d2);
  
}
