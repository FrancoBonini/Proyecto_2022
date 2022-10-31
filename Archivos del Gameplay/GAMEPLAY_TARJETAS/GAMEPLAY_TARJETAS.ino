#include <Arduino.h>           // los encabezados de las librerias deben estar declarados tal como se muestra en el sketch, 
#include "DYPlayerArduino.h"   // ya que de lo contrario no funcionaran los dos puertos series, unicamente el predeterminado. 
#include <Adafruit_NeoPixel.h> // Ademas al declarar el segundo puerto serie, hay que utilizar otro nombre para el objeto,   
//#include <Ticker.h>            // de lo contrario se estaria redeclarando el objeto predeterminado.


#define TARJETA1  53
#define TARJETA2  52
#define TARJETA3  51
#define TARJETA4  50
#define TARJETA5  49
#define TARJETA6  48
#define TARJETA7  47
#define SERVO1    46            //PUERTA DEL MULTIBALL
#define SENSOR_MULTIBALL 

typedef enum{TARJETA1_S1, TARJETA1_S2, TARJETA1_S3, TARJETA1_S4, TARJETA2_S1, TARJETA2_S2, TARJETA2_S3, TARJETA2_S4, TARJETA3_S1, TARJETA3_S2, TARJETA3_S3,
TARJETA3_S4, TARJETA4_S1, TARJETA4_S2, TARJETA4_S3, TARJETA4_S4, TARJETA5_S1, TARJETA5_S2, TARJETA5_S3, TARJETA5_S4, TARJETA6_S1, TARJETA6_S2, TARJETA6_S3,
TARJETA6_S4, TARJETA7_S1, TARJETA7_S2, TARJETA7_S3, TARJETA7_S4, TARJETA7_S5, TARJETA7_S6, TARJETA7_S7, PUERTA_ABIERTA, PUERTA_CERRADA, MULTIBALL_ESPERA, 
MULTIBALL_ACTIVO, ESTADO_N} estadoMEF_t;

  bool state_TARJ1 = 1;
  bool state_TARJ2 = 1;
  bool state_TARJ3 = 1;
  bool state_TARJ4 = 1;
  bool state_TARJ5 = 1;
  bool state_TARJ6 = 1;
  bool state_TARJ7 = 1;
  bool MULTIBALL = 0 ;
  bool banco_tarjetas_completo = 0;
  bool banco_tarjetas_multiball = 0;
  

  int puntaje,banco_tarjetas, contador_colecionado_multiball;
  
  estadoMEF_t  eA_TARJETA1;     //ESTADOACTUAL_TARJETA Nª1
  uint8_t tInicio_TARJ1;
  estadoMEF_t  eA_TARJETA2;     //ESTADOACTUAL_TARJETA Nª2
  uint8_t tInicio_TARJ2;
  estadoMEF_t  eA_TARJETA3;     //ESTADOACTUAL_TARJETA Nª3
  uint8_t tInicio_TARJ3;
  estadoMEF_t  eA_TARJETA4;     //ESTADOACTUAL_TARJETA Nª4
  uint8_t tInicio_TARJ4;
  estadoMEF_t  eA_TARJETA5;     //ESTADOACTUAL_TARJETA Nª5
  uint8_t tInicio_TARJ5;
  estadoMEF_t  eA_TARJETA6;     //ESTADOACTUAL_TARJETA Nª6   
  uint8_t tInicio_TARJ6;
  estadoMEF_t  eA_TARJETA7;     //ESTADOACTUAL_TARJETA Nª7
  uint8_t tInicio_TARJ7;

  estadoMEF_t  eA_MULTIBALL;     //ESTADOACTUAL_MULTIBALL  
  uint8_t tInicio_MULTIBALL;
  
  void InicializarMEF_TARJ1(void);        //INICIALIZAR TARJETA 1
  void ActualizarMEF_TARJ1(void);         //ACTUALIZA TARJETA 1
  
  void InicializarMEF_TARJ2(void);
  void ActualizarMEF_TARJ2(void);
  
  void InicializarMEF_TARJ3(void);
  void ActualizarMEF_TARJ3(void);
  
  void InicializarMEF_TARJ4(void);
  void ActualizarMEF_TARJ4(void);
  
  void InicializarMEF_TARJ5(void);
  void ActualizarMEF_TARJ5(void);
  
  void InicializarMEF_TARJ6(void);
  void ActualizarMEF_TARJ6(void);
  
  void InicializarMEF_TARJ7(void);
  void ActualizarMEF_TARJ7(void);

  void InicializarMEF_MULTIBALL(void);
  void ActualizarMEF_MULTIBALL(void);

    //primer parametro = cantidad de pixeles en la tira
   //segundo parametro = pin digital del arduino
  //tercer parametro = NEO_KHZ800 + NEO_GRB

   Adafruit_NeoPixel   tira =    Adafruit_NeoPixel(300,42, NEO_GRB + NEO_KHZ800);


   //void  sonido(uint8_t cantsonido, uint8_t nsonido1, uint8_t nsonido2);

    DY::Player player;            //objeto predeterminado
  //  DY::Player modulo(&Serial1);  //segundo objeto
  
    //en los objetos es donde se establaecen los puertos series que se usaran en la comunicacion, por eso en el segundo objeto
   // se agrega (&Serial2). El numero indica que puerto serie se utilizara.

void setup() {
  
 // attachInterrupt(digitalPinToInterrupt(2),llamadoInterr,RISING);

   pinMode(TARJETA1,INPUT_PULLUP);
   pinMode(TARJETA2,INPUT_PULLUP);
   pinMode(TARJETA3,INPUT_PULLUP);
   pinMode(TARJETA4,INPUT_PULLUP);
   pinMode(TARJETA5,INPUT_PULLUP);
   pinMode(TARJETA6,INPUT_PULLUP);
   pinMode(TARJETA7,INPUT_PULLUP);
   pinMode(SERVO1,INPUT_PULLUP);

  tira.begin();
  tira.show();

  player.begin();
  modulo.begin();

  player.setVolume(12);
  modulo.setVolume(14);
  player.playSpecified(17); 
  modulo.playSpecified(5);

  tira.setBrightness(10);


  InicializarMEF_TARJ1();
  InicializarMEF_TARJ2();
  InicializarMEF_TARJ3();
  InicializarMEF_TARJ4();
  InicializarMEF_TARJ5();
  InicializarMEF_TARJ6();
  InicializarMEF_TARJ7();
  
  InicializarMEF_MULTIBALL();


}

void loop() {

  
  ActualizarMEF_TARJ1();
  ActualizarMEF_TARJ2();
  ActualizarMEF_TARJ3();
  ActualizarMEF_TARJ4();
  ActualizarMEF_TARJ5();
  ActualizarMEF_TARJ6();
  ActualizarMEF_TARJ7();

  ActualizarMEF_MULTIBALL();

  tInicio_TARJ1 = millis();
  tInicio_TARJ2 = millis();
  tInicio_TARJ3 = millis();
  tInicio_TARJ4 = millis();
  tInicio_TARJ5 = millis();
  tInicio_TARJ6 = millis();
  tInicio_TARJ7 = millis();

}

//************* TIRAS LED *************************
void tiraState(bool state, int numpixel)                  
 {
  if(state==true)
  {
    tira.setPixelColor(numpixel,255,255,255);
    tira.show();
  }
  else
  {
    tira.setPixelColor(numpixel,0,0,0);
    tira.show();
  }
}

//***************INICIALIZARMEF DE TARJETAS*************************
void InicializarMEF_TARJ1(void) {
    eA_TARJETA1 = TARJETA1_S1;                // Establece estado inicial 
    tInicio_TARJ1 = tickRead();              // También inicia temporizacion
}
void InicializarMEF_TARJ2(void) {
    eA_TARJETA2 = TARJETA1_S2;                // Establece estado inicial 
    tInicio_TARJ2 = tickRead();              // También inicia temporizacion   
}
void InicializarMEF_TARJ3(void) {
    eA_TARJETA3 = TARJETA1_S3;                // Establece estado inicial 
    tInicio_TARJ3 = tickRead();              // También inicia temporizacion  
}
void InicializarMEF_TARJ4(void) {
    eA_TARJETA4 = TARJETA1_S4;                // Establece estado inicial 
    tInicio_TARJ4 = tickRead();              // También inicia temporizacion   
}
void InicializarMEF_TARJ5(void) {
    eA_TARJETA5 = TARJETA1_S5;                // Establece estado inicial 
    tInicio_TARJ5 = tickRead();              // También inicia temporizacion  
}
void InicializarMEF_TARJ6(void) {
    eA_TARJETA6 = TARJETA1_S6;                // Establece estado inicial 
    tInicio_TARJ6 = tickRead();              // También inicia temporizacion   
}
void InicializarMEF_TARJ7(void) {
    eA_TARJETA7 = TARJETA7_S7;                // Establece estado inicial 
    tInicio_TARJ7 = millis();
    tInicio_TARJ7 = tickRead();              // También inicia temporizacion  
}
void InicializarMEF_MULTIBALL(void){
  eA_MULTIBALL = PUERTA_ABIERTA;              // Establece estado inicial 
  tInicio_MULTIBALL = tickRead();            // También inicia temporizacion  
}

//*******************************************TARJETA 1 + FUNCIONAMIENTO GENERAL DE 6 TARJETAS******************************************************
void ActualizarMEF_TARJ1(void) {
    switch (eA_TARJETA1) {
        case TARJETA1_S1:

                state = true;                         //LED DE LA TARJETA1 PRENDIDO 
                tiraState(state,1);                  //
                eA_TARJETA1 = TARJETA1_S2;          // Cambiar a otro estado
                tInicio_TARJ1 = millis();          // También inicia temporizacion
            
            break;
        case TARJETA1_S2:
            
            if (millis() - tInicio_TARJ1 > 500) {                 
                eA_TARJETA1 = TARJETA1_S1;                  // Cambiar a otro estado                                                           
                !state;                                    //LED DE LA TARJETA1 APAGADO    
            }
            if(TARJETA1==0 && MULTIBALL==1){
                  eA_TARJETA1 = TARJETA1_S4;                  // Cambiar a otro estado
                  puntaje +=100;                             //suma puntos
                  modulo.playSpecified(5);                  //sonido
                  state = true;                            //LED DE LA TARJETA1 PRENDIDO   
                  banco_tarjetas++;                                           
              }
            else(TARJETA1==0){
                  eA_TARJETA1 = TARJETA1_S3;              // Cambiar a otro estado     
                  puntaje +=100;                         //suma puntos
                  modulo.playSpecified(5);              //sonido
                  state = true;                        //LED DE LA TARJETA1 PRENDIDO
                  banco_tarjetas++;
              }             
            break;
        case TARJETA1_S3:
           
            if(banco_tarjetas==6){
                  eA_TARJETA1 = TARJETA1_S1;                      // Cambiar a otro estado inicial
                  banco_tarjetas=0;                              //reinicio la suma de las tarjetas golpeadas
                  banco_tarjetas_completo=1;                    //se golpearon las 6 tarjetas
              }
            
            break;
                   
        case TARJETA1_S4:
            
            if(banco_tarjetas==6){
                  puntaje +=500;                                   //suma puntos especiales
                  eA_TARJETA1 = TARJETA1_S1;                      // Cambiar a otro estado
                  banco_tarjetas=0;                              //reinicio la suma de las tarjetas golpeadas
                  banco_tarjetas_multiball=1;                   //se golpearon las 6 tarjetas
              }
            break;
        default:
            //Si algo modificó la variable estadoActual TARJETA1
            // a un estado no válido llevo la MEF a un 
            // lugar seguro, por ejemplo, la reinicio:
            InicializarMEF_TARJ1();
            
    }
}

//*****************************TARJETA 2***********************************
void ActualizarMEF_TARJ2(void) {
    switch (eA_TARJETA2) {
        case TARJETA2_S1:

                state = true;                         //LED DE LA TARJETA1 PRENDIDO 
                tiraState(state,1);                  //
                eA_TARJETA2 = TARJETA2_S2;          // Cambiar a otro estado
                tInicio_TARJ2 = millis();          // También inicia temporizacion
            
            break;
        case TARJETA2_S2:
            
            if (millis() - tInicio_TARJ2 > 500) {                 
                eA_TARJETA2 = TARJETA2_S1;                  // Cambiar a otro estado                                                           
                !state;                                    //LED DE LA TARJETA1 APAGADO    
            }
            if(TARJETA2==0 && MULTIBALL==1){
                  eA_TARJETA2 = TARJETA2_S4;                  // Cambiar a otro estado
                  puntaje +=100;                             //suma puntos
                  modulo.playSpecified(5);                  //sonido
                  state = true;                            //LED DE LA TARJETA1 PRENDIDO   
                  banco_tarjetas++;                                           
              }
            else(TARJETA2==0){
                  eA_TARJETA2 = TARJETA2_S3;              // Cambiar a otro estado     
                  puntaje +=100;                         //suma puntos
                  modulo.playSpecified(5);              //sonido
                  state = true;                        //LED DE LA TARJETA1 PRENDIDO
                  banco_tarjetas++;
              }             
            break;
        case TARJETA2_S3:
           
            if(banco_tarjetas==6){
                  eA_TARJETA2 = TARJETA2_S1;                      // Cambiar a otro estado inicial                 
              }
            
            break;
                   
        case TARJETA2_S4:
            
            if(banco_tarjetas==6){                 
                  eA_TARJETA2 = TARJETA2_S1;                      // Cambiar a otro estado                
              }
            break;
        default:
            //Si algo modificó la variable estadoActual TARJETA1
            // a un estado no válido llevo la MEF a un 
            // lugar seguro, por ejemplo, la reinicio:
            InicializarMEF_TARJ2();
            
    }
}

//*****************************TARJETA 7 ESPECIAL***********************************
void ActualizarMEF_TARJ7(void) {
    switch (eA_TARJETA7) {
        case TARJETA7_S1:

                state = true;                         //LED DE LA TARJETA7 PRENDIDO 
                tiraState(state,1);                  //
                eA_TARJETA7 = TARJETA7_S2;          // Cambiar a otro estado
                tInicio_TARJ7 = millis();          // También inicia temporizacion
            
            break;
        case TARJETA7_S2:
            
            if (millis() - tInicio_TARJ7 > 500) {                 
                eA_TARJETA7 = TARJETA7_S1;                  // Cambiar a otro estado                                                           
                !state;                                    //LED DE LA TARJETA7 APAGADO    
            }
            if(TARJETA7==0 && MULTIBALL==1){
  /*                eA_TARJETA7 = TARJETA7_S3;                // Cambiar a otro estado
                  puntaje +=10000;                           //suma 10k puntos
                  modulo.playSpecified(5);                  //sonido
                  state = true;                            //LED DE LA TARJETA7 PRENDIDO   
                  tiraState(state,1);                     //
                  state = true;                          //LED DE 10k PRENDIDO
                  tiraState(state,1);                   //  
                  tInicio_TARJ7 = millis();            // También inicia temporizacion  */
                  TARJETA7_10K();       
                  eA_TARJETA7 = TARJETA7_S3;                  // Cambiar a otro estado                               
              }
            else(TARJETA7==0){     
                  puntaje +=100;                         //suma puntos
                  modulo.playSpecified(5);              //sonido
                  eA_TARJETA7 = TARJETA7_S1;           // Cambiar a otro estado
              }             
            break;
        case TARJETA7_S3:

          if (millis() - tInicio_TARJ7 > 500) {                                                                           
                !state;                                    //LED DE LA TARJETA7 
                tiraState(state,1);                       //  
                tInicio_TARJ7 = millis();                // También inicia temporizacion
            }
           
           if(TARJETA7==0 && MULTIBALL==1){
                  puntaje +=30000;                           //suma 30k puntos
                  modulo.playSpecified(5);                  //sonido
                  state = true;                            //LED DE LA TARJETA7 PRENDIDO   
                  tiraState(state,1);                     //
                  state = true;                          //LED DE 30k PRENDIDO
                  tiraState(state,1);                   // 
                  eA_TARJETA7 = TARJETA7_S4;           //Cambiar a otro estado  
                  tInicio_TARJ7 = millis();           // También inicia temporizacion                                       
              }
            
            break;
                   
        case TARJETA7_S4:

            if (millis() - tInicio_TARJ7 > 500) {                                                                           
                !state;                                    //LED DE LA TARJETA7 
                tiraState(state,1);                       //  
                tInicio_TARJ7 = millis();                // También inicia temporizacion
            }
           
           if(TARJETA7==0 && MULTIBALL==1){
                  puntaje +=50000;                           //suma 50k puntos
                  modulo.playSpecified(5);                  //sonido
                  state = true;                            //LED DE LA TARJETA7 PRENDIDO   
                  tiraState(state,1);                     //
                  state = true;                          //LED DE 50k PRENDIDO
                  tiraState(state,1);                   // 
                  eA_TARJETA7 = TARJETA7_S5;           //Cambiar a otro estado  
                  tInicio_TARJ7 = millis();           // También inicia temporizacion                                       
              }   
            
            break;
            case TARJETA7_S5:

            if (millis() - tInicio_TARJ7 > 500) {                                                                           
                !state;                                    //LED DE LA TARJETA7 
                tiraState(state,1);                       //  
                tInicio_TARJ7 = millis();                // También inicia temporizacion
            }
           
           if(TARJETA7==0 && MULTIBALL==1){
                  EXTRABALL = 1;
                  modulo.playSpecified(5);                  //sonido
                  state = true;                            //LED DE LA TARJETA7 PRENDIDO   
                  tiraState(state,1);                     //
                  state = true;                          //LED DE EXTRABALL PRENDIDO
                  tiraState(state,1);                   // 
                  eA_TARJETA7 = TARJETA7_S6;           //Cambiar a otro estado  
                  tInicio_TARJ7 = millis();           // También inicia temporizacion                                       
              }   
            
            break;
            case TARJETA7_S6:

            if (millis() - tInicio_TARJ7 > 500) {                                                                           
                !state;                                    //LED DE LA TARJETA7 
                tiraState(state,1);                       //  
                tInicio_TARJ7 = millis();                // También inicia temporizacion
            }
           
           if(TARJETA7==0 && MULTIBALL==1){
                  puntaje +=70000;                           //suma 70k puntos
                  modulo.playSpecified(5);                  //sonido
                  state = true;                            //LED DE LA TARJETA7 PRENDIDO   
                  tiraState(state,1);                     //
                  state = true;                          //LED DE 70K PRENDIDO
                  tiraState(state,1);                   // 
                  eA_TARJETA7 = TARJETA7_S7;           //Cambiar a otro estado  
                  tInicio_TARJ7 = millis();           // También inicia temporizacion                                       
              }   
            
            break;
            case TARJETA7_S7:

            if (millis() - tInicio_TARJ7 > 500) {                                                                           
                !state;                                    //LED DE LA TARJETA7 
                tiraState(state,1);                       //  
                tInicio_TARJ7 = millis();                // También inicia temporizacion
            }
           
           if(TARJETA7==0 && MULTIBALL==1){
                  puntaje +=000000000;                           //suma PUNTAJE ESPECIAL
                  modulo.playSpecified(5);                  //sonido
                  state = true;                            //LED DE LA TARJETA7 PRENDIDO   
                  tiraState(state,1);                     //
                  state = true;                          //LED DE SPECIAL POINT PRENDIDO
                  tiraState(state,1);                   // 
         //       eA_TARJETA7 = TARJETA7_S7;           //Cambiar a otro estado  
                  tInicio_TARJ7 = millis();           // También inicia temporizacion                                       
              }   
            
            break;
        default:
            //Si algo modificó la variable estadoActual TARJETA1
            // a un estado no válido llevo la MEF a un 
            // lugar seguro, por ejemplo, la reinicio:
            InicializarMEF_TARJ7();
            
    }
}

//***********************************MULTIBALL*******************************************
void ActualizarMEF_MULTIBALL(void){
      switch (eA_MULTIBALL) {
        case PUERTA_ABIERTA:                          
        
            if(banco_tarjetas_completo == 1){
              eA_MULTIBALL = PUERTA_CERRADA;                  //cambia de estado
              SERVO1 = 1;                                    //se cierra la puerta para guardar pelotitas
              contador_colecionado_multiball = 0;           //reinicio el contador para empezar a contar 
            }
                
            break;
        case PUERTA_CERRADA:

            if(SENSOR_MULTIBALL==1){
              contador_colecionado_multiball++;           //cuenta las bolas guardadas
            }
            
            if(contador_colecionado_multiball == 3){
              eA_MULTIBALL = MULTIBALL_ESPERA;           //cambia de estado  
              MULTIBALL = 1;                            // activo multiball  
            }
                       
            break;
        case MULTIBALL_ESPERA:
           
            if(banco_tarjetas_multiball = 1){
             tInicio_MULTIBALL = millis();              // inicia temporizacion
             MULTIBALL = 0;                            // desactivo multiball  
             eA_MULTIBALL = MULTIBALL_ACTIVO;         //cambia de estado 
             SERVO1 = 0;                             //se abre la puerta para guardar pelotitas 
            }
            
            break;
                   
        case MULTIBALL_ACTIVO:
            if(millis() - tInicio_1 > 5000){
             eA_MULTIBALL = PUERTA_ABIERTA;           //cambia de estado   
                 
            }
            break;
        default:
            //Si algo modificó la variable estadoActual PUERTA_ABIERTA
            // a un estado no válido llevo la MEF a un 
            // lugar seguro, por ejemplo, la reinicio:
            InicializarMEF_MULTIBALL();
     }
}


//**********************************************************************************************************************************************************
void TARJETA7_10K(void){
  
   
                  puntaje +=10000;                           //suma 10k puntos
       //           modulo.playSpecified(5);                  //sonido
                  state = true;                            //LED DE LA TARJETA7 PRENDIDO   
                  tiraState(state,1);                     //
                  state = true;                          //LED DE 10k PRENDIDO
                  tiraState(state,1);                   //  
  }
