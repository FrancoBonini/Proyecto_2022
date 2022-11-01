#include "DYPlayerArduino.h"
#include <Adafruit_NeoPixel.h>
#include <Servo.h> 


#define PINSERVO  5
#define PULSOMIN  850
#define PULSOMAX  2150

#define tarjeta_1   53         
#define tarjeta_2   51
#define tarjeta_3   49
#define tarjeta_4   47
#define tarjeta_5   45
#define tarjeta_6   43
#define TARJETA7   41
#define sensor_multiball    39

#define pixel_1     1         
#define pixel_2     2
#define pixel_3     3
#define pixel_4     4         
#define pixel_5     5         
#define pixel_6     6 
#define pixel_A_1     6
#define pixel_A_2     6
#define pixel_A_3     6
#define pixel_A_4     6
#define pixel_gaming_1     6
#define pixel_gaming_2     6
#define pixel_gaming_3     6        

#define LedOn_1     50
#define LedOn_2     50
#define LedOn_3     50
#define LedOn_4     50
#define LedOn_5     50
#define LedOn_6     50
#define LedOn_A_1     50
#define LedOn_A_2     50
#define LedOn_A_3     50
#define LedOn_A_4     50
#define LedOn_gaming_1     50
#define LedOn_gaming_2     50
#define LedOn_gaming_3     50

#define LedOff_1    50
#define LedOff_2    50
#define LedOff_3    50
#define LedOff_4    50
#define LedOff_5    50
#define LedOff_6    50
#define LedOff_A_1    50
#define LedOff_A_2    50
#define LedOff_A_3    50
#define LedOff_A_4    50
#define LedOff_gaming_1    50
#define LedOff_gaming_2    50
#define LedOff_gaming_3    50

#define sensorA_1    39
#define sensorA_2   39
#define sensorA_3    39
#define sensorA_4    39

#define sensor_gaming_1    39
#define sensor_gaming_2    39
#define sensor_gaming_3    39

#define sensor_start    39
#define sensor_over    39
#define sensor_over2    39
#define sensor_over3    39
#define pulsador_start    39


typedef enum{PrendePixel, ApagaPixel,PrendePixel_v2, ApagaPixel_v2, SoloRuido, PuertaAbierta, PuertaCerrada, MultiBallEspera, MultiBallActivo,
Game0, Game1, Game2, Game3, Game4, Game5, Game6,
TARJETA7_S1, TARJETA7_S2, TARJETA7_S3, TARJETA7_S4, TARJETA7_S5, TARJETA7_S6, TARJETA7_S7,
ESTADO_5 } estadoMEF_t;     //se crea un nuevo tipo de dato llamado estadoMEF_t
                                                                                                //que cada variable declarada con este tipo de dato                                                                                                 
                                                                                                //puede unicamente valer lo que se encuentra dentro 
                                                                                                //de las llaves

estadoMEF_t estadoJuego;

estadoMEF_t  eA_TARJETA7;     //ESTADOACTUAL_TARJETA Nª7
uint8_t tInicio_TARJ7;
/*****************************************************************************************/
/******************** Declaracion de estructuras *****************************************/ 
/*****************************************************************************************/




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

struct variablesMEFS_v2                      //se determina una tipo de dato de estructura de datos, con las variables 
{                                         //a utilizar, donde cada "renglon" de ella sera un valor que llamara la MEF 
  unsigned long tInicio_v2;
  uint16_t numpixel_v2;
  uint8_t sensor_v2;    
  uint8_t estado_v2;
  uint8_t pixelOn_v2;
  uint8_t pixelOff_v2;       
  estadoMEF_t  estadoActual_v2;
};

//struct variablesMulti                      //se determina una tipo de dato de estructura de datos, con las variables 
//{                                         //a utilizar, donde cada "renglon" de ella sera un valor que llamara la MEF 
//  unsigned long tInicio;
//  uint16_t numpixel;
//  uint8_t tarjeta;    
//  uint8_t estado;
//  uint8_t pixelOn;
//  uint8_t pixelOff;       
//  estadoMEF_t  estadoActual;
//};





/*****************************************************************************************/
/******************** Creacion de cada estructura ****************************************/ 
/*****************************************************************************************/



struct variablesMEFS MEF1, MEF2, MEF3, MEF4, MEF5, MEF6;    //se crean variables de tipo estructura, en la que 
                                          //cada una sera cargada con los datos correspondientes a cada tarjeta,
                                          //y sera utilizada por la funcion: actualizarMEF();
struct variablesMEFS_v2 MEF_A_1, MEF_A_2, MEF_A_3, MEF_A_4, MEF_G_1, MEF_G_2, MEF_G_3;
//struct variablesMulti MULTI1;


/*****************************************************************************************/
/******************** Declaracion de punteros ********************************************/ 
/*****************************************************************************************/


struct variablesMEFS *indice1;             //se declara el puntero que utilizara la funcion actualizarMEF(); para 
                                          //invocar cada dato de la estructura de datos.
struct variablesMEFS_v2 *indice2;


/*****************************************************************************************/
/******************** Declaracion de variables *******************************************/ 
/*****************************************************************************************/

estadoMEF_t estadoMultiball;

uint8_t bandera = 0;
uint8_t banderaMultiball = 0;
bool banderaHabilitacion = 1;
bool  banderaMultiplicacion = 0;
bool MULTIBALL = 0;
unsigned long tInicio_1;

/*****************************************************************************************/
/******************** Creacion de objetos ************************************************/ 
/*****************************************************************************************/


//primer parametro = cantidad de pixeles en la tira
//segundo parametro = pin digital del arduino
//tercer parametro = NEO_KHZ800 + NEO_GRB

Adafruit_NeoPixel tira=  Adafruit_NeoPixel(300,42, NEO_RGB + NEO_KHZ800);

//DY::Player player;              //objeto predeterminado
DY::Player modulo;//(&Serial1);    //segundo objeto

Servo servo;
Servo servo_juego;

uint16_t numero_led;
bool jugando;
int vidas;
bool gameover;

int puntaje;
bool state_TARJ7 = 1;
//en los objetos es donde se establaecen los puertos series que se usaran en la comunicacion, por eso en el segundo objeto
// se agrega (&Serial2). El numero indica que puerto serie se utilizara.



/*****************************************************************************************/
/*****************************************************************************************/ 
/*****************************************************************************************/

void setup() 
{
  //attachInterrupt(digitalPinToInterrupt(2),llamadoInterr,RISING);
  
 // player.begin();
  modulo.begin();
  
  
  pinMode(tarjeta_1,INPUT_PULLUP);
  pinMode(tarjeta_2,INPUT_PULLUP);
  pinMode(tarjeta_3,INPUT_PULLUP);
  pinMode(tarjeta_4,INPUT_PULLUP);
  pinMode(tarjeta_5,INPUT_PULLUP);
  pinMode(tarjeta_6,INPUT_PULLUP);
  pinMode(TARJETA7,INPUT_PULLUP);
  pinMode(sensor_multiball,INPUT);

  pinMode(sensorA_1,INPUT);
  pinMode(sensorA_2,INPUT);
  pinMode(sensorA_3,INPUT);
  pinMode(sensorA_4,INPUT);

  pinMode(sensor_gaming_1,INPUT);
  pinMode(sensor_gaming_2,INPUT);
  pinMode(sensor_gaming_3,INPUT);

  pinMode(pulsador_start,INPUT_PULLUP);
  pinMode(sensor_start,INPUT);
  pinMode(sensor_over,INPUT);
  pinMode(sensor_over2,INPUT);
  pinMode(sensor_over3,INPUT);

  tira.begin();
  tira.show();

  tira.setBrightness(10);

  servo.attach(PINSERVO,PULSOMIN,PULSOMAX);

  //player.stop();
    
  //player.setVolume(20);
  modulo.setVolume(20);
  modulo.playSpecified(5);
  //player.playSpecified(17);
  

  mifuncion(&MEF1, tarjeta_1, pixel_1, LedOn_1, LedOff_1);
 
  mifuncion(&MEF2, tarjeta_2, pixel_2, LedOn_2, LedOff_2 );

  mifuncion(&MEF3, tarjeta_3, pixel_3, LedOn_3, LedOff_3 );

  mifuncion(&MEF4, tarjeta_4, pixel_4, LedOn_4, LedOff_4 );

  mifuncion(&MEF5, tarjeta_5, pixel_5, LedOn_5, LedOff_5 );

  mifuncion(&MEF6, tarjeta_6, pixel_6, LedOn_6, LedOff_6 );

  mifuncion_v2(&MEF_A_1, sensorA_1, pixel_A_1, LedOn_A_1, LedOff_A_1 );

  mifuncion_v2(&MEF_A_2, sensorA_2, pixel_A_2, LedOn_A_2, LedOff_A_2 );

  mifuncion_v2(&MEF_A_3, sensorA_3, pixel_A_3, LedOn_A_3, LedOff_A_3 );

  mifuncion_v2(&MEF_A_4, sensorA_3, pixel_A_4, LedOn_A_4, LedOff_A_4 );

  mifuncion_v2(&MEF_G_1, sensor_gaming_1, pixel_gaming_1, LedOn_gaming_1, LedOff_gaming_1 );

  mifuncion_v2(&MEF_G_2, sensor_gaming_2, pixel_gaming_2, LedOn_gaming_2, LedOff_gaming_2 );

  mifuncion_v2(&MEF_G_3, sensor_gaming_3, pixel_gaming_3, LedOn_gaming_3, LedOff_gaming_3 );
  
  
  inicializarMEF(&MEF1);
  inicializarMEF(&MEF2);
  inicializarMEF(&MEF3);
  inicializarMEF(&MEF4);
  inicializarMEF(&MEF5);
  inicializarMEF(&MEF6);

  InicializarMEF_TARJ7();
  
  inicializarMEF_multi();

  inicializarMEF_v2(&MEF_A_1);
  inicializarMEF_v2(&MEF_A_2);
  inicializarMEF_v2(&MEF_A_3);
  inicializarMEF_v2(&MEF_A_4);
  inicializarMEF_v2(&MEF_G_1);
  inicializarMEF_v2(&MEF_G_2);
  inicializarMEF_v2(&MEF_G_3);

  inicializarMEF_Juego();
}

void loop() 
{
   if(banderaHabilitacion == 1)
   {
      actualizarMEFMultiBall();   
   }

    else
    {
      if(millis() - tInicio_1 > 6000)
      {
        banderaHabilitacion =  1;
      }
    }

   actualizarMEF_Juego();
   
   actualizarMEF(&MEF1);
   actualizarMEF(&MEF2);  
   actualizarMEF(&MEF3);
   actualizarMEF(&MEF4);
   actualizarMEF(&MEF5);  
   actualizarMEF(&MEF6);

   ActualizarMEF_TARJ7();

   actualizarMEF_v2(&MEF_A_1);
   actualizarMEF_v2(&MEF_A_2);
   actualizarMEF_v2(&MEF_A_3);
   actualizarMEF_v2(&MEF_A_4);
   actualizarMEF_v2(&MEF_G_1);
   actualizarMEF_v2(&MEF_G_2);
   actualizarMEF_v2(&MEF_G_3);

   
}

/*****************************************************************************************/
/******************** inicializacion de maquinas de estado *******************************/ 
/*****************************************************************************************/  

void inicializarMEF_Juego(){
  
  estadoJuego = Game0;
  
}

void InicializarMEF_TARJ7() {
    eA_TARJETA7 = TARJETA7_S2;                // Establece estado inicial 
    //tInicio_TARJ7 = millis();
    //tInicio_TARJ7 = tickRead();              // También inicia temporizacion  
}

void inicializarMEF(struct variablesMEFS *indice1)
{
  indice1->estadoActual = PrendePixel;
  indice1->tInicio = millis();
  
}

void inicializarMEF_v2(struct variablesMEFS_v2 *indice2)
{
  indice2->estadoActual_v2 = PrendePixel_v2;
  //indice2->tInicio = millis();
  
}

void inicializarMEF_multi()
{
  estadoMultiball = PuertaAbierta;
  
}


/*****************************************************************************************/
/******************** actualizacion de maquinas de estado *******************************/ 
/*****************************************************************************************/ 
//*****************************Funcionamiento del juego(gameover)***********************************
void actualizarMEF_Juego(){
  
  switch(estadoJuego)
  {
    case Game0:
    if(digitalRead(pulsador_start) == 1){
       modulo.playSpecified(6);
       tira.setPixelColor(numero_led,255,255,255);
       tira.show();
          
       vidas = 3;
       gameover = 0;
       jugando = 0;
       estadoJuego = Game1;
       servo_juego.write(180);
    }

    break;
    
    case Game1:  
       if(digitalRead(sensor_start) == 1){    
        estadoJuego = Game2;
        servo_juego.write(0);
       }
         
        
    break;

    case Game2:
        if(digitalRead(sensor_start) == 0){
        modulo.playSpecified(6);
        tira.setPixelColor(numero_led,255,255,255);
        tira.show();
            
        estadoJuego = Game3;
       }
         
    break;

    case Game3:
        if(digitalRead(sensorA_1) == 1 || digitalRead(sensorA_2) == 1 || digitalRead(sensorA_3) == 1 || digitalRead(sensorA_4) == 1){
          jugando = 1;
          modulo.playSpecified(6);
          tira.setPixelColor(numero_led,255,255,255);
          tira.show();
          estadoJuego = Game4;
        }
       
    break;
    
    case Game4:
         if(digitalRead(sensor_over2) == 1){
          modulo.playSpecified(6);
          tira.setPixelColor(numero_led,255,255,255);
          tira.show();
          
          estadoJuego = Game5;
         }
         if(digitalRead(sensor_over3) == 1){
          modulo.playSpecified(6);
          tira.setPixelColor(numero_led,255,255,255);
          tira.show();
          
          estadoJuego = Game5;
         }

         if(digitalRead(sensor_over) == 1){
          modulo.playSpecified(6);
          tira.setPixelColor(numero_led,255,255,255);
          tira.show();

          inicializarMEF(&MEF1);
          inicializarMEF(&MEF2);
          inicializarMEF(&MEF3);
          inicializarMEF(&MEF4);
          inicializarMEF(&MEF5);
          inicializarMEF(&MEF6);
        
          InicializarMEF_TARJ7();
          
          inicializarMEF_multi();
        
          inicializarMEF_v2(&MEF_A_1);
          inicializarMEF_v2(&MEF_A_2);
          inicializarMEF_v2(&MEF_A_3);
          inicializarMEF_v2(&MEF_A_4);
          inicializarMEF_v2(&MEF_G_1);
          inicializarMEF_v2(&MEF_G_2);
          inicializarMEF_v2(&MEF_G_3);         
          
          jugando = 0;
          vidas--;
          estadoJuego = Game6;
         }

    break;
    case Game5:
    if(digitalRead(sensor_over) == 1){
          modulo.playSpecified(6);
          tira.setPixelColor(numero_led,255,255,255);
          tira.show();

          inicializarMEF(&MEF1);
          inicializarMEF(&MEF2);
          inicializarMEF(&MEF3);
          inicializarMEF(&MEF4);
          inicializarMEF(&MEF5);
          inicializarMEF(&MEF6);
        
          InicializarMEF_TARJ7();
          
          inicializarMEF_multi();
        
          inicializarMEF_v2(&MEF_A_1);
          inicializarMEF_v2(&MEF_A_2);
          inicializarMEF_v2(&MEF_A_3);
          inicializarMEF_v2(&MEF_A_4);
          inicializarMEF_v2(&MEF_G_1);
          inicializarMEF_v2(&MEF_G_2);
          inicializarMEF_v2(&MEF_G_3);         
          
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
          
          
          inicializarMEF_Juego();                   // estadoJuego = Game0;
         
        }
    break;
  }
}

//*****************************TARJETA 7 ESPECIAL***********************************
void ActualizarMEF_TARJ7(void) {
    switch (eA_TARJETA7) {
//        case TARJETA7_S1:
//
////                tira.setPixelColor(numero_led,255,255,255);     
////                tira.show();                              //LED DE LA TARJETA7 PRENDIDO                         
////                eA_TARJETA7 = TARJETA7_S2;               // Cambiar a otro estado
////                tInicio_TARJ7 = millis();               // También inicia temporizacion
//            
//            break;
        case TARJETA7_S2:
            
//            if (millis() - tInicio_TARJ7 > 500) {                 
//                eA_TARJETA7 = TARJETA7_S1;                  // Cambiar a otro estado                                                           
//                tira.setPixelColor(numero_led,0,0,0);     
//                tira.show();                                     //LED DE LA TARJETA7 APAGADO    
//            }
            if(digitalRead(TARJETA7)==0 && MULTIBALL==1){
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
            else if(digitalRead(TARJETA7)==0){     
                  puntaje +=100;                         //suma puntos
                  modulo.playSpecified(5);              //sonido
                 // eA_TARJETA7 = TARJETA7_S2;           // Cambiar a otro estado
              }             
            break;
        case TARJETA7_S3:

//          if (millis() - tInicio_TARJ7 > 500) {                                                                           
//                tira.setPixelColor(numero_led,0,0,0);     
//                tira.show();                                   //LED DE LA TARJETA7 apagado
//                tInicio_TARJ7 = millis();                      // También inicia temporizacion
//            }
           
           if(digitalRead(TARJETA7)==0 && MULTIBALL==1){
                  puntaje +=30000;                             //suma 30k puntos
                  modulo.playSpecified(5);                    //sonido
//                  tira.setPixelColor(numero_led,255,255,255);     
//                  tira.show();                              //LED DE LA TARJETA7 PRENDIDO   
                  
                  tira.setPixelColor(numero_led,255,255,255);     
                  tira.show();                           //LED DE 30k PRENDIDO
                  
                  eA_TARJETA7 = TARJETA7_S4;           //Cambiar a otro estado  
                 // tInicio_TARJ7 = millis();           // También inicia temporizacion                                       
              }
            
            break;
                   
        case TARJETA7_S4:

//            if (millis() - tInicio_TARJ7 > 500) {                                                                           
//                tira.setPixelColor(numero_led,0,0,0);     
//                  tira.show();                                     //LED DE LA TARJETA7 apagado
//  
//                tInicio_TARJ7 = millis();                        // También inicia temporizacion
//            }
           
           if(digitalRead(TARJETA7)==0 && MULTIBALL==1){
                  puntaje +=50000;                             //suma 50k puntos
                  modulo.playSpecified(5);                    //sonido
//                  tira.setPixelColor(numero_led,255,255,255);     
//                  tira.show();                              //LED DE LA TARJETA7 PRENDIDO   
                  
                  tira.setPixelColor(numero_led,255,255,255);     
                  tira.show();                           //LED DE 50k PRENDIDO

                  eA_TARJETA7 = TARJETA7_S5;           //Cambiar a otro estado  
//                  tInicio_TARJ7 = millis();           // También inicia temporizacion                                       
              }   
            
            break;
            case TARJETA7_S5:

//            if (millis() - tInicio_TARJ7 > 500) {                                                                           
//                tira.setPixelColor(numero_led,0,0,0);     
//                tira.show();                                     //LED DE LA TARJETA7 apagado
//                
//                tInicio_TARJ7 = millis();                      // También inicia temporizacion
//            }
           
           if(digitalRead(TARJETA7)==0 && MULTIBALL==1){
                  vidas++;
                  modulo.playSpecified(5);                    //sonido
//                  tira.setPixelColor(numero_led,255,255,255);     
//                  tira.show();                              //LED DE LA TARJETA7 PRENDIDO   
                                   
                  tira.setPixelColor(numero_led,255,255,255);     
                  tira.show();                           //LED DE EXTRABALL PRENDIDO
                                     
                  eA_TARJETA7 = TARJETA7_S6;           //Cambiar a otro estado  
//                  tInicio_TARJ7 = millis();           // También inicia temporizacion                                       
              }   
            
            break;
            case TARJETA7_S6:

//            if (millis() - tInicio_TARJ7 > 500) {                                                                           
//                tira.setPixelColor(numero_led,0,0,0);     
//                tira.show();                                  //LED DE LA TARJETA7 apagado 
//                                    
//                tInicio_TARJ7 = millis();                     // También inicia temporizacion
//            }
           
           if(digitalRead(TARJETA7)==0 && MULTIBALL==1){
                  puntaje +=70000;                             //suma 70k puntos
                  modulo.playSpecified(5);                    //sonido
//                  tira.setPixelColor(numero_led,255,255,255);     
//                  tira.show();                              //LED DE LA TARJETA7 PRENDIDO   
                  
                  tira.setPixelColor(numero_led,255,255,255);     
                  tira.show();                           //LED DE 70K PRENDIDO
                  
                  eA_TARJETA7 = TARJETA7_S7;           //Cambiar a otro estado  
//                  tInicio_TARJ7 = millis();           // También inicia temporizacion                                       
              }   
            
            break;
            case TARJETA7_S7:

//            if (millis() - tInicio_TARJ7 > 500) {                                                                           
//                tira.setPixelColor(numero_led,0,0,0);     
//                tira.show();                                     //LED DE LA TARJETA7 apagado
//                                      
//                tInicio_TARJ7 = millis();                // También inicia temporizacion
//            }
           
           if(digitalRead(TARJETA7)==0 && MULTIBALL==1){
                  puntaje +=100000;                       //suma PUNTAJE ESPECIAL
                  modulo.playSpecified(5);                  //sonido
//                  tira.setPixelColor(numero_led,255,255,255);     
//                  tira.show();                             //LED DE LA TARJETA7 PRENDIDO   
                  
                  tira.setPixelColor(numero_led,255,255,255);     
                  tira.show();                           //LED DE SPECIAL POINT PRENDIDO
                  
         //       eA_TARJETA7 = TARJETA7_S7;           //Cambiar a otro estado  
//                  tInicio_TARJ7 = millis();           // También inicia temporizacion                                       
              }   
            
            break;
        default:
            //Si algo modificó la variable estadoActual TARJETA1
            // a un estado no válido llevo la MEF a un 
            // lugar seguro, por ejemplo, la reinicio:
            InicializarMEF_TARJ7();
            
    }
}

void actualizarMEF(struct variablesMEFS *indice1)
{
  switch(indice1->estadoActual)
  {
    case PrendePixel:

         if(digitalRead(indice1->tarjeta)==0)
          {
            tira.setPixelColor(indice1->numpixel,255,255,255);
            tira.show();
            modulo.playSpecified(4);
            bandera++;
            indice1->estadoActual = SoloRuido;
          }

          

          if(millis() - indice1->tInicio > indice1->pixelOn)
          {
            
            tira.setPixelColor(indice1->numpixel,255,255,255);
            tira.show();
            indice1->tInicio = millis();
            indice1->estadoActual = ApagaPixel;         
          }

        
    break;

    case ApagaPixel:

         if(digitalRead(indice1->tarjeta)==0)
          {
            tira.setPixelColor(indice1->numpixel,255,255,255);
            tira.show();
            modulo.playSpecified(4);
            bandera++;
            indice1->estadoActual = SoloRuido;
          }
            

          if(millis() - indice1->tInicio > indice1->pixelOff)
          {
            
            tira.setPixelColor(indice1-> numpixel,0,0,0);
            tira.show();
            indice1->tInicio = millis();
            indice1->estadoActual = PrendePixel;         
          }

    break;
  

    case SoloRuido:
          
          /*if(digitalRead(indice1->tarjeta)==0)
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





void actualizarMEF_v2(struct variablesMEFS_v2 *indice2)
{
  switch(indice2->estadoActual_v2)
  {
    case PrendePixel_v2:

         if(digitalRead(indice2->sensor_v2)==0)
          {
            tira.setPixelColor(indice2->numpixel_v2,255,255,255);
            tira.show();
            modulo.playSpecified(4);
            //bandera++;
            indice2->estadoActual_v2 = ApagaPixel_v2;
          }
          else
          {
            tira.setPixelColor(indice2->numpixel_v2,0,0,0);
            tira.show();
            //modulo.playSpecified(4);
            //bandera++;
            indice2->estadoActual_v2 = PrendePixel_v2;
          }

          

//          if(millis() - indice1->tInicio > indice1->pixelOn)
//          {
//            
//            tira.setPixelColor(indice1->numpixel,255,255,255);
//            tira.show();
//            indice2->tInicio = millis();
//            indice2->estadoActual = ApagaPixel;         
//          }

        
    break;

    case ApagaPixel_v2:

//         if(digitalRead(indice2->sensor)==1)
//          {
//            tira.setPixelColor(indice2->numpixel,0,0,0);
//            tira.show();
//            modulo.playSpecified(4);
//            //bandera++;
//           // indice2->estadoActual = SoloRuido;
//          }
            

//          if(millis() - indice2->tInicio > indice2->pixelOff)
//          {
//            
//            tira.setPixelColor(indice2-> numpixel,0,0,0);
//            tira.show();
//            indice2->tInicio = millis();
//            indice2->estadoActual = PrendePixel;         
//          }

    break;
  

//    case SoloRuido_v2:
//          
//          /*if(digitalRead(indice1->tarjeta)==0)
//          {
//            
//            modulo.playSpecified(4);
//            
//          }*/
//          
//    break;

    default:
            inicializarMEF_v2(&MEF_A_1);
            inicializarMEF_v2(&MEF_A_2);      
    break;
  }
}






/*******************************************Maquina de Estados general para modulizar************************************/

void actualizarMEFMultiBall()
{
  switch(estadoMultiball)
  {
    case PuertaAbierta:

         if(bandera==6 )
         {
            servo.write(180);
            modulo.playSpecified(6);
            estadoMultiball = PuertaCerrada;
            MULTIBALL = 1;
         }
        
    break;

    
    case PuertaCerrada:

         if(flagRead())
         {
            inicializarMEF(&MEF1);
            inicializarMEF(&MEF2);
            inicializarMEF(&MEF3);
            inicializarMEF(&MEF4);
            inicializarMEF(&MEF5);
            inicializarMEF(&MEF6);
            estadoMultiball = MultiBallEspera;
            bandera = 0;
         }
        
    break;

    case MultiBallEspera:

         if(bandera == 6)
         {
            tInicio_1 = millis();
            banderaHabilitacion = 0;
            banderaMultiplicacion = 1;
            servo.write(0);
            estadoMultiball = PuertaAbierta;
         }

    break;
  }
}

/*****************************************************************************************/
/******************************** Funciones generales ************************************/ 
/*****************************************************************************************/ 

void mifuncion(struct variablesMEFS *indice1, char numtar, uint16_t pixel, uint16_t valorOn, uint16_t valorOff)
{
    indice1->tarjeta   = numtar;
    indice1->numpixel  = pixel;
    indice1->pixelOn   = valorOn;
    indice1->pixelOff  = valorOff;
    indice1->tInicio   = millis();
}

void mifuncion_v2(struct variablesMEFS_v2 *indice2, char numtar_v2, uint16_t pixel_v2, uint16_t valorOn_v2, uint16_t valorOff_v2)
{
    indice2->sensor_v2   = numtar_v2;
    indice2->numpixel_v2  = pixel_v2;
    indice2->pixelOn_v2   = valorOn_v2;
    indice2->pixelOff_v2  = valorOff_v2;
    indice2->tInicio_v2   = millis();
}


int flagRead()
{
  if(digitalRead(sensor_multiball) == 1)
  {
    banderaMultiball++;
  }

  if(banderaMultiball==3)
  {
    banderaMultiball = 0;
    return(1);
  }

  else
  {
    return(0);
  }
}


void llamadoInterr()
{
  //player.playSpecified(17);
}

//**********************************************************************************************************************************************************
void TARJETA7_10K(){
  
   
                  puntaje +=10000;                                    //suma 10k puntos
                  modulo.playSpecified(5);                           //sonido
                                                                 
                  tira.setPixelColor(numero_led,255,255,255);     //LED DE 10k PRENDIDO
                  tira.show();                        
                                      
  }
