# Sincronización

## Índice

### Condición de carrera

Tenemos estos 3 procesos

**Proceso 1**

    while(1){
        agregarTarea();
        tareasPendientes ++;
    }

    registro = tareasPendientes
    registro = registro + 1
    tareasPendientes = registro

**Proceso 2**

    while(1){
        agregarTarea();
        tareasPendientes --;
    }

    registro = tareasPendientes
    registro = registro - 1
    tareasPendientes = registro

**Proceso 3**

    while(1){
        if(tareasPendientes == 0){
            printf("No hay tareas pendientes");
        }
    }

    registro = tareasPendientes
    cmp registro 0
    jz (ejecuta printf)
    jnz (sale del if)

Supongamos que estos 3 procesos se ejecutan en paralelo, con un algoritmo de planificación **RR** con un quantum muy chico, y que `tareasPendientes = 10`. Si nosotros ponemos ejecutar el proceso 1, supongamos que llegamos a ejecutar la línea `registro = registro + 1`, y justo después salta el quantum, bien, pasa al proceso 2. En el proceso dos hace lo mismo pero lo resta, `registro = registro – 1`, y salta el quantum, vuelve al proceso 1, y posteriormente al 2 cuando nuevamente salte el quantum.
¿Cuál es el punto de mostrar este ejemplo? Que en el proceso 1, `tareasPendientes` puede llegar a quedar igual a 11 y en el proceso 2, igual a 9, ¿qué problema no? Veamos por qué se da este fenómeno y cómo se puede resolver.

> Condición de carrera: Es una situación en la que varios procesos/hilos manipulan datos *compartidos concurrentemente* de forma de que el *resultado* de la ejecución depende del *orden* paricular en que se terminan ejecutando

Hay que asegurar que **sólo un proceso/hilo** pueda acceder a estos datos a la vez para garantizar la coherencia de los mismos, para ellos hay que **sincronizarlos**. Esto es lo que se denomina **Región Crítica**

Pero, pero... **¿Siempre que más de un proceso acceda a datos compartidos tengo que sincronizarlos?**

No necesariamente, Sincronizar cobra sentido cuando algunos/s de los procesos que usan un recurso compartido, editan sobre dicho recurso. Si los procesos concurrentes no modifican los datos compartidos, no es necesario. Si todos los que usan dicho recurso compartido SOLO lo estuvieran LEYENDO, no se provocaría esta condición de carrera.

### Región Crítica

#### ¿Cuándo puedo tener una condición de carrera?

Es lo que se denomina *Condiciones de Bernstein*

- Más de un proceso/hilo usando el mismo recurso
- Al menos uno de los que usa ese recurso lo está modificando
- Los accesos a dicho recurso se realizan en forma concurrente


#### ¿Como tiene que ser la región crítica?

- Debe contener alguna operación sobre un **recurso compartido**
- Debe ser lo más **chica** posible
- Debe ejecutarse en forma **atómica**, es decir, que al momento de ejecutar una instrucción, se ejecute como UNA sola o directamente NO se ejecute, como en el caso de `tareasPendientes++`, que no tenga que ejecutar una línea y saltar a otra diferente, sino que el ciclo de instrucción se haga completo.

#### Requerimientos para la solución al problema de la sección crítica

- **Mutua exclusión**: Sólo un proceso puede acceder a su sección crítica a la vez.
- **Progreso**: Sólo los procesos que se encuentren en la sección de entrada o de salida pueden participar en la decisión de qué proceso puede ingresar en la sección crítica.
- **Espera limitada**: Tiene que haber un límite en la cantidad de veces que otros procesos pueden ingresar a la sección crítica luego de que un proceso pide ingresar en la misma, es decir, un proceso no debería esperar indefinidamente para ejecutar su sección crítica.
- **Velocidad de los procesos**: La solución debe funcionar sin importar cómo los procesos usen sus secciones críticas, es decir, si las mismas son largas, cortas, si las utilizan muchas o pocas veces.

#### Soluciones para las condiciones de carrera

Existen dos tipos, las soluciones a nivel software y a nivel hardware. El tema está en que las soluciones a nivel software como son con uso conjunto de `while` y arrays, o la denominada *solución de Peterson* son muy tediosas de programar, por lo que dieron lugar a las soluciones a nivel hardware

#### Soluciones a nivel Hardware

El HW nos puede dar soporte para resolver el problema de la SC en forma sencilla y eficiente:

**Deshabilitar interrupciones**

    deshabilitarInterrupciones();

    SECCIÓN CRÍTICA

    habilitarInterrupcioens

    SECCIÖN RESTANTE

**Pros**
- No permite que se cambie de proceso una vez en la SC en forma sencilla

**Contras**
- Costo de enviar mensaje a cada CPU
- Baja eficiencia uso CPU
- El proceso tarda más en ingresar a la SC

**Instrucciones atómicas** (TEST AND SET // SWAP AND EXCHANGE)

    while ( TestAndSet (&lock ));
    //    sección crítica
    lock = FALSE;
    //    sección restante

*Funcionamiento TestAndSet*

    boolean TestAndSet (boolean *target) {
            boolean rv = *target;
            *target = TRUE;
            return rv:
    }

**Pros**
- Algunos sistemas proveen instrucciones que permiten validar el valor de una variable y modificarla en forma atómica 
- Son sencillos de usar
- Son eficientes incluso en sistemas multiprocesador

**Contras**
- No todos los sistemas tienen este soporte

El problema que puede llegar a tener esta solución es que se quede clavado en el while, y que por ende tarde mucho en setear a la variable lock en FALSE. Lo que estaría bueno implementar, es que en vez de dejar esperando a los demás procesos para entrar al while, directamente los bloquee. Lo que pasa es que el hardware no es capaz de bloquearlos, cosa que sí es posible para el sistema operativo (S.O). Por lo que ahora aparecen las ***soluciones a nivel SO***

### Soluciones a nivel SO: Semáforos

>*Def*: Un semáforo es una variable entera que es accedida únicamente por dos funciones atómicas (syscalls) wait y signal

    SEM = 1
    ...

    WAIT(SEM);

    SECCIÓN CRÍTICA

    SIGNAL(SEM)

    SECCIÓN RESTANTE

A diferencia del resto de las estrategias vistas, se puede implementar con o sin espera activa

**Con espera activa**

    wait (sem) {
        while (sem == 0); // no-op
        sem--;
    }

    signal (sem) { 
        sem++;
    }

**Con bloqueo**

    wait (S) { 
        valor --;
        if (valor < 0) { 
            block();  // Cola de espera del semáforo
        }
    }

    signal (S) { 
        valor ++;
        if (valor <= 0) { 
            wakeup(pid);  // Despierta al primero que se bloqueo
        }
    }

#### PTHREADS

Esta biblioteca nos brinda los dos tipos de semáforos

Con espera activa $=>$ pthreads_spinlock_t
Con bloqueo $=>$ pthreads_mutex_t

Como siempre priorizamos el buen uso de la CPU y no queremos desperdiciarlo con una espera activa, entonces... **¿Siempre es mejor usar la implementación con bloqueo?**

En ciertas situaciones puede ser más eficiente usar los spinlocks:
- Cuando hay más de 1 CPU
- Cuando la SC es chica

El proceso en espera activa continúa su ejecución más rápido, nos ahorramos el bloqueo/desbloqueo + cambios de contexto

#### Tipos de Semáforos

