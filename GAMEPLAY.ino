
byte contador1=0;
byte contador2=0;
byte contador3=0;

byte variableTar1=0;
byte variableTar2=0;
byte variableTar3=0;
byte variableTar4=0;
byte variableTar5=0;
byte variableTar6=0;

byte variableRoll1=0;
byte variableRoll2=0;
byte variableRoll3=0;

#define tarjeta1 1
#define tarjeta2 2
#define tarjeta3 3
#define tarjeta4 4
#define tarjeta5 5
#define tarjeta6 6
#define tarjeta7 7

#define bobina1 8
#define bobina2 9

#define rollover1 10
#define rollover2 11
#define rollover3 12
#define rollover4 13
#define rollover5 14
#define rollover6 15
#define rollover7 16
#define rollover8 17
#define rollover9 18

#define sensor1   19
#define sensor2   20
#define sensor3   21
#define sensor4   22
#define sensor5   23
#define sensor6   24
#define sensor7   25  
#define sensor8   26
#define sensor9   27
#define sensor10  28

#define bumper1   29
#define bumper2   30

#define delay1 50
#define delay2 150

void setup() 
{
pinMode(tarjeta1,INPUT);
pinMode(tarjeta2,INPUT);
pinMode(tarjeta3,INPUT);
pinMode(tarjeta4,INPUT);
pinMode(tarjeta5,INPUT);
pinMode(tarjeta6,INPUT);
pinMode(tarjeta7,INPUT);

pinMode(bobina1,OUTPUT);
pinMode(bobina2,OUTPUT);

pinMode(rollover1,OUTPUT);
pinMode(rollover2,OUTPUT);
pinMode(rollover3,OUTPUT);
pinMode(rollover4,OUTPUT);
pinMode(rollover5,OUTPUT);
pinMode(rollover6,OUTPUT);
pinMode(rollover7,OUTPUT);

pinMode(sensor1,OUTPUT);
pinMode(sensor2,OUTPUT);
pinMode(sensor3,OUTPUT);
pinMode(sensor4,OUTPUT);
pinMode(sensor5,OUTPUT);
pinMode(sensor6,OUTPUT);
pinMode(sensor7,OUTPUT);
pinMode(sensor8,OUTPUT);
pinMode(sensor9,OUTPUT);
pinMode(sensor10,OUTPUT);

pinMode(bumper1,OUTPUT);
pinMode(bumper2,OUTPUT);
}

void loop() 
{
    
    /*************************************Este bloque maneja los bumpers**************************************/
    
    if(bumper1 == 1)
    {
        //suma un puntaje
    }
    
    if(bumper2 == 1)
    {
        //suma un puntaje
    }
    
        
    /**************************************************************************************************************/
    
    /*************** este bloque se encarga de sumar un puntaje cuando se activan las tarjetas ******************/
    if(tarjeta1 == 1)
    {
      //sumar punto
      variableTar1 = 1;
    }

    if(tarjeta2 == 1)
    {
      //sumar punto
      variableTar2 = 1;
    }

    if(tarjeta3 == 1)
    {
      //sumar punto
      variableTar3 = 1;
    }

    if(tarjeta4 == 1)
    {
      //sumar punto
      variableTar4 = 1;
    }
  
    if(tarjeta5 == 1)
    {
      //sumar punto
      variableTar5 = 1;
    }

    if(tarjeta6 == 1)
    {
      //sumar punto
      variableTar6 = 1;
    }
  
    /**********************Este bloque se encarga de verificar si los tres rollovers estan en 1***************/
    if(rollover7 == 1)
    {
      //suma puntaje
      //hace sonido
      variableRoll1 = 1;

    }
    
    if(rollover8 == 1)
    {
      //suma puntaje
      //hace sonido
      variableRoll2 = 1;

    }
    
    if(rollover9 == 1)
    {
      //suma puntaje
      //hace sonido
      variableRoll3 = 1;

    }

    if((variableRoll1 == 1) && (variableRoll2 == 1) && (variableRoll3 == 1) )
    {
      //special
    }
  /*******************************************************************************************************************************************/
  /******************************************Este bloque  maneja el multiball*****************************************************************/ 
  
  
  corroborarTarjetas();
  
  corroborarContador();

  if (contador1 == 4)
  {
    contador1--;
    
    digitalWrite(bobina1,HIGH);

    delay(delay1);

    digitalWrite(bobina1,LOW);

  }

  genMultiBall();
  
  terminacionDelMultiBall();
/**********************************************************************************************************************************************/


  corroborarTarjetaSiete();


  

   if(sensor1 == 1 || sensor4 == 1 || sensor10 == 1)
   {
     //manejoDeBolas();   
   }
   
}
void variablesEnCero()
{
  variableTar1 = 0;
    
    variableTar2 = 0;

    variableTar3 = 0;

    variableTar4 = 0;

    variableTar5 = 0;

    variableTar6 = 0;
}


void corroborarTarjetas()
{
  if( (variableTar1 == 1) && (variableTar2 == 1) && (variableTar3 == 1) && (variableTar4 = 1) && (variableTar5 == 1) && (variableTar6 == 1) )
  {  
    multiBall();
  }
}

void corroborarContador()
{
  
  if(contador1 == 3)
  {
    variablesEnCero();

  }  
}

void multiBall()
{
  if (rollover6 == 1)
  {
      contador1++;
      //sonido
      delay(delay1);
      //soltar bola en lanzador
  }
}

void genMultiBall()
{
  if( (variableTar1 == 1) && (variableTar2 == 1) && (variableTar3 == 1) && (variableTar4 = 1) && (variableTar5 == 1) && (variableTar6 == 1) )
  {
      digitalWrite(bobina1,HIGH);
      delay(delay2);
      digitalWrite(bobina1,LOW);
  }
}

void corroborarTarjetaSiete()
{
  if(tarjeta7 == 1)
  {
    contador2 += 1;

    switch(contador2)
    {
      case1: 
              //sumo 5K
      break;

      case2: 
              //sumo 10K
      break;
      case3: 
              //sumo 30K
      break;
      case4: 
              //sumo 50K
      break;
      case5: 
              //extra ball
      break;
      case6: 
              //2x
      break;
      case7: 
              //3x
      break;
    }
   }
}

void terminacionDelMultiBall()
{
  if((sensor1==1) && (sensor4 == 1) && (sensor10 == 1))
  {
    contador3++;
  }

  if(contador3 < 3)
  {
    if(rollover6 == 1)
    {
      delay(delay1);

      digitalWrite(bobina1,HIGH);

      delay(delay1);

      digitalWrite(bobina1,LOW);

    }
  }
}