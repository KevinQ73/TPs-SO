# 1° Parcial Sistemas Operativos 2C 2022 TT

## Teoría 

1. **Describa los modos de ejecución en una computadora. ¿Cuáles son los eventos que podrían generar un cambio hacia modo kernel?**

Hay dos modos de ejecución, el modo usuario y el modo privilegiado o kernel. 

En el primer modo, las peticiones son limitadas ya que no tienen permiso de ingresar o modificar datos sensibles del equipo. Se pueden ejecutar instrucciones que estén disponibles en el CPU, y lo usa el SO.

El modo kernel es el modo completo, el cual se usa para poder ejecutar instrucciones privilegiadas. Lo usan los procesos

Los eventos que generar un cambio a modo kernel son las syscalls y las interrupciones.

2. **En caso de disponer de un SO con soporte para hilos a nivel kernel, indique cuáles atributos del proceso/hilo estarían exclusivamente en el PCB y cuales en el TCB (brinde al menos 2 ejemplos para cada caso). ¿Podría un hilo en este sistema leer la información de su TCB?**

Exclusivamente en PCB: PID, PPID, recursos asignados (archivos, memoria), limites de memoria

Exclusivamente en TCB: contexto de ejecución, estado, puntero a la pila

Un hilo no podría leer su TCB, dado que al ser un hilo de kernel su estructura se encuentra en espacio del sistema operativo.

3. **Responda por V o F justificando en ambos casos**
 - a. Si una biblioteca de ULTs utiliza un algoritmo sin desalojo y las I/O se realizan invocando directamente a las syscalls, es imposible que ocurra un thread switch sin que un hilo finalice.
- b.  Un semáforo con espera activa es una solución menos performante en todos los casos

a. **Verdadero**. Si se utilizan directamente las syscalls y no las funciones previstas por la biblioteca, no existe jacketing posible, por lo que cuando se bloquee el ULT, se bloquearan las otras hasta que esta finalice, más allá de que el planificador sea con desalojo o no ya que ni va a llegar a replanificar.

Al no conocer la entrada salida y al ser el algoritmo no expropiativo, sería imposible que la biblioteca decida cambiar de hilo sin que el mismo finalice, ya que una vez pase a ejecutar un hilo, nunca volvería a encolarse (no lo haría luego de una entrada salida, y la biblioteca nunca lo desalojaría).

b. **Falso**. Si tenemos más de una CPU y la sección crítica es pequeña, es más eficiente una espera activa ya que nos ahorramos los bloqueos y desbloqueos de, con sus respectivos cambios de contexto que esto genera, en resumen, menos overhead.

4. En un sistema que utiliza la estrategia de detección y recuperación de deadlock, ¿Cuáles son las acciones que podría tomar el mismo para solucionar un deadlock? ¿Qué criterios podría usar en cada caso para seleccionar las “víctimas”?

Las acciones que podría tomar son la de finalizar procesos o sacarle recursos a un proceso.

En la primera, se puede desalojar todos los procesos involucrados en el deadlock pero tiene un alto precio, o eliminarlos uno a uno hasta que se solucione el deadlock, este genera más overhead porque tendría que seleccionar a su victima, y correr el algoritmo cada vez que eligió a una.

Y si se quiere desalojar recursos, será necesario volver al proceso expropiado a un estado seguro desde el cual pueda reanudar su ejecución, además de que puede llegar a generar inanición si es que un proceso continuamente es elegido como víctima.

Los factores a considerar para seleccionar victimas son la prioridad, el tipo de proceso, cuanto tiempo lleva ejecutando y cuantos o que tipo de recursos utiliza.

5. ¿Por qué los semáforos necesitan soporte del sistema operativo? ¿Qué los diferencia de una solución de software?

Los semáforos ejecutan su código de manera atómica para no tener condición de carrera, además de que en su implementación, bloquean procesos, por lo que necesitan soporte del SO. Mientras que las soluciones de SW como la de Peterson emplea espera activa, que es más complicado de codíficar, está casi limitado a dos procesos.

## Práctica

1. [Solución](https://docs.google.com/spreadsheets/d/17VahbgO3byOm2pTxiAkE1_c8vRGTHkQeqYrhmqlShsQ/edit#gid=0)

2. [Solución](https://docs.google.com/spreadsheets/d/17VahbgO3byOm2pTxiAkE1_c8vRGTHkQeqYrhmqlShsQ/edit#gid=303552335)

3. [Solución](https://docs.google.com/spreadsheets/d/17VahbgO3byOm2pTxiAkE1_c8vRGTHkQeqYrhmqlShsQ/edit#gid=261007182)