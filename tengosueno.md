## Sincronizacion

### Introduccion a la sincronizacion

La concurrencia en lo que puede resultar es lo que llamamos interrupcion o traslape de procesos. El problema que existe es que el acceso concurrente a los datos/recursos puede causar/resultar en compromisos a la integridad de los datos e informacion y a esto le llamamos **inconsistencias**.

El OS es el encargado en coordinar el uso de recursos. 

### Race Conditions

Es una situacion no deseada en la que un dispositivo o sistema trata de realizar dos o mas operaciones al mismo tiempo pero que por naturaleza deberian ser en orden especifico.

#### Definicion aplicada a computacion:
Es cuando 2 o mas procesos o threads tratan de acceder al mismo recurso al mimo tiempo.

Se dividen en dos grupos:

#### Informal

##### Criticos

Se le llama critico cuando se introduce un comportamiento inesperado o bug.

##### No criticos

Cuando no son criticos

#### Formal
Tipos de race condition:

##### Read-modify-write
El caso donde tenemos 2 procesos que leen un valor y escriben de regreso uno nuevo.

##### Check-then-act
El caso donde tenemos 2 procesos que primero revisan un valor y luego sobre ese valor tomamos una decision.

### Clases de interaccion entre procesos

La idea es dividir segun el tipo de interaccion que tienen entre si. 
Existen 3 grados y 4 tipos

#### Degree of awareness
Nos dice que tanta informacion conoce un proceso sobre el otro
- 1. Process unaware of each other
    - El resultado del proceso es independiente de los otros 
- 2. Process indirectly aware(shared object) 
    - El resultado de un proceso puede afectar a otro.
- 3. Process directly aware (communicacion directa) 
    - El impacto de un proceso si afecta la informacion de otro proceso

#### Relationship
- 1. Competition 
    - 
- 2. Cooperation by sharing 
    -
- 3. Cooperation by communication
    -

#### Influence that one process has on tahe other
- 1. Result of one process are independent of actions of others 
    - Timing may affect
- 2. Results of one procces may affect on others 
    -Timing may affect
- 3. Results of one process depend on information of others. 
    -

#### Potential problems
- 1. Problemas del primer nivel 
    - Mutual Exclusion 
    - Deadlocks
    - Starvation
- 2. Problemas del segundo nivel
    - Mutual exclusion
    - Deadlocks
    - Starvation
    - Data Coherence
- 3. Problemas del tercer nivel
    - Deadlocks
    - Starvation


