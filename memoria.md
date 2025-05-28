# Manejo de Memoria

## Abstraccion de memoria y requisitos para su manejo

Es el conjunto de mecanismos mediante los cuales el Os oculta la ocmplejidad de la memoria fisica y ofrece una vista mas flexible util para los procesos. Para que esto pueda suceder el SO debe cumplir con los siguientes requisitos.

1. Reubicacion:
Los procesos consultan direcciones relativas. Los mecanismos que nos permiten reubicar data en el SO es:
    - MMU
    - Swapping
2. Proteccion:
Hace referencia a que los procesos tienen espacio de memoria aislados. 
    - Aplica para el OS mismo
3. Mecanismos para compartir memoria:
Para poder optimizar memoria, buscamos compartir memoria. Estos mecanismos son:
    - IPC
    - Bibliotecas compartidas
    - Dinamic Linking
4. Organizacion:
Como se distribuye logisticamente la memoria y tambien como lo hacemos eficiente. Mecanismos:
    - Segmentacion
    - Paginacion
    - Establecer las jerarquias de memoria

## Espacio de direcciones: Direcciones Logicas y Fisicas

La abstraccion de la memoria fisica se presenta como un espacio de direcciones. El espacio de direcciones es el conjunto de direcciones de memoria a los cuales un proceso puede acceder.

### Direcciones Logicas
Son las direcciones relativas que los procesos utilizan para acceder a memoria.

### Direcciones fisicas
Son las direcciones reales en la memoria fisica
 
## Vinculacion de direcciones
El procesador es el encargado de hacer la traduccion de las direcciones logicas a fisicas. Esto se da gracias a 2 registros que se definen al momento de crear el proceso. Dichos procesos son:
- Base Register: Es la minima dirección de memoria fisica que podemos utilizar.
- Limit Register: Es la direccion de memoria fisica maxima a la que podemos avanzar/utilizar.

## Memory Management Unit
Es una unidad de procesamiento del CPu dedicad al manejo de memoria, introducida inicialmente junto a la memoria virtual.

- Agujeros en el espacio de direcciones
- Insuficiencia de ram o memoria principal
- Seguridad al acceso entre procesos


