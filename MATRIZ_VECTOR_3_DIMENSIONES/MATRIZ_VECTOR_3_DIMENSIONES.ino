/*
 * funcion lc.setLed(Nro.disp, fila de la matriz, columna de la matriz, valor que puede ser true o false)
 * funcion lc.setRow(Nro.disp, fila de la matriz en la que se quiere imprimir, valor de 8 bits que se quiere mostar).
 * en el vector primero vienen la cantidad de tablas, las filas y despues las columnas .
 */


#include  "LedControl.h"

LedControl  lc=LedControl(12,10,11,4);  (DIN, CLK, CS, Nro.dispositivo)

char i;
char y;
char x;
char SecDig;
char PrimDig;


#define Alto 8
#define Largo 8
#define Num 10

byte Display [Num][Largo][Alto]=
{    
    
    {
      {B00000000},
      {B01100000},
      {B10010000},
      {B10010000},
      {B10010000},
      {B10010000},
      {B01100000},
      {B00000000} 
    },
    
    {  
      {B00000000},
      {B01000000},
      {B11000000},
      {B01000000},
      {B01000000},
      {B01000000},
      {B01000000},
      {B00000000} 
    }
};


void setup() 
{
    Serial.begin(9600);
    
    for(i; i <= 4; i++)
    {
       lc.shutdown(i,false);
       lc.setIntensity(i,0);
       lc.clearDisplay(i);
    }
    GenMatriz(1,1);
}

void loop() 
{
  GenMatriz(1,1);
  GenMatriz(0);
  delay(1000);
  GenMatriz(0,1);
  delay(1000);
}



void  GenMatriz( char PrimDig, char SecDig)

  byte contador = 0;
  
  if(PrimDig==SecDig)
  {
/*  con este for se barren todos los los renglones de la tabla,
    para mostrar el primer digito en la primera mitad de la matriz  */  
    
    for( x = 0; x <= 8; x++)
    {
      for( y = 0; y <= 8; y++)
      {
        lc.setRow(0,contador,Display[PrimDig][x][y]);     
      }
      contador++;
    }

/*  con este for shifteo el numero cargado en la tabla, 4 lugares,  
 *   para escribir el segundo digito
 */

//***********no funciona este bloque************\\
    
    for(x = 0; x<=8; x++)
     {
       for(y =0 ; y<=8; y++)
       {
         Display[PrimDig][x][y] >> 4;
      }
     }
 
//************************************************\\

/*  con este for se barren todos los los renglones de la  tabla,
    para mostrar el segundo digito en la segunda mitad de la matriz  */

    contador =0;
      
    for(x = 0; x <= 8; x++)
    {
      for(y = 0; y <= 8; y++)
      {
       lc.setRow(0,contador,Display[PrimDig][x][y]);    
      }
      contador++;
    }
}
    
  }    cierra el if
  
  
  
  else
  {
    /*  con este for se barren todos los los renglones de la tabla,
    para mostrar el primer digito en la primera mitad de la matriz  */  
    
    for( x = 0; x <= 8; x++)
    {
      for( y = 0; y <= 8; y++)
      {
       lc.setRow(0,contador,Display[PrimDig][x][y]);    
      }
      contador++;
    }
/*  con este for shifteo el numero cargadoi en la tabla 4 lugares,  
 *   para escribir el segundo digito
 */
    
    for(x = 0; x<=8; x++)
    {
      for(y = 0; y<=8; y++)
      {
        Display[SecDig][x][y] >> 4;
      }
    }

/*  con este for se barren todos los los renglones de la  tabla,
 *  para mostrar el segundo digito en la segunda mitad de la matriz  
 */
    contador=0;  
    for(x = 0; x <= 8; x++)
    {
      for(y = 0; y <= 8; y++)
      {
       lc.setRow(0,contador,Display[PrimDig][x][y]);    
      }
      contador++;
    }
  }  cierra el else
  
}   cierra el void
