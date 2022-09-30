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

typedef enum{TARJETA1_S1, TARJETA1_S2, TARJETA1_S3, TARJETA1_S4, TARJETA2_S1, TARJETA2_S2, TARJETA2_S3, TARJETA2_S4, TARJETA3_S1, TARJETA3_S2, TARJETA3_S3, TARJETA3_S4, TARJETA4_S1, TARJETA4_S2, TARJETA4_S3, TARJETA4_S4, TARJETA5_S1, TARJETA5_S2, TARJETA5_S3, TARJETA5_S4, TARJETA6_S1, TARJETA6_S2, TARJETA6_S3, TARJETA6_S4, TARJETA7_S1, TARJETA7_S2, TARJETA7_S3, TARJETA7_S4, PUERTA_ABIERTA, PUERTA_CERRADA, MULTIBALL_ESPERA, MULTIBALL_ACTIVO, ESTADO_N} estadoMEF_t;

  bool state_TARJ1 = 1;
  bool state_TARJ2 = 1;
  bool state_TARJ3 = 1;
  bool state_TARJ4 = 1;
  bool state_TARJ5 = 1;
  bool state_TARJ6 = 1;
  bool state_TARJ7 = 1;
  
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

    //primer parametro = cantidad de pixeles en la tira
   //segundo parametro = pin digital del arduino
  //tercer parametro = NEO_KHZ800 + NEO_GRB

   Adafruit_NeoPixel   tira =    Adafruit_NeoPixel(300,42, NEO_GRB + NEO_KHZ800);


   //void  sonido(uint8_t cantsonido, uint8_t nsonido1, uint8_t nsonido2);

    DY::Player player;            //objeto predeterminado
    DY::Player modulo(&Serial1);  //segundo objeto
  
    //en los objetos es donde se establaecen los puertos series que se usaran en la comunicacion, por eso en el segundo objeto
   // se agrega (&Serial2). El numero indica que puerto serie se utilizara.

void setup() {
  
  attachInterrupt(digitalPinToInterrupt(2),llamadoInterr,RISING);

   pinMode(TARJETA1,INPUT_PULLUP);
   pinMode(TARJETA2,INPUT_PULLUP);
   pinMode(TARJETA3,INPUT_PULLUP);
   pinMode(TARJETA4,INPUT_PULLUP);
   pinMode(TARJETA5,INPUT_PULLUP);
   pinMode(TARJETA6,INPUT_PULLUP);
   pinMode(TARJETA7,INPUT_PULLUP);

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
  
 


}

void loop() {

  
  ActualizarMEF_TARJ1();
  ActualizarMEF_TARJ2();
  ActualizarMEF_TARJ3();
  ActualizarMEF_TARJ4();
  ActualizarMEF_TARJ5();
  ActualizarMEF_TARJ6();
  ActualizarMEF_TARJ7();

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
    eA_TARJETA7 = TARJETA1_S7;                // Establece estado inicial 
    tInicio_TARJ7 = tickRead();              // También inicia temporizacion  
}


void ActualizarMEF_TARJ1(void) {
    switch (eA_TARJETA1) {
        case TARJETA1_S1:

                state = true;                       //LED DE LA TARJETA1 PRENDIDO 
                tiraState(state,1);
                eA_TARJETA1 = TARJETA1_S2;          // Cambiar a otro estado
                tInicio_1 = millis();        // También inicia temporizacion
            
            break;
        case TARJETA1_S2:
            
            if (millis() - tInicio_1 > 500) {                 
                eA_TARJETA1 = TARJETA1_S1;                   // Cambiar a otro estado
                                                            // También inicia temporizacion 
                !state;                            //LED DE LA TARJETA1 APAGADO    
            }
            if(TARJETA1==0){
                  eA_TARJETA1 = TARJETA1_S3;                   // Cambiar a otro estado
                  //INCOMPLETO (SUMA PUNTO Y SONIDO)
                  modulo.playSpecified(5);
                  LED_TARJ1=1;                            //LED DE LA TARJETA1 PRENDIDO                                              //INCOMPLETO
              }
              if(TARJETA1==0 && MULTIBALL==1){
                  eA_TARJETA1 = TARJETA1_S4;                   // Cambiar a otro estado
                  //INCOMPLETO (SUMA PUNTO Y SONIDO)
                  LED_TARJ1=1;                            //LED DE LA TARJETA1 PRENDIDO                                              //INCOMPLETO
              }
            break;
        case TARJETA1_S3:
           
            if(BANCO_DE_TARJETAS==1){
                  eA_TARJETA1 = TARJETA1_S1;                   // Cambiar a otro estado
              }
            
            break;
                   
        case TARJETA1_S4:
            
            if(BANCO_DE_TARJETAS==1){
                  //SUMA PUNTUAJE ESPECIAL
                  eA_TARJETA1 = TARJETA1_S1;                   // Cambiar a otro estado
              }
            break;
        default:
            //Si algo modificó la variable estadoActual TARJETA1
            // a un estado no válido llevo la MEF a un 
            // lugar seguro, por ejemplo, la reinicio:
            InicializarMEF_TARJ1();
            
    }
}
