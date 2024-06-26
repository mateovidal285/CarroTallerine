#include <SoftwareSerial.h>
#include <SPI.h>
#include <MFRC522.h>

SoftwareSerial BT(12, 13);

#define RST_PIN	9    
#define SS_PIN	53   
MFRC522 mfrc522(SS_PIN, RST_PIN); 

#define PWM_D 11
#define PIN_DD 10
#define PIN_DI 8
#define PWM_I 3
#define PIN_ID 4
#define PIN_II 2
#define Potenciometro 0
#define PIN_InfD 7
#define PIN_InfI 6

byte ActualUID[4]; 
byte Tarjeta1[4]= {0x93, 0x63, 0x2E, 0x11} ; //código de tarjeta 1

enum {ADELANTE, ATRAS, IZQUIERDA, DERECHA, FRENAR, NADA, SG, DD, DI};

int estado = NADA;

void setup()
{
  Serial.begin(9600);
  for(int i = 2; i<= 11; i++){
    pinMode(i, OUTPUT);
  }
  BT.begin(9600);
  BT.println("CONECTADO");

  pinMode(PIN_InfD, INPUT);
  pinMode(PIN_InfI, INPUT);

  SPI.begin();        //Iniciamos el Bus SPI
	mfrc522.PCD_Init(); // Iniciamos  el MFRC522
  
}

void loop()
{

Serial.println(digitalRead(PIN_InfI));
  recibirMensajes();

  leerTarjeta();

  analogWrite(PWM_D, 110);
  analogWrite(PWM_I, 110);


  switch (estado)
  {
    case FRENAR:
      frenarMotores();
      break;
    case DERECHA:
      girarDerecha();
      break;
    case IZQUIERDA:
      girarIzquierda();
      break;
    case ADELANTE:
      moverAdelante();
      break;
    case ATRAS:
      moverAtras();
      break;
    case SG:
      seguirLinea(PIN_InfD, PIN_InfI);
      break;
    case DD:
      DiagonalDerAdelante(PWM_I, velocidad);
      break;
    case DI:
      DiagonalIzqAdelante(PWM_D, velocidad);
      break;
  }
  delay(100);
}


void leerTarjeta(){


  if ( mfrc522.PICC_IsNewCardPresent()) 
        {  
  		//Seleccionamos una tarjeta
            if ( mfrc522.PICC_ReadCardSerial()) 
            {
                  // Enviamos serialemente su UID
                  Serial.print(F("Tarjeta UID:"));
                  for (byte i = 0; i < mfrc522.uid.size; i++) {
                          Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
                          Serial.print(mfrc522.uid.uidByte[i], HEX);   
                          ActualUID[i]=mfrc522.uid.uidByte[i];          
                  } 
                  Serial.print("     ");                 
                  //comparamos los UID para determinar si es uno de nuestros usuarios  
                  if(compareArray(ActualUID,Tarjeta1)){
                    Serial.println("Tarjeta frenar");
                    estado = FRENAR;
                  }
                    
                  else{
                    Serial.println("tarjeta no reconocida");
                  }
                  
                  mfrc522.PICC_HaltA();
          
            }
      
	}
}

 boolean compareArray(byte array1[],byte array2[])
{
  if(array1[0] != array2[0])return(false);
  if(array1[1] != array2[1])return(false);
  if(array1[2] != array2[2])return(false);
  if(array1[3] != array2[3])return(false);
  return(true);
}