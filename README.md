# curiosity_btl
files for Curiosity Bricolabs Technology Laboratory project

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

## electr'onica




¿Y usar un L298 para controlar los 3 motores de cada lado?

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

Para la alimentaci'on usaremos 2 18650 con un interruptor
v0: alimentamos a los L9110 desde V y G del shield ¿son 5V?
v1: alimentarlos desde las baterías

## Impresi'on 3D

Usar al menos un 30-40% de relleno en las partes de las ruedas

## Programaci'on
Como se va a controlar por Bluetooth vamos a hacer un programa que permita controlarlo desde comandos serie

Control de velocidad y giro por movimiento
   w
 a s d
   x

**w** acelera los 6 motores
**a** gira a la derecha (motores izd atras, drchos adelante)
**s** detiene en seco
**d** gira a la izda (motores izd adelante, drchos atras)
**x** ralentiza los 6 motores

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


### Detalles del programa

Un switch que reacciona a cada tecla
Al final del switch se actualizan todos los estados

## Mejoras

Añadir micro-agujeros para los tornillos

Forma del enganche del servo	
