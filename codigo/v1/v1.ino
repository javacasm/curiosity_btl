
#include <Servo.h>



/*  Esquema electrico  
    
    M1 S1          S4 M6
     \                /
     L9110.1    L9110.3
     /                \
    M2                M5
       ____L9110.2___    
      /              \  
    M3 S2          S3 M4

L9110.1 
    M1 13 y 12
    M2 11 y 10
    
    
L9110.2 
    M5 9 y 8
    M6 7 y 6
    

L9110.3 
    M3 5 y 4
    M4 3 y 2
    

S1 A0
S2 A1
S3 A3
S4 A4


Bluetooth 0,1


*/


// Pines de control de los motores

#define M1_1 13
#define M1_2 12
#define M2_1 11
#define M2_2 10
#define M5_1  9
#define M5_2  8
#define M6_1  7
#define M6_2  6
#define M3_1  5
#define M3_2  4
#define M4_1  3
#define M4_2  4

// Pines de control de los servos

#define S1 A0
#define S2 A1
#define S3 A2
#define S4 A3

Servo s1,s2,s3,s4;

int pinesMotores[] = {M1_1,M1_2,M2_1,M2_2,M3_1,M3_2,M4_1,M4_2,M5_1,M5_2,M6_1,M6_2};


void setup(){

    // Configuramos los pines de los motores como salida
    pinMode(M1_1,OUTPUT);
    pinMode(M1_2,OUTPUT);
    pinMode(M2_1,OUTPUT);
    pinMode(M2_2,OUTPUT);
    pinMode(M5_1,OUTPUT);
    pinMode(M5_2,OUTPUT);
    pinMode(M6_1,OUTPUT);
    pinMode(M6_2,OUTPUT);
    pinMode(M3_1,OUTPUT);
    pinMode(M3_2,OUTPUT);
    pinMode(M4_1,OUTPUT);
    pinMode(M4_2,OUTPUT);

    // Configuramos los pines de los servos como salida
    pinMode(S1,OUTPUT);
    pinMode(S2,OUTPUT);
    pinMode(S3,OUTPUT);
    pinMode(S4,OUTPUT);

    // Configuramos las comunicaciones
    Serial.begin(9600);

    // Configuramos los servos
    
    s1.attach(S1);
    s2.attach(S2);
    s3.attach(S3);
    s4.attach(S4);

}

// La velocidad va desde -255 a 255, con valores negativos moviendose hacia atras 
int velocidad = 0;
int pasoVelocidad = 5; // Usaremos este incremento

// Nos permite dar velocidad a cada motor
void setSpeed(int pin1,int pin2,int speed){
    if(speed > 0){
        analogWrite(pin1,speed);
        analogWrite(pin2,0);
    } else {
        analogWrite(pin2,speed);
        analogWrite(pin1,0);
    }
    
}


int posS1 = 90, posS2 = 90, posS3 = 90, posS4 = 90;
int pasoServo = 5; // Incremento de posicion de los servos
  


void loop(){

/*

Control de velocidad y giro por movimiento
   w
   s 
   x

**w** acelera los 6 motores
**s** detiene en seco
**x** ralentiza los 6 motores

Control de giro usando los servos

o Mueve los servos para girar a la izquierda \ \
                                               / /

p Mueve los servos para girar a la derecha / /
                                           \ \ 
*/

    if(Serial.available()>0){
        char caracter = Serial.read();
        switch(caracter){
            case 'o': // Mas giro a la izquierda
                posS1 -= pasoServo;
                posS4 -= pasoServo;
                posS3 += pasoServo;
                posS2 += pasoServo;
                break;
            case 'p': // Mas giro a la derecha
                posS1 += pasoServo;
                posS4 += pasoServo;
                posS3 -= pasoServo;
                posS2 -= pasoServo;
                break;
            case 'w':
                velocidad += pasoVelocidad;
                break;
            case 's':
                velocidad = 0;
                break;                
            case 'x':
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
        
        s1.write(posS1);
        s2.write(posS2);
        s3.write(posS3);
        s4.write(posS4);
        
        // Establecemos la velocidad
        
        for(int i = 0; i < 12; i += 2){
            setSpeed(pinesMotores[i],pinesMotores[i + 1], velocidad);
        }
        
        Serial.print("velocidad = ");
        Serial.println(velocidad);
        Serial.print("S1,S4 = ");
        Serial.println(posS1);
        Serial.print("S2,S3 = ");
        Serial.println(posS2);        
        
    }    
}
