#include "DYPlayerArduino.h"
#include <Adafruit_NeoPixel.h>
#include <Servo.h> 

#define sensor_start    39
#define sensor_over    39
#define sensor_over2    39
#define sensor_over3    39
#define pulsador_start    39

#define sensorA_1    39
#define sensorA_2   39
#define sensorA_3    39
#define sensorA_4    39

//#define sensor_gaming_1    39
//#define sensor_gaming_2    39
//#define sensor_gaming_3    39

typedef enum{ Game0, Game1, Game2, Game3, Game4, Game5, Game6 } estadoMEF_t;

Servo servo_juego;

estadoMEF_t estadoJuego;

//no va 333333333333333333333333333333333333333333333333333333333333333333
Adafruit_NeoPixel tira=  Adafruit_NeoPixel(300,42, NEO_RGB + NEO_KHZ800);

//DY::Player player;              //objeto predeterminado
DY::Player modulo;//(&Serial1);    //segundo objeto

uint16_t numpixel;
bool jugando;
int vidas;
bool gameover;
//33333333333333333333333333333333333333333333333333333333333333

void setup() {
  //no va 33333333333333333333333333333
  tira.begin();
  tira.show();

  tira.setBrightness(10);

  

  //player.stop();
    
  //player.setVolume(20);
  modulo.setVolume(20);
  modulo.playSpecified(5);
  //333333333333333333333333333333333333333
  
  pinMode(pulsador_start,INPUT_PULLUP);
  pinMode(sensor_start,INPUT);
  pinMode(sensor_over,INPUT);
  pinMode(sensor_over2,INPUT);
  pinMode(sensor_over3,INPUT);

  pinMode(sensorA_1,INPUT);
  pinMode(sensorA_2,INPUT);
  pinMode(sensorA_3,INPUT);
  pinMode(sensorA_4,INPUT);
//
//  pinMode(sensor_gaming_1,INPUT);
//  pinMode(sensor_gaming_2,INPUT);
//  pinMode(sensor_gaming_3,INPUT);

  inicializarMEF_Juego();
}

void loop() {
  actualizarMEF_Juego();

}


// maquinas de estados

void inicializarMEF_Juego(){
  
  estadoJuego = Game0;
  
}

void actualizarMEF_Juego(){
  
  switch(estadoJuego)
  {
    case Game0:
    if(pulsador_start == 1){
       modulo.playSpecified(6);
       tira.setPixelColor(numpixel,255,255,255);
       tira.show();
          
       vidas = 4;
       gameover = 0;
       jugando = 0;
       estadoJuego = Game1;
       servo_juego.write(180);
    }

    break;
    
    case Game1:  
       if(sensor_start == 1){    
        estadoJuego = Game2;
        servo_juego.write(0);
       }
         
        
    break;

    case Game2:
        if(sensor_start == 0){
        modulo.playSpecified(6);
        tira.setPixelColor(numpixel,255,255,255);
        tira.show();
            
        estadoJuego = Game3;
       }
         
    break;

    case Game3:
        if(sensorA_1 == 1 || sensorA_2 == 1 || sensorA_3 == 1 || sensorA_4 == 1){
          jugando = 1;
          modulo.playSpecified(6);
          tira.setPixelColor(numpixel,255,255,255);
          tira.show();
          estadoJuego = Game4;
        }
       
    break;
    
    case Game4:
         if(sensor_over2 == 1){
          modulo.playSpecified(6);
          tira.setPixelColor(numpixel,255,255,255);
          tira.show();
          
          estadoJuego = Game5;
         }
         if(sensor_over3 == 1){
          modulo.playSpecified(6);
          tira.setPixelColor(numpixel,255,255,255);
          tira.show();
          
          estadoJuego = Game5;
         }

    break;
    case Game5:
    if(sensor_over == 1){
          modulo.playSpecified(6);
          tira.setPixelColor(numpixel,255,255,255);
          tira.show();

          /* inicializarMEF(&MEF1);                     
          inicializarMEF(&MEF2);
          inicializarMEF(&MEF3);
          inicializarMEF(&MEF4);
          inicializarMEF(&MEF5);
          inicializarMEF(&MEF6);
          inicializarMEF_multi();
          */
          
          jugando = 0;
          vidas--;
          estadoJuego = Game6;
         }
    break;
    case Game6:

        if(vidas > 0){
          servo_juego.write(180);                     // mueve la pelota para tirar una nueva
          estadoJuego = Game1;
        }
        else{
          gameover = 1;
         // inicializa puntos
          
          
          inicializarMEF_Juego();
         // estadoJuego = Game0;
        }
    break;
  }
}
