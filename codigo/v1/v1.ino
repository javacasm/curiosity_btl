// V1 versión 1 del software de control de la maqueta de curiosity btl de @felixstdp
// by @javacasm
// Licencia CC

//#include <BitbloqSoftwareSerial.h>

#include <Servo.h>



/*  Esquema electrico  
    
    M1 S1       S4 M6
      \           /
    M2-\__L9110__/-M5
      /          \
     /            \ 
    M3 S2       S3 M4

L9110
    M1 9 y 10
    M2 5 y 6
 
    

S1 12
S2  8
S3  7
S4  2


Bluetooth 0,1


*/


// Pines de control de los motores

#define M1_1 11
#define M1_2  6
#define M2_1  5
#define M2_2  3


// Pines de control de los servos

#define S1 12
#define S2  8
#define S3  7
#define S4  2

Servo s1,s2,s3,s4;

//bqSoftwareSerial bluetooth_de_la_placa(0, 1, 19200);

void setup(){

    // Configuramos los pines de los motores como salida
    pinMode(M1_1,OUTPUT);
    pinMode(M1_2,OUTPUT);
    pinMode(M2_1,OUTPUT);
    pinMode(M2_2,OUTPUT);


    // Configuramos los pines de los servos como salida
    pinMode(S1,OUTPUT);
    pinMode(S2,OUTPUT);
    pinMode(S3,OUTPUT);
    pinMode(S4,OUTPUT);

    // Configuramos las comunicaciones
    Serial.begin(19200);
    //bluetooth_de_la_placa.begin(19200);

    // Configuramos los servos
    s1.attach(S1);
    s2.attach(S2);
    s3.attach(S3);
    s4.attach(S4);

   setServosInitialState();

   setState();
   
   showState();
}

// La velocidad va desde -255 a 255, con valores negativos moviendose hacia atras 
int velocidad = 0;
int pasoVelocidad = 10; // Usaremos este incremento

// Nos permite dar velocidad a cada motor
void setSpeed(int pin1,int pin2,int speed){
    if(speed > 0){
        analogWrite(pin1,speed);
        analogWrite(pin2,0);
    } else {
        analogWrite(pin2, - speed);
        analogWrite(pin1,0);
    }
    
}


int posS1, posS2, posS3,posS4;
int pasoServo = 5; // Incremento de posicion de los servos
  

void setServosInitialState(){
  posS1 = 97;
  posS2 = 105;
  posS3 = 98;
  posS4 = 82;
}

void showState(){
    Serial.println("F Acelera");
    Serial.println("S STOP");
    Serial.println("B Decelera");
    Serial.println("L Giro izquierda \\ \\");
    Serial.println("                 / /");
    Serial.println("O Ruedas Rectas  | |");
    Serial.println("                 | |");
    Serial.println("R Giro derecha   / /");
    Serial.println("                 \\ \\ ");
    Serial.println("");
    Serial.print("velocidad = ");
    Serial.println(velocidad);
    Serial.print("S1,S4 = ");
    Serial.println(posS1);
    Serial.print("S2,S3 = ");
    Serial.println(posS2); 
}

void setState(){
    s1.write(posS1);
    s2.write(posS2);
    s3.write(posS3);
    s4.write(posS4);
    
    // Establecemos la velocidad
    
    setSpeed(M1_1,M1_2, velocidad);
    setSpeed(M2_1,M2_2, velocidad);
}

void loop(){

/*
Control de velocidad y giro por movimiento
  w acelera los 6 motores
  s detiene en seco
  x ralentiza los 6 motores

Control de giro usando los servos
i girar a la izquierda \ \
                       / /
                       
o servos rectos a      | |

p girar a la derecha  / /
                      \ \ 
*/

    if(Serial.available()>0){
      Serial.println("reading");
        char caracter = Serial.read();
        Serial.print("reading:");
        Serial.println(caracter);
        switch(caracter){
            case 'i':
            case 'L': // Mas giro a la izquierda
                posS1 -= pasoServo;
                posS4 -= pasoServo;
                posS3 += pasoServo;
                posS2 += pasoServo;
                break;
            case 'o':
            case 'O':
                setServosInitialState();
                break;  
            case 'p':                  
            case 'R': // Mas giro a la derecha
                posS1 += pasoServo;
                posS4 += pasoServo;
                posS3 -= pasoServo;
                posS2 -= pasoServo;
                break;
            case '1':
                if(velocidad > 0 ) velocidad = 100;
                else  velocidad = -100;                    
                break;
            case '5':
                if(velocidad > 0 ) velocidad = 150;
                else  velocidad = -150;                    
                break;
            case '9':
                if(velocidad > 0 ) velocidad = 250;
                else  velocidad = -250;                    
                break;                
            case 'w':  
            case 'F':
                velocidad += pasoVelocidad;
                break;
            case 's':
            case 'S':
                velocidad = 0;
                break;  
            case 'x':                  
            case 'B':
                velocidad -= pasoVelocidad;
                break;
        }
        // Vemos si nos hemos pasado de posiciones
        if(posS1 < 0) posS1 = 0;
        if(posS2 < 0) posS2 = 0;
        if(posS3 < 0) posS3 = 0;
        if(posS4 < 0) posS4 = 0;
        if(posS1 > 180) posS1 = 180;
        if(posS2 > 180) posS2 = 180;
        if(posS3 > 180) posS3 = 180;
        if(posS4 > 180) posS4 = 180;
        
        // Vemos si nos pasamos en las velocidades
        if(velocidad > 255 ) velocidad = 255;
        if(velocidad < -255 ) velocidad = -255;
        
        // Establecemos las posiciones de los servos
        
        setState();

        if(Serial.available() == 0)
          showState();       
        
    }    
}
