# Deadlock

## Índice

- [Recursos del sistema](#recursos-del-sistema)
- [Condiciones necesarias](#condiciones-necesarias)
- [Tratamiento de Deadlocks a nivel SO](#tratamiento-de-deadlocks-a-nivel-so)
    - [Prevención de Deadlocks](#prevención-de-deadlocks)
    - [Evasión de Deadlocks](#evasión-de-deadlocks)
    - [Detección y Recuperación de Deadlocks](#detección-y-recuperación-de-deadlocks)
        - [Detección](#detección)
        - [Recuperación](#recuperación)
- [Resumen](#resumen)
- [Livelock](#livelock)

### Recursos del sistema

- Los sistemas poseen recursos limitados
    - Recursos consumibles -> EJ: interrupción, señal, mensaje, info en IO buffers
    - Recursos reusables -> EJ: Memoria, archivos, dispositivos IO
- Los procesos para utilizar los recursos deben pedirlos y luego liberarlos a través de llamadas al sistema:
    - Recursos gestionados a través del SO -> open/close - malloc/free 
    - Recursos no gestionados por el SO -> wait /signal

Los recursos pueden tener más de una instancia (cualquiera satisface a un proceso por igual)

> *Def Deadlock*: Un conjunto de procesos estará en un estado de interbloqueo/deadlock cuando todos los procesos del conjunto estén esperando a que se produzca un suceso que sólo puede producirse como resulta­do de la actividad de otro proceso del conjunto. En un **deadlock**, los procesos nunca terminan de ejecutarse y los recursos del sistema están ocupados, lo que impide que se inicien otros trabajos.

**Ejemplo**

Con `mutex = 1; sem1 = 1; sem2 = 0;`

**P1**

    WHILE (true) {
        wait(sem1);  T1)
        wait(mutex); T3)

    SECCIÓN CRÍTICA

        signal(mutex);
        signal(sem2);
    }

**P2**

    WHILE (true) {
        wait(mutex); T2)  
        wait(sem2);  T4)

    SECCIÓN CRÍTICA

        signal(mutex);
        signal(sem1);
    }

El orden en que se realizan los waits genera un deadlock

### Condiciones necesarias

- **Exclusión mutua**. Al menos un recurso debe estar en modo no compartido (sólo un proceso puede usarlo a la vez). Si otro proceso solicita el recurso, el proceso solicitante ten­drá que esperar hasta que el recurso sea liberado.
- **Retención y espera**. Un proceso debe estar reteniendo al menos un recurso y esperando para adquirir otros recursos adicionales que actualmente estén retenidos por otros procesos.
- **Sin desalojo**. Los recursos no pueden ser desalojados; es decir, un recurso sólo puede ser liberado voluntariamente por el proceso que le retiene, después de que dicho proceso haya completado su tarea.
- **Espera circular**. Debe existir un conjunto de procesos en espera, tal que cada uno espere un recurso retenido por el siguiente.

### Tratamiento de Deadlocks a nivel SO

- Utilizar un protocolo para impedir o evitar los deadlocks, asegurando que el sistema nunca entre en dicho estado. **(PREVENCIÓN / EVASIÓN)**

- Permitir que el sistema entre en estado de deadlock, detectarlo y realizar una recuperación. **(DETECCIÓN Y RECUPERACIÓN)**

- Ignorar el problema y actuar como si nunca se produjeran deadlocks en el sis­tema.

#### Prevención de Deadlocks

- Proporciona un conjunto de métodos para asegurar que al menos una de las con­diciones necesarias no pueda cumplirse. 
- Se restringe el modo en que se pueden realizar las solicitudes. 
- Son políticas del SO definidas a priori

- *Prevenir*:
    - **Mutua exclusión**: evitar la mutua exclusión sobre recursos compartibles. Ej: apertura de archivos en modo lectura.
    - **Espera y retención**:
        - Los procesos pidan y se le asignen previamente todos los recursos que vaya a usar.
        - Un proceso para pedir un nuevo recurso tenga que liberar todos los que retiene.
    - **Sin desalojo**:
        - Si un proceso pide un recurso que no está disponible, debe esperar y se liberan todos los recursos que tenía asignados.
        - Si un proceso pide un recurso retenido por otro proceso en espera, los mismos son desalojados y asignados al primero
    - **Espera circular**: requerir que los recursos se pidan en orden.

#### Evasión de Deadlocks

Una forma más sofisticada que la prevención de deadlocks, es la evasión.

**¿Qué pasos vamos a seguir para llevar a cabo esta evasión?**

- El proceso debe indicarle al SO cuáles van a ser los recursos máximos que puede llegar a solicitar durante su tiempo de vida.

- Ante cada solicitud, se analizará si se le asigna el recurso al proceso o si se lo hace esperar. Para tomar una decisión se realiza una simulación teniendo en cuenta las posibles futuras solicitudes y liberaciones de recursos por parte de todos los procesos del sistema.

**¿Qué se hará en dicha “simulación”?**

- Mantiene al sistema siempre en **Estado Seguro**
    - Un estado es seguro si el sistema puede asignar recursos a cada proceso (hasta su máximo) en determinado orden sin que eso produzca un deadlock (existe una **secuencia segura**).
    - Si el estado es seguro $=>$ no existe ni existirá deadlock
    - Si el estado es inseguro $=>$ podría ocurrir deadlock
- Sólo se asigna un recurso si dicha asignación deja al sistema en estado seguro.
- Se podría utilizar un grafo de asignación de recursos para analizar el estado del sistema (agregando el tipo de arista **declaración** - - - > )

#### Detección y Recuperación de Deadlocks

##### Detección 

Al igual que el algoritmo del banquero, realiza una simulación de asignación de recursos, en este caso, para ver si puede satisfacer todas las peticiones actuales.

Estructuras necesarias
- Matriz de asignación
- Matriz de peticiones
- Vectores de recursos totales y disponibles

Tiene un coste significativo asociado
- Mantenimiento de la información necesaria y la ejecución del algo­ritmo de detección.
- Potenciales pérdidas inherentes al proceso de recuperación.

**¿Con qué frecuencia hay que correr el algoritmo de detección?**

Se corre cada intervalos regulares, buscando procesos que no puedan continuar ejecutando, aunque la frecuencia real depende mucho de cómo se programe el algoritmo.

##### Recuperación

*Finalizar procesos*
- Todos los intervinientes del deadlock → tiene un alto precio
- Finalizar de a uno hasta que se solucione el deadlock → tiene más trabajo asociado (elegir a la víctima + correr el algoritmo de detección nuevamente luego de la finalización del proceso)

*Desalojar recursos*
- Es necesario volver al proceso expropiado a un estado seguro desde el cual pueda reanudar su ejecución.
- Puede llegar a generar inanición si es que un proceso continuamente es elegido como víctima.

*Factores a considerar para seleccionar víctimas*:
- La prioridad y el tipo del proceso.
- Tiempo actual de ejecución.
- Cuántos y qué tipo de recursos ha utilizado o necesita.

### Resumen

|-|**Prevención**|**Evasión**|**Detección y recuperación**|
|-|-|-|-|
|**¿Cuándo se aplica?**|Petición|Asignación|Deadlock|
|**Flexibilidad en las peticiones**|Restringida por la política aplicada|Intermedia, los procesos deben declarar sus peticiones máximas|Flexible, cualquier solicitud puede realizarse|
|**Puede ocurrir deadlock**|No|No|Sí|
|**Overhead requerido**|Por lo general es poco, sólo se define en qué forma se realizan las peticiones|Alto, con cada petición se debe correr el algoritmo del banquero|Intermedio, depende de la frecuencia del algoritmo de detección|
|**Utilización correcta de los recursos**|Puede ser muy ineficiente dependiendo la estrategia|Por ser pesimista  se puede evitar asignar un recurso.|Puede llegar a ser ineficiente en caso de desalojos frecuentes|

### Livelock

- Es una situación similar al deadlock en la cual un conjunto de procesos no puede progresar en la ejecución de su trabajo pero, en este caso, los procesos siguen ejecutándose.
- Como los procesos no se encuentran bloqueados, es más complicada su detección.
