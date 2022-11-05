#include <EEPROM.h>
#include <Wire.h>     // libreria de comunicacion por I2C
#include <LCD.h>      // libreria para funciones de LCD
#include <LiquidCrystal_I2C.h>    // libreria para LCD por I2C

LiquidCrystal_I2C lcd (0x27, 2, 1, 0, 4, 5, 6, 7); // DIR, E, RW, RS, D4, D5, D6, D7

//Parametros Encoder
const int salida_A = 7;    //CLK 
const int salida_B = 6;    //DT
const int swPin  = 4;      //SW

//  int pinPotenciometro = A0;
  int lectura;
  int porcentaje;
//  int pinPotenciometro2 = A1;
  int lectura2;
  int porcentaje2;
  int x = 0;
  

void setup()
{
   Serial.begin(9600);
   
   pinMode (salida_A,INPUT);
   pinMode (salida_B,INPUT);
   pinMode (swPin,INPUT_PULLUP);
  
//   pinMode(2, INPUT_PULLUP); 
//   pinMode(4, INPUT_PULLUP);
 //  pinMode(pinPotenciometro, INPUT);
 //  pinMode(pinPotenciometro2, INPUT);
    lcd.setBacklightPin(3,POSITIVE);  // puerto P3 de PCF8574 como positivo
    lcd.setBacklight(HIGH);   // habilita iluminacion posterior de LCD
    lcd.begin(16, 2);     // 16 columnas por 2 lineas para LCD 1602A
    lcd.clear();      // limpia pantalla
}

void loop()
{
//   int pulsador = digitalRead(2);
//   int limpiador = digitalRead(4);
 /*  lectura = analogRead(pinPotenciometro);
   porcentaje = map(lectura, 0, 1018, 0, 100);
   lectura2 = analogRead(pinPotenciometro2);
   porcentaje2 = map(lectura2, 0, 1018, 0, 255);       //hasta 255 digitales de 1018 analogico*/
   
   if(x == 0){

   lectura = analogRead(pinPotenciometro);
   porcentaje = map(lectura, 0, 1018, 0, 100);
   lectura2 = analogRead(pinPotenciometro2);
   porcentaje2 = map(lectura2, 0, 1018, 0, 255);       //hasta 255 digitales de 1018 analogico
    
    lcd.setCursor(10, 0);    // ubica cursor en columna 0 y linea 0
    lcd.print("     ");  // escribe el texto
    
    lcd.setCursor(0, 0);    // ubica cursor en columna 0 y linea 0
    lcd.print("Volumen: ");  // escribe el texto
    lcd.print(porcentaje);
   // lcd.setCursor(12, 0);    // ubica cursor en columna 12 y linea 0
    lcd.print("%");
    
    lcd.setCursor(10, 1);    // ubica cursor en columna 0 y linea 1
    lcd.print("     ");
    
    lcd.setCursor(0, 1);    // ubica cursor en columna 0 y linea 1
    lcd.print("Brillo:  ");
    lcd.print(porcentaje2);   // funcion millis() / 1000 para segundos transcurridos
    //lcd.setCursor(12, 1);    // ubica cursor en columna 12 y linea 1
    lcd.print("%");
    delay(150);
   }

  if(x == 1){

   lectura = analogRead(pinPotenciometro);
   porcentaje = map(lectura, 0, 1018, 0, 20);        //hasta 20 digitales de 1018 analogico
   lectura2 = analogRead(pinPotenciometro2);
   porcentaje2 = map(lectura2, 0, 1018, 0, 10);       //hasta 10 digitales de 1018 analogico
    
    lcd.setCursor(13, 0);    // ubica cursor en columna 0 y linea 0
    lcd.print("   ");  // escribe el texto
    
    lcd.setCursor(0, 0);    // ubica cursor en columna 0 y linea 0
    lcd.print("Canciones: ");  // escribe el texto
    lcd.print(porcentaje);
   // lcd.setCursor(14, 0);    // ubica cursor en columna 14 y linea 0
    lcd.print("%");

    lcd.setCursor(13, 1);    // ubica cursor en columna 0 y linea 1
    lcd.print("   ");
    
    lcd.setCursor(0, 1);    // ubica cursor en columna 0 y linea 1
    lcd.print("Juego:     ");
    lcd.print(porcentaje2);   // funcion millis() / 1000 para segundos transcurridos
  //  lcd.setCursor(14, 1);    // ubica cursor en columna 14 y linea 1
    lcd.print("%");
    delay(150);
    }


    if(pulsador == LOW){
      x++;
      delay(400);
      if(x == 2){
        x = 0;
      }
      
      }
      if(limpiador == LOW){
      lcd.clear();      // limpia pantalla
      delay(150);
      }
    
       

    //funciones
  //  myDFPlayer.volume(porcentaje);
  //  Setbrightness(porcentaje2);     //0 a 255(brillo)
}
