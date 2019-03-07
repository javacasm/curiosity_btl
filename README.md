# Curiosity BTL

Este proyecto trata de crear un modelo a escala del rover marciano [Curiosity](https://en.wikipedia.org/wiki/Curiosity_(rover))

![Curiosity](https://upload.wikimedia.org/wikipedia/commons/thumb/f/f3/Curiosity_Self-Portrait_at_%27Big_Sky%27_Drilling_Site.jpg/260px-Curiosity_Self-Portrait_at_%27Big_Sky%27_Drilling_Site.jpg)

![alt text](https://github.com/felixstdp/curiosity_btl/raw/master/randall_munroe_curiosity.jpg)

Basado en  [Curiosity Bricolabs Technology Laboratory project](https://bricolabs.cc/wiki/proyectos/curiosity_btl)

## Modelos

A día de hoy conozco 3 modelos a diferente escala

[Scale 1:15](https://www.thingiverse.com/thing:3432863) de [CEIP Federico García Lorca](http://unblogfantasticoenguevejar.blogspot.com/)

![Escala 1.15](https://cdn.thingiverse.com/renders/8c/d8/23/7b/d2/31d51dae61ead87122333f0cf6d42c45_preview_featured.jpg)

[scale 1_10](https://github.com/felixstdp/curiosity_btl/tree/master/scale_1_10)
- 4 x 9g servos
- 6 x N20 dc motors

![escala 1.10](https://bricolabs.cc/wiki/_media/proyectos/curiosity/curiosity_1_800.jpg?w=800&tok=0070ac)

[scale_1_5](https://github.com/felixstdp/curiosity_btl/tree/master/scale_1_5) (Deseando montar uno)
- 4 x s3003 servos
- 6 x type 2418 dc motors

Tanto los ficheros originals de diseño como los STL para imprimirlos están disponibles

https://bricolabs.cc/wiki/proyectos/curiosity_btl


## Electrónica

Tengo pensado realizar diferentes versiones con complejidad creciente

### V 0

Conectamos juntos los 3 motores de cada lado

Usar un L9110  para controlar los 3 motores de cada lado

    M1 S1       S4 M6
      \           /
    M2-\__L9110__/-M5
       /         \
      /           \
    M3 S2       S3 M4

    L9110
    M1 11 y 6
    M2 5 y 3

Usaremos un Arduino Uno y un Sensor Shield v5.0 para facilitar la conexión

** MUY IMPORTANTE: No podemos usar servos y PWM 9 y 10 al mismo tiempo https://www.luisllamas.es/salidas-analogicas-pwm-en-arduino/ **


    S1 12
    S2  8
    S3  7
    S4  2


Lo controlaremos vía Bluetooth  (conectado a los pines 0,1)

#### Montaje

![Montaje](https://github.com/javacasm/curiosity_btl/raw/master/images/Curiosity_v1_bb.png)

#### Esquema electrónico

![Esquema](https://github.com/javacasm/curiosity_btl/raw/master/images/Curiosity_v1_esquematico.png)

###  V 0.5

** Comentar problemas de alimentación y hacer versión mas potente con alimentación directa de las baterías **



### V 1

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
v1: alimentarlos directamente desde las baterías

### V 2

NodeMCU y Shield de motores controlando los motores


### V 3

Raspberry pi y placa controladora de servos y PWM
Cámara con mecanismo Pan/Tilt

## Impresión 3D

Usar al menos un 30-40% de relleno en las partes de las ruedas

## Programación

** MUY IMPORTANTE: No podemos usar servos y PWM 9 y 10 al mismo tiempo https://www.luisllamas.es/salidas-analogicas-pwm-en-arduino/ **



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

![app](https://lh3.googleusercontent.com/w5hcbVT0Vinb7l0EgoF5PAc19hzAlHsjR5Irn8Z4GbZGLmKYy48CdcFJ9B9OXuRxP8Q=w720-h310-rw)

## Mejoras

Añadir micro-agujeros para los tornillos
