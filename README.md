# Curiosity BTL

Basado en  Curiosity Bricolabs Technology Laboratory project

¿Scale 1:15 de CEIP Federico García Lorca?

scale_1_10 folder for 1:10 scale model
- 4 x 9g servos
- 6 x N20 dc motors

scale_1_5 folder for 1:5 scale model
- 4 x s3003 servos
- 6 x type 2418 dc motors

.scad files for OpenScad
.stl files for printing
.ino files for Arduino
.jpg files for images

https://bricolabs.cc/wiki/proyectos/curiosity_btl

![alt text](https://github.com/fstdp/curiosity_btl/blob/master/randall_munroe_curiosity.jpg)

## Electrónica

### V0

Usar un L9110 o L298 para controlar los 3 motores de cada lado

    M1 S1       S4 M6
      \           /
    M2-\__L9110__/-M5
       /         \
      /           \ 
    M3 S2       S3 M4

    L9110
    M1 11 y 6
    M2 5 y 3
 
** MUY IMPORTANTE: No podemos usar servos y PWM 9 y 10 al mismo tiempo https://www.luisllamas.es/salidas-analogicas-pwm-en-arduino/ **


** Comentar problemas de alimentación y hacer versión mas potente con alimentación directa de las baterías **

    S1 12
    S2  8
    S3  7
    S4  2


Bluetooth 0,1


### V1

3 L9110, cada uno capaz de controlar 2 motores. Necesitan 2 entradas PWM para cada motor, por eso necesitamos un arduino Mega y un Sensor shield v5.0 por sencillez para los servos


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

Para la alimentación usaremos 2 18650 con un interruptor
v0: alimentamos a los L9110 desde V y G del shield ¿son 5V?
v1: alimentarlos directamente desde las baterías

## Impresión 3D

Usar al menos un 30-40% de relleno en las partes de las ruedas

## Programación

** MUY IMPORTANTE: No podemos usar servos y PWM 9 y 10 al mismo tiempo https://www.luisllamas.es/salidas-analogicas-pwm-en-arduino/ **

** Problemas con el bluetooth de bq ¿Por qué no hacerlo standard **



### V0 Control de velocidad y giro por movimiento
    w acelera los 6 motores
    s detiene en seco
    x ralentiza los 6 motores

    Control de giro usando los servos
    i girar a la izquierda \ \
                           / /
                  
    o servos rectos a      | |

    p girar a la derecha  / /
                          \ \ 

### V1 Control individual más fino

Control de giro de los servos

    Q/q   E/e
        S
    Z/z   C/c

Cada tecla mayúscula aumenta el ángulo del servo, la minúscula lo reduce

S mayúscula centra los 4 servos


    R/r   T/t
    F/f   G/g
    V/v   B/b

Controla la velocidad de cada uno de los 6 motores (incrementa/decrementa la velocidad) 

### Giro en el sitio

**a** gira a la derecha (motores izd atras, drchos adelante)
**d** gira a la izda (motores izd adelante, drchos atras)

### Detalles del programa

Un switch que reacciona a cada tecla
Al final del switch se actualizan todos los estados

## Aplicación de control

[Arduino Bluetooth Controler](https://play.google.com/store/apps/details?id=com.satech.arduinocontroller)



## Mejoras

Añadir micro-agujeros para los tornillos

Forma del enganche del servo	
