#include "DYPlayerArduino.h"
#include <Adafruit_NeoPixel.h>
//#include <rp2040_pio.h>
#include <Arduino.h>
//#include "DYPlayerArduino.h"

#define tarjeta_1   53         
#define tarjeta_2   51
#define tarjeta_3   49

#define pixel_1     1         
#define pixel_2     2
#define pixel_3     3

#define LedOn_1     50
#define LedOn_2     50
#define LedOn_3     50

#define LedOff_2    50
#define LedOff_1    50
#define LedOff_3    50

typedef enum{PrendePixel, ApagaPixel, SoloRuido, ESTADO_4, ESTADO_5, ESTADO_6 } estadoMEF_t;     //se crea un nuevo tipo de dato llamado estadoMEF_t
                                                                                                //que cada variable declarada con este tipo de dato                                                                                                 
                                                                                                //puede unicamente valer lo que se encuentra dentro 
                                                                                                //de las llaves

struct variablesMEFS                      //se determina una tipo de dato de estructura de datos, con las variables 
{                                         //a utilizar, donde cada "renglon" de ella sera un valor que llamara la MEF 
  unsigned long tInicio;
  uint16_t numpixel;
  uint8_t tarjeta;    
  uint8_t estado;
  uint8_t pixelOn;
  uint8_t pixelOff;       
  estadoMEF_t  estadoActual;
};



struct variablesMEFS MEF1, MEF2, MEF3;    //se crean variables de tipo estructura, en la que 
                                          //cada una sera cargada con los datos correspondientes a cada tarjeta,
                                          //y sera utilizada por la funcion: actualizarMEF();



struct variablesMEFS *indice;             //se declara el puntero que utilizara la funcion actualizarMEF(); para 
                                          //invocar cada dato de la estructura de datos.


//primer parametro = cantidad de pixeles en la tira
//segundo parametro = pin digital del arduino
//tercer parametro = NEO_KHZ800 + NEO_GRB

Adafruit_NeoPixel tira=  Adafruit_NeoPixel(300,42, NEO_RGB + NEO_KHZ800);

DY::Player player;              //objeto predeterminado
DY::Player modulo(&Serial1);    //segundo objeto

//en los objetos es donde se establaecen los puertos series que se usaran en la comunicacion, por eso en el segundo objeto
// se agrega (&Serial2). El numero indica que puerto serie se utilizara.

void setup() 
{
  attachInterrupt(digitalPinToInterrupt(2),llamadoInterr,RISING);
  
  player.begin();
  modulo.begin();
  
  
  pinMode(tarjeta_1,INPUT_PULLUP);
  pinMode(tarjeta_2,INPUT_PULLUP);
  pinMode(tarjeta_3,INPUT_PULLUP);

  tira.begin();
  tira.show();

  tira.setBrightness(10);

 

  //player.stop();
    
  player.setVolume(20);
  modulo.setVolume(20);
  modulo.playSpecified(5);
  player.playSpecified(17);
  

  mifuncion(&MEF1, tarjeta_1, pixel_1, LedOn_1, LedOff_1);
 
  mifuncion(&MEF2, tarjeta_2, pixel_2, LedOn_2, LedOff_2 );

  mifuncion(&MEF2, tarjeta_3, pixel_3, LedOn_3, LedOff_3 );
  
  inicializarMEF(&MEF1);
  inicializarMEF(&MEF2);
  inicializarMEF(&MEF3);
  
}

void loop() 
{
   
   actualizarMEFGen();


   
   actualizarMEF(&MEF1);
   actualizarMEF(&MEF2);  
   actualizarMEF(&MEF3);  

}

/*****************************************************************************************/
/******************** inicializacion de maquinas de estado *******************************/ 
/*****************************************************************************************/  

void inicializarMEF(struct variablesMEFS *indice)
{
  indice->estadoActual = PrendePixel;
  indice->tInicio = millis();
}



/*****************************************************************************************/
/******************** actualizacion de maquinas de estado *******************************/ 
/*****************************************************************************************/ 



void actualizarMEF(struct variablesMEFS *indice)
{
  switch(indice->estadoActual)
  {
    case PrendePixel:

         if(digitalRead(indice->tarjeta)==0)
          {
            tira.setPixelColor(indice->numpixel,255,255,255);
            tira.show();
            modulo.playSpecified(4);
            indice->estadoActual = SoloRuido;
          }

          

          if(millis() - indice->tInicio > indice->pixelOn)
          {
            
            tira.setPixelColor(indice->numpixel,255,255,255);
            tira.show();
            indice->tInicio = millis();
            indice->estadoActual = ApagaPixel;         
          }

        
    break;

    case ApagaPixel:

         if(digitalRead(indice->tarjeta)==0)
          {
            tira.setPixelColor(indice->numpixel,255,255,255);
            tira.show();
            modulo.playSpecified(4);
            indice->estadoActual = SoloRuido;
          }
            

          if(millis() - indice->tInicio > indice->pixelOff)
          {
            
            tira.setPixelColor(indice-> numpixel,0,0,0);
            tira.show();
            indice->tInicio = millis();
            indice->estadoActual = PrendePixel;         
          }

    break;
  

    case SoloRuido:
          
          /*if(digitalRead(indice->tarjeta)==0)
          {
            
            modulo.playSpecified(4);
            
          }*/
          
    break;

    default:
            inicializarMEF(&MEF1);
            inicializarMEF(&MEF2);      
    break;
  }
}


void mifuncion(struct variablesMEFS *indice, char numtar, uint16_t pixel, uint16_t valorOn, uint16_t valorOff)
{
    indice->tarjeta   = numtar;
    indice->numpixel  = pixel;
    indice->pixelOn   = valorOn;
    indice->pixelOff  = valorOff;
    indice->tInicio   = millis();
}


void llamadoInterr()
{
  player.playSpecified(17);
}



/*******************************************Maquina de Estados general para modulizar************************************/

void actualizarMEFGen()
{
  
}
