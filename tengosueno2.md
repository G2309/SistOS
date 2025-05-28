## Sincronizacion por medio de hardware
[Sistemas com un solo cpu] monoprocesador
1.**Limitar/desactivar Interrupciones**
    - *Pros*
        - Control absoluto del CPU.
        - Evitar elacceso a recursos.
        - Garantia de atomicidad [MIentras un proceso se ejecuta nadie lo puede interrumpir]
        - Simple implementacion
    - *Contras*
        - Bloquea el sistema
        - Degrada el rendimiento
        - Ineficiente

[Sistema multiprocesador]
2.**Test and Set Instruction [TAS]**
    En una sola instruccion hago un test y set de una variable como operacion atomica (ES un bloque de instruccion que no se puede interrumpir)
    - *Pros*
        - Simple
        - Eficiente
        - Nos ayuda a evitar race conditions
        - Garantiza atomicidad
    - *Contra*
        - Busy waiting
        - No es recomendable si tenemos muchos procesos 

3. **Compare and Swap Instruction[CAS]**
    - *Pros*
        - Simple
        - Eficiente
        - Nos ayuda a evitar race conditions
        - Garantiza atomicidad
    - *Contra*
        - Busy waiting
        - No es recomendable si tenemos muchos procesos 

## Mutex locks

Los diseñadores de OS decidieron abstraer la funcionalidad de TAS y CAS a nivel de software para resolver el CS problem.
Funciones que realizan las logicas TAS y CAS
    - adquire()
    - release()

Si yo tengo mi programa y quiero entrar a mi critical section, llamo a la funcion adquiere y se le pasa un lock:

```sh
while(true) {
    adquire(*lock)
    critical section
    release(*lock)
    } 
````

## Inversion de prioridades

Un problema que ocurre4 cuando se usan mecanismos de explusion mutua, cuando un proceso de baja prioridad bloquea indirectamente uno de alta prioridad

La inversion de prioridades dice que si tenemos un proceso de prioridad alta bloqueado por otro proceso de prioridad baja, el OS le sube la prioridad al proceso de prioridad baja que bloquea al de la alta.


