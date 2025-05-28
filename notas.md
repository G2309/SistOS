# Threads

## ¿Que es un thread?
Un thread es una unidad basica, de ejecucion de un proceso. A un thread tambien se le suele denominar como una version ligera de un proceso. Los threads son parte de lo que conforman la ejecucion de un proceso. Esta relacionado a la creacion de los procesos. Donde la ejecucion de procesos pueden ocurrir en uno o varios threads. 
---
**Un thread esta compuesto por:**
---
- ID
- Estado
- Program Counter
- Registros
- Stack
---

### Motivaciones (Por que usamos threads si ya tenemos otros conceptos como procesos)

- Los threads permite hacer varias tareas por separado. 
- Crear un proceso es mas pesado que crear un thread, debido a que para un Proceso 'A' para agregarlo a un thread, le doy los datos de ID, estado, Program Counter, etc.
- Incrementamos eficiencia.
- Las aplicaciones hoy endia son multithread.

Cuales son los beneficios de usar threads? 

- Responsiveness: Permite que partes de un proceso puedan seguir trabajando incluso si otra parte esta siendo bloqueada.
- Resource Sharing: Los threads comparten los recursos del proceso. 
- Economy: Es mas barato crear un pthread que un proceso.
- Scalability: El uso de threads permite sacar provecho a todas las arquitecturas multithread debido a que podemos asignar tareas paralelas.


## Threads de Kernel y Threads de Usuario

Cada uno de los tipos de threads corresponde a los modos de operacion. 

Threads de usuario son threads gestionados por aplicaciones en modo usuario, por el otro lado los threads de kernel son gestionados por el SO o modo kernel.
---
| Thread de usuario | Threads de kernel |
| El procesador no hace cambio de contexto | Ejecutados por el procesador |
| Gestionado por la aplicacion | Permiten paralelismo |
| No necesariamente permite paralelismo | Gestionado por el OS |
---

## Modelos de multithreading

### Muchos a uno

Es cuando tenemos muchos threads de usuario y estan mapeados a un thread de kernel. Este modelo no permite paralelismo

Usuarios: | | | |
          -------
Kernel:      |

Si un thread de usuario bloquea el kernel, el resto se queda bloqueado.

### Uno a uno

Es cuando a un thread usuario esta mapeado a un thread de kernel. Este modelo permite concurrencia y paralelismo. Si creamos un thread de usuario, entonces tenemos que crear uno de kernel. La cantidad de threads podria estar o puede limitarse debido a la introduccion de overhead. El diseño ayuda a evitar bloqueos. Es el mas utilizado por la industria. 

Usuario:  | | | | | 
          _________
Kernel:   | | | | |

### Muchos a Muchos

Muchos threads de usuario mapeado a muchos threads de kernel. Pero ademas tenemos uno y uno de cada uno especificos para coordinar esta gestion de los muchos a muchos. En teoria no posee ninguna desventaja de los demas modelos, pero en la practica la implementacion de este modelo introduce mucho overhead. Debido a que como pueden crecer y variar, y son dinamicos, pueden terminar perjudicando en el overhead.
