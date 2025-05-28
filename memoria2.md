## Dinamyc Loading y Linking

### Dinamyc Loading 
Es una tecnica de manejo de memoria que permite que las rutinas y objetos se carguen dinamicamente hasta que se necesiten. 
Son responsabilidades del desarrollador, sistema operativo y paquetes que implementen:

### Dinamyc Linking
Tecnica de manejo de memoria que permite que las rutinas y objetos se carguen en la memoria una vez y si desea ser utilizado nuevamente s hace un link a la rutina original.

## Swapping
Es una tecnica de manejo de memoria que permite que los procesos sean cargados a memoria o descargados de memoria segun desiciones del SO.

## Segmentacion
Es una tecnica de manejo de memoria que permite la asignacion de memoria de manera no continua. Es dividir los procesos en segmentos. La segmentacion depende del lenguaje de programacion + compilador.

Tiene una estructura llamada tabla de segmentos. Esta tabla de segmentos tiene la informacion sobre los segmentos de los procesos. Cuando hacemos uso de segmentacion tiene mas carga el procesador, debido a que una tabla existe en los registros del cpu. 

## Paginacion
Es una tecnica de manejo de memoria en donde la idea es separar tanto la memoria fisica como la logica en trozos pequeños de igual tamaño. El tamaño de las paginas se da en potencias de 2. 

32 bits m=32    n=12
2^32 direcciones logicas disponibles
2^12 tamaño de paginas

quedan 2^20 paginas

Cuantas paginas podemos tener en un sistema de 32 bits?? 
tenemos un tamaño de pagina de 4 kilobytes

m = 32 bits
n = 4kilobytes = 4000 bits o  log2(4) = 2^12 bytes
2^m-n

2^32-12 = 2^20 bits


Asumiendo:
Pagina de 2048 bytes
tamaño de proces de 72,766

Cuantas  paginas ocupa el proceso

72,766/2048 = 36 paginas 

En bytes cuanta fragmentacion introducimos?

se esta perdiendo 962 bytes en fragmentacion

72766/2048 = 35.53 
eso nos da un 47% porel 1 - .53 da .47 y ese 47 es la fragmentacion, luego es un:
pagina x fragmentacion y es 2048 x .47 = 962

### Mecanismos para complementar la paginacion

#### Paginacion jerargica
*buscar foto*

#### Paginacion con hashing
*buscar foto*

#### Paginacion invertida
*buscar foto*

El sistema operativo tiene que realizar operaciones para manejar la paginacion.

1. La obtencion, se refiere a como es que el sistema sabe que pagina debe agarrra
    - image paging, cuando se necesita se carga
    - 
