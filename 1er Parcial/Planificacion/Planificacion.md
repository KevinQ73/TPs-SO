# Planificación

## Índice
- [Definiciones varias](#definiciones-varias)
- [Tipos de planificadores](#tipos-de-planificadores)
    - [Planificador de largo plazo](#planificador-de-largo-plazo)
    - [Planificador de mediano plazo](#planificador-de-mediano-plazo)
    - [Planificador de corto plazo](#planificador-de-corto-plazo)
- [Tipos de planificadores de Corto Plazo](#tipos-de-planificadores-de-corto-plazo)
    - [Criterios de replanificación](#criterios-de-replanificación)
    - [Eventos de replanificación](#eventos-de-replanificación)
- [Criterios de Algoritmos](#criterios-de-algoritmos)
    - [Orientados al usuario](#orientados-al-usuario)
    - [Orientados al sistema](#orientados-al-sistema)
- [Algoritmos para planificadores de corto plazo](#algoritmos-para-planificadores-de-corto-plazo)
    - [FIFO](#fifo)
    - [SJF/SRT (Shortest job first)/(Shortest remaining time first)](#sjfsrt-shortest-job-firstshortest-remaining-time-first)
        - [SJF](#sjf)
        - [SRT](#srt)
        - [SJR vs SJF](#sjr-vs-sjf)
        - [Estimación de ráfaga](#estimación-de-ráfaga)
    - [Por Prioridades](#por-prioridades)
        - [¡Aging!](#aging)
    - [HRRN (Highest Response Ratio Next)](#hrrn-highest-response-ratio-next)
    - [Round Robin (RR)](#round-robin-rr)
    - [Virtual Round Robin](#virtual-round-robin)

### Definiciones varias

> **Planificación de Procesos**: Hace referencia a un conjunto de políticas y mecanismos del SO que gobiernan el orden en que se ejecutan los procesos.

> **Planificador de procesos**: Es un módulo del SO que se encarga de mover los procesos entre las distintas colas de planificación.

> La ejecución de un proceso consiste en una alternancia entre *ráfagas de CPU* y *ráfagas de E/S*.

- Las *ráfagas de CPU* son un periodo de tiempo en que un proceso se ejecuta en CPU
hasta que se bloquea o termina.
- Las *ráfagas de E/S* son el periodo de tiempo entre que un proceso hace una llamada
bloqueante de E/S (como leer de disco) hasta que llega la interrupción de fin de E/S.

Existen dos tipos de procesos distintos

- **Proceso limitado por E/S** *(I/O Bound)*: Es aquél que pasa más tiempo haciendo E/S que usando la CPU (tiene ráfagas de CPU cortas).
- **Proceso limitado por CPU** *(CPU Bound)*: Es aquél que pasa más tiempo procesando que haciendo E/S (tiene ráfagas de CPU largas).

### Tipos de planificadores

#### Planificador de largo plazo

- Debe tomar la decisión de si se agregará un nuevo proceso al conjunto de procesos que están activos
- Se ejecuta cuando un nuevo proceso es creado.
- Decide en qué momento se puede cargar un nuevo proceso
    - **Proceso finaliza -> disminuye grado multiprogramación**
    - **Monitoreo uso CPU -> cierto tiempo CPU IDLE**
    - **Job alta prioridad**

- Decide qué job será aceptado y convertido en proceso
- Controla el grado de multiprogramación del sistema
    - Baje grado de multiprogramación $=>$ CPU IDLE
    - Alto grado de multiprogramación $=>$ CPU BUSY y Menor % CPU para cada proceso
    **Estos brincan un servicio satisfactorio a los procesos LISTOS**


#### Planificador de mediano plazo

- Debe realizar operaciones de swapping (intercambio) -> IN/OUT.
- Debe tomar la decisión de si es necesario suspender un proceso -> almacenamiento secundario.
- También debe decidir cuándo volver a cargar en RAM un proceso suspendido.
- Modifica el grado de multiprogramación -> tratando de lograr una buena mezcla de procesos CPU/IO BOUND.
    - SWAP IN -> aumento
    - SWAP OUT -> disminución

**Ejemplos**

`Muchos procesos -> IO BOUND` $=>$ `Todos bloqueados -> CPU IDLE` $=>$ `Suspender procesos + cargar procesos CPU BOUND desde swap`

Completar más tarde

#### Planificador de corto plazo

- Comprende la decisión de a cuál de los procesos que en un momento se encuentran cargados en RAM listos para ejecutarse se le asignará CPU.
- Se ejecuta con mayor frecuencia que el resto -> debe tomar buenas decisiones + el overhead debe ser mínimo
- Es invocado cuando ocurre un evento que libera a la CPU o que provee la oportunidad de seleccionar otro proceso más “prioritario”. Eventos a tener en cuenta:
    - Interrupciones de I/O 
    - Llamadas al sistema
    - Señales

### Tipos de planificadores de Corto Plazo

- Dependiendo de qué eventos tenga en cuenta un algoritmo de planificación de corto plazo se clasificará en:
    - Con desalojo / Apropiativo / Preemptive.
    - Sin desalojo / No apropiativo / Non preemptive.

> Sin desalojo: Los planificadores que sólo tienen en cuenta los eventos que son obligatorios (los que liberan a la CPU) son llamados sin desalojo/No apropiativos/Non preemptive, ya que esperan a que el proceso le devuelva el control al SO para elegir otro proceso a ejecutar.

> Con desalojo: Los planificadores que además de considerar los eventos obligatorios consideran al menos UNO del resto de los eventos son llamados con desalojo/apropiativo/ Preemptive, ya que pueden interrumpir la ejecución de un proceso (desalojarlo de CPU -> vuelta a READY) para ejecutar otro más “prioritario”.

#### Criterios de replanificación

- Utilización de la CPU –> mantener la CPU tan ocupada como sea posible (maximizar)
- Rendimiento –> número de procesos que se completan por unidad de tiempo (maximizar)
- Tiempo de retorno –> tiempo transcurrido desde que se presenta el proceso hasta que se completa (minimizar)
- Tiempo de espera –> tiempo que un proceso pasa en la cola de procesos listos esperando la CPU (minimizar)
- Tiempo de respuesta –> tiempo que tarda un proceso desde que se le presenta una solicitud hasta que se produce la primera respuesta (minimizar / hacerlo previsible). Esto es lo que más le importa al usuario, la velocidad en el tiempo de respuesta.

#### Eventos de replanificación
**Siempre a tener en cuenta** (CPU Liberada)
- Proceso finaliza ( Running -> Finished) 
- Proceso se bloquea (Running -> Blocked)
- Proceso cede voluntariamente CPU ( Running -> Ready)

**Pueden ser considerados** (Puede convenir elegir otro proceso)
- Proceso recibe evento esperado (Blocked -> Ready)
- Proceso nuevo (Syscall : New -> Ready)
- Interrupción por timer

### Criterios de Algoritmos

#### Orientados al usuario
- Tiempo de respuesta
- Predictibilidad
- Cumplimientos de Deadlines

#### Orientados al sistema
- Utilización CPU
- Throughput
- Respetar prioridades
- Utilización de recursos
- Tiempo de espera
- Tiempo de ejecución

### Algoritmos para planificadores de corto plazo

#### FIFO

- Se atienden los procesos en orden de llegada a la cola de READY
- Es SIN DESALOJO, replafica cuando:
    - Proceso finaliza
    - Proceso se bloquea
    - Proceso libera CPU voluntariamente
    - (Los 3 items anteriores liberan CPU)

**Pros**

- Es simple
- Tiene poco **Overhead**
- Es “justo”, respecto al orden de llegada

**Contras**

- No optimiza métricas (throughput, tiempo de espera, tiempo de respuesta…).

#### SJF/SRT (Shortest job first)/(Shortest remaining time first)

**SJF**
- Atiende al proceso cuya siguiente ráfaga de CPU es más corta
- Es SIN DESALOJO, replanifica cuando:
    - Libera CPU

> **Para igual ráfaga, FIFO desempata**

**Pros**

-  Throughput
- Tiempo de espera promedio
- Tiempo de respuesta


**Contras**

- Un proceso puede monopolizar la CPU.
- Puede generar **starvation**.

> **Starvation**: Significa que puede generar que un proceso nunca se ejecute por tener este una ráfaga de CPU larguísima.

**SRT**

- Atiende al proceso cuyo remanente de la siguiente ráfaga de CPU (lo que no ejecutó aún) es más corto.
- Es CON DESALOJO, replanifica cuando: 
    - Libera CPU
    - Llega un proceso nuevo al sistema
    - Un proceso se desbloquea

**SJR vs SJF**

- SRT (con desalojo): Si llega un proceso a la cola de listos con una ráfaga de CPU más corta que el tiempo restante, se expropia.
- SJF (sin desalojo): Cuando se asigna la CPU a un proceso no se puede expropiar hasta que completa su ráfaga de CPU

**SJF/SRT es óptimo dado que da el mínimo tiempo de espera medio para un conjunto de procesos dado**

**¿Cómo sé cuál es la próxima ráfaga de los procesos que tengo encolados?, No podemos saber cuánto va a durar la próxima ráfaga… pero podemos estimarla**

**Estimación de ráfaga**

Se calcula como un promedio de la duración de las ráfagas anteriores:
- $Est(n)$ = Estimado de la ráfaga anterior
- $R(n)$ = Lo que realmente ejecutó la ráfaga anterior en la CPU
- $Est(n+1)$ = El estimado de la próxima ráfaga

$Est(n+1) =$ $\alpha$ $R(n) + ( 1 -$ $\alpha$ $) Est(n)$

con $\alpha \in [0,1]$

### Por Prioridades

- Se asocia con cada proceso una prioridad (número entero) 
- La CPU se asigna al proceso con la prioridad más alta (consideramos número pequeño ≡ prioridad alta)
- Tenemos dos posibilidades:
    - Sin desalojo
    - Con desalojo
- SJF se puede ver como un algoritmo de planificación por prioridad en el que la prioridad es la duración predicha para la siguiente ráfaga de CPU

**Pros**
- Permite garantizar prioridades establecidas.

**Contras**
- Starvation – los procesos de más baja prioridad podrían no ejecutarse nunca

**¿Cómo se podría resolver el problema de starvation?**

#### ¡Aging!

Vamos aumentando la prioridad del proceso hasta que llega a la máxima (0) y puede ser elegido. Pero... ¿Podemos aplicar aging a todos los algoritmos? No, pero el *agaig* da lugar al siguiente algoritmo

### HRRN (Highest Response Ratio Next)

Este algoritmo elimina POR COMPLETO la inanición (starvation). Su nombre indica su comportamiento, se prioriza a los procesos con mayor RR (Response Ratio).

$RR = (S + W ) / S => 1 + W / S$

Donde
- $S$= Duración próxima ráfaga CPU (service time)
- $W$= Tiempo de espera en READY (wait time) 

A mayor tiempo de espera $=>$ Mayor RR $=>$ Mayor prioridad
A mayor duración de ráfaga $=>$ Menor RR $=>$ Menor prioridad

- Es SIN DESALOJO, replanifica cuando:
    - Libera CPU

**Pros**
- Prioriza procesos IO bound pero sin generar starvation.

**Contras**
- Genera mucho **overhead**.
- También requiere estimación.

### Round Robin (RR)

- Atiende por orden de llegada dejando que ejecute como máximo un **QUANTUM** de tiempo.
- Es CON DESALOJO, replanifica cuando:
    - Libera CPU
    - Fin de $Q$ (interrupción timer)
- Si hay $n$ procesos en la cola de listos y el quantum es $q$, ningún proceso espera más de $q*(n-1)$ unidades de tiempo.
- No minimiza el tiempo de espera, pero lo hace muy previsible
- ¿Qué tamaño debería tener el quantum?
    - Demasiado grande → se comportaría como FIFO.
    - Demasiado chico → **overhead**.

**Pros**
- Respeta orden de llegada.
- Permite que todos ejecuten concurrentemente

**Contras**
- Puede generar mucho **overhead** (por process switch).

### Virtual Round Robin

Lo que ocurre en el RR es que se priorizan más los CPU Bound que a los I/O Bound, los cuales generalmente suelen tener ráfagas más cortas. A diferencia del Round Robin común, lo que va a hacer el VRR es darle más importancia a los I/O Bound, priorizarlos un poco más.

En el Virtual Round Robin van a existir dos colas de ready, el ready común y un ready +, que
va a ser más prioritario que el anterior. Supongamos que tenemos un proceso en ready, y el quantum es de Q = 10. En el momento de ejecutar un proceso, este ejecuta solo 2 ráfagas y se bloquea, entonces lo que va a suceder, es que este proceso luego de que se desbloquee va a ir a la cola de ready+ con un quantum de 8, ¿Y por qué 8?, porque se le va a restar el quantum dado (10) con las ráfagas que usó antes de bloquearse (2).

En el caso de que el quantum que ese proceso haya usado sea de 10 y se bloquee, cuando se desbloquee va a pasar a la cola de ready común, ya que no tendría sentido mandarlo a la cola ready+ con un quantum de 0
