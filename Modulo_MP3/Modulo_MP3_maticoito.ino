#include <SoftwareSerial.h>

#include "arduino.h"

#include <DFRobotDFPlayerMini.h>

//te amo mati

SoftwareSerial mySoftwareSerial(0,1);    //rx,tx
DFRobotDFPlayerMini myDFPlayer;

void setup() {
  mySoftwareSerial.begin (9600);
  Serial.begin (115200);

myDFPlayer.setTimeOut (500);
myDFPlayer.EQ (DFPLAYER_EQ_NORMAL);
myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);  //<-- para usar la microSD
//myDFPlayer.outputDevice(DFPLAYER_U_DISK);   //<-- para usar pendrive como fuente de sonidos

myDFPlayer.volume(10);    //0 a 30 de vol

//myDFPlayer.volumeUp();
//myDFPlayer.volumeDown();

//setear volume, device, etc
 
}

void loop() {
 
  myDFPlayer.play (3);    //<-- reproduce 3er cancion de la carpeta raiz
  delay(500);
 

}
