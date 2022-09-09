
#include <Arduino.h>           // los encabezados de las librerias deben estar declarados tal como se muestra en el sketch, 
#include "DYPlayerArduino.h"   // ya que de lo contrario no funcionaran los dos puertos series, unicamente el predeterminado. 
#include <Adafruit_NeoPixel.h> // Ademas al declarar el segundo puerto serie, hay que utilizar otro nombre para el objeto,   
//#include <Ticker.h>            // de lo contrario se estaria redeclarando el objeto predeterminado. 
                               
#define entrada1  53         
#define entrada2  51
#define entrada3  50
#define entrada4  49         
#define entrada5  48
#define entrada6  47
#define entrada7  46
#define salida   45

void InicializarMEF_1();
void ActualizarMEF();

typedef enum{ESTADO_1, ESTADO_2, ESTADO_3, ESTADO_4, ESTADO_5, ESTADO_6 } estadoMEF_t;

bool state = 1;
bool state_1 = 1;

uint8_t tInicio;
uint8_t tInicio_1;
uint8_t tInicio_2;
uint8_t tInicio_3;
uint8_t tInicio_4;
uint8_t tInicio_5;
uint8_t tInicio_6;
uint8_t tInicio_7;
bool flag_1 = 0;
bool flag_2 = 0;
uint8_t condicion = 0;
uint8_t bolaEntr = 0;

estadoMEF_t  estadoActual_1;
estadoMEF_t  estadoActual_2;
estadoMEF_t  estadoActual_3;
estadoMEF_t  estadoActual_4;
estadoMEF_t  estadoActual_5;
estadoMEF_t  estadoActual_6;
estadoMEF_t  estadoActual_7;

//primer parametro = cantidad de pixeles en la tira
//segundo parametro = pin digital del arduino
//tercer parametro = NEO_KHZ800 + NEO_GRB

Adafruit_NeoPixel   tira =    Adafruit_NeoPixel(300,42, NEO_GRB + NEO_KHZ800);


//void  sonido(uint8_t cantsonido, uint8_t nsonido1, uint8_t nsonido2);

  DY::Player player;            //objeto predeterminado
  DY::Player modulo(&Serial1);  //segundo objeto
  
//en los objetos es donde se establaecen los puertos series que se usaran en la comunicacion, por eso en el segundo objeto
// se agrega (&Serial2). El numero indica que puerto serie se utilizara. 





void setup() 
{
  attachInterrupt(digitalPinToInterrupt(2),llamadoInterr,RISING);
  
  pinMode(entrada1,INPUT_PULLUP);
  pinMode(entrada2,INPUT_PULLUP);
  pinMode(entrada3,INPUT_PULLUP);
  pinMode(entrada4,INPUT_PULLUP);
  pinMode(entrada5,INPUT_PULLUP);
  pinMode(entrada6,INPUT_PULLUP);
  pinMode(entrada7,INPUT_PULLUP);

  tira.begin();
  tira.show();

  player.begin();
  modulo.begin();

  player.setVolume(12);
  modulo.setVolume(14);
  player.playSpecified(17); 
  modulo.playSpecified(5);

  tira.setBrightness(10);

  InicializarMEF_1();
}

void loop() 
{
  ActualizarMEF_1();
  ActualizarMEF_2();
  ActualizarMEF_3();
  ActualizarMEF_4();
  ActualizarMEF_5();
  ActualizarMEF_6();
  
  if (flag_1 == 1 && flag_2 == 1) 
  {
    condicion==1;
    digitalWrite(salida,HIGH);
  }
  else
  {
    condicion==0;
  }
  tInicio = millis();

  
}

//*********** llamado a interrupcion **************

void llamadoInterr()
{
  player.playSpecified(17);
  
}

//************* tiras led *************************
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
//************ maquina de estados *****************

void InicializarMEF_1() 
{
  estadoActual_1 = ESTADO_1;
}



void ActualizarMEF_1() //tarjeta 1
{
  switch (estadoActual_1)
  {
    case ESTADO_1:
          
           if (millis() - tInicio_1 > 500) 
           {
              !state; // Actualizar salida en el estado
              tInicio_1 = millis();
           }
          tiraState(state,1);  
          
          if(entrada1==0) 
          {                                                       // Chequear condiciones de transición de estado
            estadoActual_1 = ESTADO_2; // Cambiar a otro estado
            modulo.playSpecified(5);

          }
    break;

    case ESTADO_2:
          
          state = true; // Actualizar salida en el estado
          tiraState(state,1);
          
          if(entrada3==0) 
          {                                                       // Chequear condiciones de transición de estado
            estadoActual_1 = ESTADO_1; // Cambiar a otro estado
            
          }
    break;

    default: InicializarMEF_1();
    break;
  }
}

void InicializarMEF_2() //tarjeta 2
{
  estadoActual_2 = ESTADO_1;
}



void ActualizarMEF_2() //tarjeta 2
{
  switch (estadoActual_2)
  {
    case ESTADO_1:
          
          if (millis() - tInicio_2 > 500) 
           {
              !state; // Actualizar salida en el estado
              tInicio_2 = millis();
           }
          tiraState(state,2);
          
          if(entrada1==0) 
          {                                                       // Chequear condiciones de transición de estado
            estadoActual_2 = ESTADO_2; // Cambiar a otro estado
            modulo.playSpecified(5);

          }
    break;

    case ESTADO_2:
          
          state = true; // Actualizar salida en el estado
          tiraState(state,2);
          
          if(entrada3==0) 
          {                                                       // Chequear condiciones de transición de estado
            estadoActual_2 = ESTADO_1; // Cambiar a otro estado
            
          }
    break;

    default: InicializarMEF_2();
    break;
  }
}


void InicializarMEF_3() //tarjeta 3
{
  estadoActual_3 = ESTADO_1;
}



void ActualizarMEF_3() //tarjeta 3
{
  switch (estadoActual_3)
  {
    case ESTADO_1:
          
          if (millis() - tInicio_3 > 500) 
           {
              !state; // Actualizar salida en el estado
              tInicio_3 = millis();
           }
          
          tiraState(state,3);
          
          if(entrada1==0) 
          {                                                       // Chequear condiciones de transición de estado
            estadoActual_3 = ESTADO_2; // Cambiar a otro estado
            modulo.playSpecified(7);

          }
    break;

    case ESTADO_2:
          
          state = true; // Actualizar salida en el estado

          tiraState(state,3);
          
          if(entrada3==0) 
          {                                                       // Chequear condiciones de transición de estado
            estadoActual_3 = ESTADO_1; // Cambiar a otro estado
            flag_1 = 1;
          }
    break;

    default: InicializarMEF_3();
    break;
  }
}




void InicializarMEF_4() //tarjeta 3
{
  estadoActual_4 = ESTADO_1;
}



void ActualizarMEF_4() //tarjeta 2
{
  switch (estadoActual_4)
  {
    case ESTADO_1:
          
          if (millis() - tInicio_4 > 500) 
           {
              !state; // Actualizar salida en el estado
              tInicio_4 = millis();
           }

          tiraState(state,4);
          
          if(entrada1==0) 
          {                                                       // Chequear condiciones de transición de estado
            estadoActual_4 = ESTADO_2; // Cambiar a otro estado
            modulo.playSpecified(5);

          }
    break;

    case ESTADO_2:
          
          state = true; // Actualizar salida en el estado

          tiraState(state,4);
          
          if(entrada6==0) 
          {                                                       // Chequear condiciones de transición de estado
            estadoActual_4 = ESTADO_1; // Cambiar a otro estado
            
          }
    break;

    default: InicializarMEF_4();
    break;
  }
}


void InicializarMEF_5() //tarjeta 3
{
  estadoActual_5 = ESTADO_1;
}



void ActualizarMEF_5() //tarjeta 2
{
  switch (estadoActual_5)
  {
    case ESTADO_1:
          
          if (millis() - tInicio_5 > 500) 
           {
              !state; // Actualizar salida en el estado
              tInicio_5 = millis();
           }
          tiraState(state,5);
          
          if(entrada1==0) 
          {                                                       // Chequear condiciones de transición de estado
            estadoActual_5 = ESTADO_2; // Cambiar a otro estado
            modulo.playSpecified(5);

          }
    break;

    case ESTADO_2:
          
          state = true; // Actualizar salida en el estado

          tiraState(state,5);
          
          if(entrada6==0) 
          {                                                       // Chequear condiciones de transición de estado
            estadoActual_5 = ESTADO_1; // Cambiar a otro estado
            
          }
    break;

    default: InicializarMEF_5();
    break;
  }
}

void InicializarMEF_6() //tarjeta 3
{
  estadoActual_6 = ESTADO_1;
}



void ActualizarMEF_6() //tarjeta 2
{
  switch (estadoActual_6)
  {
    case ESTADO_1:
          
          if (millis() - tInicio_6 > 500) 
           {
              !state; // Actualizar salida en el estado
              tInicio_6 = millis();
           }

          tiraState(state,6);
          
          if(entrada1==0) 
          {                                                       // Chequear condiciones de transición de estado
            estadoActual_6 = ESTADO_2; // Cambiar a otro estado
            modulo.playSpecified(5);
            digitalWrite(salida,HIGH);
          }
    break;

    case ESTADO_2:
          
          state = true; // Actualizar salida en el estado

          tiraState(state,6);
          
          if(entrada6==0) 
          {                                                       // Chequear condiciones de transición de estado
            estadoActual_6 = ESTADO_1; // Cambiar a otro estado
            
            flag_2 = 1;
          }
    break;

    default: InicializarMEF_6();
    break;
  }
}

void InicializarMEF_7() //tarjeta 3
{
  estadoActual_7 = ESTADO_1;
}



void ActualizarMEF_7() //tarjeta 2
{
  switch (estadoActual_7)
  {
    case ESTADO_1:
          
          if(millis() - tInicio_7 > 500)
          {
            tiraState(state_1,7);
          }
          
          if(condicion == 1) 
          {                                                       // Chequear condiciones de transición de estado
            estadoActual_7 = ESTADO_2; // Cambiar a otro estado
            modulo.playSpecified(8);

          }
    break;

    case ESTADO_2:

          !state_1;
          tiraState(state_1,7);
          
          
          if(entrada7 == 1) 
          {                                                       // Chequear condiciones de transición de estado
            modulo.playSpecified(8);
            bolaEntr++;
            estadoActual_7 = ESTADO_3; // Cambiar a otro estado
            
          }
    break;

    case ESTADO_3:
         
         if (entrada7 == 1)
         {
            modulo.playSpecified(8);
            bolaEntr++;
         }

          if (bolaEntr == 3)
          {
            
            digitalWrite(salida,HIGH);
            estadoActual_7 = ESTADO_1; 
          }

   
        
    default: InicializarMEF_6();
    break;
  }
}
