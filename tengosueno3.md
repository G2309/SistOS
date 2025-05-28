## Semaforos
La persona que propuso utilzar los Semaforos fue Edsger Dijkstra y es una herramienta de sincronizacion. Permite manejar procesos de manera concurrente mediante un valor entero al que llamamos semaforo. Los semaforos pueden ser similares a los mutex loads. Maneja 2 operaciones:
- Wait() -> P() Proberen:
**Definicion**: 
```sh
    wait(s){
        while(s<=0)
            ; busy wait
            s--;
    }
```

- Signal() -> V() Verhogen
```sh
    signal(s){
        s++;
    }
```

Usualmente implementados de 2 maneras:
- **Counting Semaphore**:
    Esta implementacion permite multiples instancias o accesos.
- **Binary Semaphore**:
    Esta implementacion es bastante similar a los mutex locks, solo pueden tener un valor 0 y 1.

### Principal Desventaja:
Busy waiting (es cuando se desperdician ciclos de reloj revisando el while) Conocido tambien como spinlock. Solucion:
```sh
wait(s) {
    if(s<=0)
        bloqueo el proceso
    else
        s--
}

signal(s){
    if(hay procesos bloqueados)
        despertar uno
    else
        s++
}
```
esta solucion puede dar el problema de starvation debido a que si un proceso no sale de la waiting queue

## Monitores
Un monitor es:

- Son distractores de alto nivel de un mecanismo de sincronizacion
- Es una clase abstracta
    - Metodos
    - Variables
Ejemplo de la clase abstracta:
variables -> Variables que pueden ser compartidas por procesos, solo pueden ser accedidas por un procedure.
condition variables -> Son estructuras que se crean para manejar el acceso a las variables compartidas
procedure P1(){} Son operaciones que se pueden hacer sobre las variables compartidas

## Sincronizacion con Pthreads

Ofrece sincronicacion a nivel de threads de usuario. Provee distintas funcionalidades.
- mutex locks
- semaforos
    * nombrados(usable por muchos procesos)
    * anonimos (threads unicamente de un mismo proceso)

##  

## 
