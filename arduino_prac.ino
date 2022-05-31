#include <AltSoftSerial.h>
AltSoftSerial mySerial;
//Constantes de la sonda
char toSend[4];
byte toRead[36];
byte toRecieve[4];
boolean measureState;
int i,len;
signed long tmp;
double m[8];
int num_ions=8;
double Ions[8];
// Constantes de la bomba
int IN1Pin = 5;  // Pin IN1 connected on D5 (PWM), Modify if you use a different PWM pin!
int IN2Pin = 6;  // Pin IN2 connected on D6 (PWM), Modify if you use a different PWM pin!
int val= 0;     // Always start with initialized variables! val will be the intensity of the PWM, rom 0 (full stop) to 255 (full speed)
int vel =200; // valor de velocidad que vamos autilizar. Fijar al valor deseado en función
//Constantes de la válvula
const byte pHpin           = A0;     // Conecto el sensor de pH
const byte RELAY_ENABLEIN1 = 2;      // válvula de 3 vías -
const byte botonPin        = 4;
double Po;
double Co;
bool estadoBoton, estadoBotonAnt = false;
bool ajustarSolucion = true;
byte acid_state = 0;
unsigned long start, timeLectura;
void setup() 
{
    pinMode(IN1Pin,OUTPUT);
    pinMode(IN2Pin,OUTPUT);
    analogWrite(IN1Pin, 0);    // According to the TA7291P datasheet, it is very important to start the bridge at full stop. I will not argue with them!
    analogWrite(IN2Pin, 0);    // Always according to the same datasheet, both pins should be low.
    Serial.println("Waiting, 5s");    // Just to remember you why nothing is working at this point!
    delay(5000);                      // Initial pause, change this value according to your needs (in milliseconds)

  measureState = false;
  Serial.begin(9600); // pc serial
  mySerial.begin(9600); //meter serial
  Serialreceive(); // ejecutamos esto aquí para que solo se ejecute una vez dandones así los valores iniciales
  rebre_Dades();
  Co = m[1]; // los almacenamos en variables diferentes para evitar que se sobreescriban en el bucle posterior.
  Po = m[7];
}

void loop() 
{ 
 flow(); // dejamos pasar el caudal de Na
 Serialreceive();  // medimos la concentración de los iones
 while (measureState == true)
 {
    rebre_Dades();
  delay(10);
 }
 delay(10);
 if (ajustarSolucion){ // si la concentración de nuestro ión supongamos que está en m[1] es igual a la concentración inical en algun momento
   if(m[1] == Co){
     acid_flow(); // dejamos pasar la corriente ácida por la válvula de tres vías
   }
   if(ajustarSolucion){ //si el pH, suponiendo que está en m[7] es igual al Po (pH) inicial, la columna está regenerada y pasamos la corriente de Na de nuevo
     if(m[7] == Po){
       flow();
     }
   }
 }
}

void flow()
{
    if(val<vel)
    {
        analogWrite(IN1Pin, val);//aceleramos poco a poco
        delay(5);            // You can tweak this value, This is the actual waiting time before increasing to the next PWM value
        val++;              // The cycle repeats itself until vel is reached.

    }
    else{
        Serial.println("Speed Reached");
    }
}

void Serialreceive()
{
  if (Serial.available()>0) 
  { 
    Serial.readBytes(toRecieve, 4);    // get the new byte:
    if (toRecieve[0]==0x4D) //Mesurar 1 'M'
    {
      toSend[0] = 0x02;    // the value 02 represents the measure instruction.
      toSend[1] = 0x00;
      toSend[2] = 0x00;
      toSend[3] = 0x00;
      for(int i=0;i<4;i++)
      {
        mySerial.print(toSend[i]);
      }
      measureState=true;
      Serial.println("Measuring ...");
    }
  }
}

void rebre_Dades()
{
  if (mySerial.available()>0) 
  {
    
    len = mySerial.readBytes(toRead,36 );
    Serial.print("HEX code: ");
    for (i=0; i<len; i++)
    {
      
      Serial.print(toRead[i], HEX);
      Serial.print(" ");
    }  
    if (toRead[0]==0x01 && toRead[1]==0x02 && toRead[34]==0x03 && toRead[35]==0x04)// 
    {
      for (i = 0; i < num_ions; i++) 
          {
            tmp = toRead[2 + 4 * i]; // int tmp
            tmp <<= 8;
            tmp |= toRead[3 + 4 * i];
            tmp <<= 8;
            tmp |= toRead[4 + 4 * i];
            tmp <<= 8;
            tmp |= toRead[5 + 4 * i];
            m[i] = ((double)tmp/100.00);

            Serial.println();
            Serial.print("ION number ");
            Serial.print(i+1);
            Serial.print("\t");
            Serial.print("value: ");
            Serial.print(m[i], 2); // como aquí se imprime el valor de la "concentración"(los mV) entendemos que en el vector m[] se alamcenan dichos valores
            Serial.print(" mV");  

          }
         measureState=false;
         Serial.println();
     }
  }
}
void acid_flow(){
    switch(acid_state){
        case 0: Serial.println("Relay OFF");
                digitalWrite(1,LOW); //abrir relay
                digitalWrite(2,LOW);
                acid_state = 1;
                start = millis();
                break;
        case 1: if(millis()-start > 500UL) {
            digitalWrite(1,HIGH); //cerrar relay
            digitalWrite(2,HIGH);
            acid_state = 2;
            start = millis();
        }
            break;
        case 2: if (millis()-start > 20000UL){
            acid_state = 3;
        }
            break;
        case 3: acid_state = 0; //reload cycle
                break;    
    }
}



