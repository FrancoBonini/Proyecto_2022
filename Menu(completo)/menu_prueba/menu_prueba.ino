  //funciones
  //  myDFPlayer.volume(porcentaje_volumen); //0 a 100%(volumen)
  //  Setbrightness(porcentaje_brillo);     //0 a 100%(brillo)
  //  tipo_canciones                       //hasta 10 canciones
  
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#define clk 2
#define dt  3
#define btn 4
//#define led 10

LiquidCrystal_I2C lcd(0x27, 16, 2);

String opciones[] = {"BRILLO", "VOLUMEN", "CANCIONES", "SALIR"};
int max_opciones = sizeof(opciones)/sizeof(opciones[0]);
int maxima_opciones = 100;
int state_clk_old;
int state_btn_old;
int count = 0;
int count2 = 1;
int contador;
int porcentaje_brillo;
int porcentaje_volumen;
int tipo_canciones;
//bool hz_1 = false;
// mono = false;
//unsigned long tiempo_actual = 0;
//unsigned long tiempo_actual2 = 0;

void setup() {
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
 // pinMode(led, OUTPUT);
  pinMode(clk, INPUT);
  pinMode(dt, INPUT);
  pinMode(btn, INPUT_PULLUP);
  state_clk_old = digitalRead(clk);
  state_btn_old = digitalRead(btn);
  mostrar_menu();
}

void loop() {

  
  int state_btn = digitalRead(btn);

  encoder();
  
  if(state_btn_old == HIGH && state_btn == LOW){
    state_btn_old = state_btn;
    run_option();
  }

// /* if(millis() >= tiempo_actual + 500){
//    tiempo_actual = millis();
//    if(hz_1) digitalWrite(led, !digitalRead(led));
//  }*/
//
// /* if(millis() >= tiempo_actual2 + 6000){
//    if(mono) digitalWrite(led, LOW);
//  }*/

  state_btn_old = state_btn;
}


void run_option(){
  if(count == 0){
    mostrar_Brillo();
    while(1){
      encoder_brillo();
      int state_btn = digitalRead(btn);
         if(state_btn_old == HIGH && state_btn == LOW){
          mostrar_menu();
          return;
         }
         state_btn_old = state_btn;
      }
  }
  if(count == 1){
    mostrar_Volumen();
    while(1){
      encoder_volumen();
      int state_btn = digitalRead(btn);
         if(state_btn_old == HIGH && state_btn == LOW){
          mostrar_menu();
          return;
         }
         state_btn_old = state_btn;
      }
  }
  if(count == 2){
    mostrar_Canciones();
    while(1){
      encoder_cancion();
      int state_btn = digitalRead(btn);
         if(state_btn_old == HIGH && state_btn == LOW){
          mostrar_menu();
          return;
         }
         state_btn_old = state_btn;
      }
  }
  if(count == 3){
   // salir del menu y apagarlo
  }
}

//***************************************************************************************************************************
void encoder(){
  int state_clk = digitalRead(clk);
  int state_dt = digitalRead(dt);
  
  if(state_clk_old == HIGH && state_clk == LOW){
    if(state_dt == LOW){
      count--;
      count2--;
    }else{
      count++;
      count2++;
    }
    if(count < 0) count = max_opciones - 1;
    if(count > max_opciones-1) count = 0;
    if(count2 < 0) count2 = max_opciones - 1;
    if(count2 > max_opciones-1) count2 = 0;
    
    mostrar_menu();
  }

  delay(5);
  state_clk_old = state_clk;
}
void encoder_brillo(){
  int state_clk = digitalRead(clk);
  int state_dt = digitalRead(dt);
  
  if(state_clk_old == HIGH && state_clk == LOW){
    if(state_dt == LOW){
     porcentaje_brillo--;    
    }else{
     porcentaje_brillo++;
    }
    if(porcentaje_brillo < 0) porcentaje_brillo = maxima_opciones ;
    if(porcentaje_brillo > maxima_opciones) porcentaje_brillo = 0;
    mostrar_Brillo();
  }

  delay(5);
  state_clk_old = state_clk;
}
void encoder_volumen(){
  int state_clk = digitalRead(clk);
  int state_dt = digitalRead(dt);
  
  if(state_clk_old == HIGH && state_clk == LOW){
    if(state_dt == LOW){
     porcentaje_volumen--;    
    }else{
     porcentaje_volumen++;
    }
    if(porcentaje_volumen < 0) porcentaje_volumen = maxima_opciones ;
    if(porcentaje_volumen > maxima_opciones) porcentaje_volumen = 0;
    mostrar_Volumen();
  }

  delay(5);
  state_clk_old = state_clk;
}
void encoder_cancion(){
  int state_clk = digitalRead(clk);
  int state_dt = digitalRead(dt);
  
  if(state_clk_old == HIGH && state_clk == LOW){
    if(state_dt == LOW){
      tipo_canciones--;    
    }else{
      tipo_canciones++;
    }
    if(tipo_canciones < 0) tipo_canciones = 10 ;
    if(tipo_canciones > 10) tipo_canciones = 0;
    mostrar_Canciones();
  }

  delay(5);
  state_clk_old = state_clk;
}
//*******************************************
void mostrar_menu(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Menu: ");
  //lcd.setCursor(0,1);
  lcd.print(opciones[count]);
  lcd.setCursor(0,1);
  lcd.print(opciones[count2]);
}

//**************************************
void mostrar_Brillo(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Brillo: ");
  lcd.print(porcentaje_brillo);
  lcd.print("%");
  //lcd.setCursor(0,1);
 // lcd.print(opciones[count]);
  lcd.setCursor(0,1);
  lcd.print("Pulsa -> salir");
}
//***********************************
void mostrar_Volumen(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Volumen: ");
  lcd.print(porcentaje_volumen);
  lcd.print("%");
  //lcd.setCursor(0,1);
 // lcd.print(opciones[count]);
  lcd.setCursor(0,1);
  lcd.print("Pulsa -> salir");
}
//******************************************
void mostrar_Canciones(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Cancion: ");
  lcd.print(tipo_canciones);
  //lcd.setCursor(0,1);
 // lcd.print(opciones[count]);
  lcd.setCursor(0,1);
  lcd.print("Pulsa -> salir");
}
