# Resolución 1° Parcial SO 29/05/2013

- **A1) Mencione y describa brevemente los estados de un proceso. Indique a qué tipo de planificación pertenece cada estado.**

**New**: Un proceso en new es un proceso con la PCB creada pero le faltan datos para su ejecución (No es planificable).

**Ready**: Su PCB está creado, está esperando que el SO lo asigne en la CPU para empezar a ejecutar. Es parte del planificador de corto plazo

**Running**: Las instrucciones se están ejecutando. Es parte del planificador de corto plazo

**Waiting**: El proceso se queda bloqueado esperando un evento. Es parte del planificador de mediano plazo

**Terminated**: Finaliza la ejecución del proceso. Es parte del planificador de largo plazo

- **A2) El modelo muchos a muchos multiplexa muchos ULT sobre un mayor número de KLT. (V/F). Justifique**

F. El modelo muchos a muchos multiplexa una cantidad $n$ de ULT sobre una cantidad MENOR O IGUAL de KLT. Esto es porque los ULT pasan desapercibido por el SO. Crear más KLT que los ULT existentes dejaria KLTs sin uso. En caso de que un KLT se bloquee, el SO podrá crear otro para seguir ejecutando los ULT, pero nunca será mayor al número de ULT, a lo sumo igual.

- **A3) Mencione y describa brevemente las clases más comunes de interrupcciones**

Una interrupción muy común, que ocurre al querer leer un disco, o al teclear algo en el teclado, hacer un click con el mouse, es una interrupción por I/O pero si hablamos de interrupciones comunes, serían las mascarables, ya que son el 98% de las mismas. Son interrupcciones que pueden ser deshabilitadas por el SO.

-**A4) Mencione y describa brevemente los tres métodos para tratar un interbloqueo (deadlock)**

- Prevención de Deadlocks: Utilizan un protocolo establecido para impedir una o más de las cuatro condiciones necesarias para que se de un deadlock, en la que se restringe el modo en el que se realizan las solicitudes de recursos de los procesos.

- Evasión de Deadlocks: Es una forma más sofisticada de prevenir deadlocks, en las que el SO le pide al proceso que le indique cuales son los recursos máximos que puede llegar a solicitar en su tiempo de vida, con esa petición, realizará una "simulación" teniendo en cuenta solicitudes futuras y liberaciones de recursos de otros procesos.

- Detección y recuperación de Deadlocks: Acá se deja que los deadlocks ocurran, pero cada cierta cantidad de tiempo, se corre un algoritmo que detecta los deadlocks y después de eso, se corre otro algoritmo que es el de recuperación, el cual es capaz de finalizar procesos o desalojar recursos necesarios para lograr que el deadlock desaparezca.

-**A5) Indique un algoritmo de planificación que sufra de *starvation* y describa brevemente su funcionamiento. ¿Que modificación realizaria sobre dicho algoritmo para evitar que se produzca el problema?**

El algoritmo por [prioridades](https://github.com/KevinQ73/TPs-SO/blob/main/1er%20Parcial/Planificacion/Planificacion.md#por-prioridades) asocia a cada proceso una prioridad con un número entero, y le asigna la CPU al proceso con prioridad más alta. Este puede ser con desalojo o sin desalojo, pero puede generar starvation ya que puede llegar un proceso con una prioridad baja y nunca ser seleccionada por el planificador. Se puede evitar que la probabilidad de que un proceso entre en starvation sea baja con una inteligente designación de las prioridades, pero para garantizar que no haya starvation, se aplica el aging, el cual irá aumentando la prioridad del proceso hasta la prioridad máxima en medida al tiempo que permanezca sin ser atendido. 
