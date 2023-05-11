# 1° Parcial 1C 2022 TM

### Teoría
**Responda brevemente las siguientes preguntas. Justifique**
1. Responda por V o F justificando en ambos casos.
    - a. La atención de una interrupción implica al menos un cambio de modo y un cambio de
contexto, independientemente de qué se esté ejecutando.
    - b. Una llamada al sistema (syscall) implica al menos un cambio de modo y un cambio de
contexto

**a.** F. Puedo estar atendiendo una interrupción y en ese momento que llegue otra y atenderla, por lo que no cambiaría de modo porque ya lo hice previamente.

**b.** V. Las syscalls son realizadas por los procesos de usuario, por lo que las mismas deben cambiar a modo Kernel no solo para poder cambiar de contexto sino también porque normalmente las mismas terminan ejecutando instrucciones privilegiadas

2. ¿Qué ventajas se podrían obtener de combinar KLTs con ULTs dentro de un mismo Proceso?
¿Sería posible forzar, desde el Sistema Operativo, a que todos los ULTs usados tengan
jacketing?

Se podría lograr manejar concurrencia sin bloquear distintos hilos, cuando por ejemplo realizaran tareas bloqueantes, mientras al mismo tiempo dentro de un KLT que sea cpu-bound realizar tareas concurrentes con muy bajo overhead.

No sería posible forzar jacketing para todos los ULTs, dado que el sistema operativo no puede forzar a que un proceso use una biblioteca en particular, y los ULTs no son administrados por el S.O.

3. Explique por qué un proceso suspendido puede no estar a la espera de un evento y dé un
ejemplo de cómo un proceso bloqueado puede llegar a ese estado.

Un proceso puede estar suspended ready. Digamos que un proceso está blocked pero el planificador decide suspenderlo, y mientras está en suspended waiting, ocurre el evento, por lo que pasaría a suspended ready, pero el planificador de mediano plazo todavía no decidió volverlo a restaurarlo a memoria.

4. ¿Sería recomendable utilizar semáforos mutex para acceder a una constante global en un
proceso multihilo? Justifique

No sería recomendable ya que, al ser una constante, estos accesos serán siempre de lectura, por lo que no habría una condición de carrera. Usar el semáforo de todas maneras generaría un overhead innecesario.

5. Un sistema implementa detección de deadlocks y muy frecuentemente encuentra que un grupo de procesos termina en esa situación por 2 recursos en particular. Al cambiar el código de los mismos para que pidan estos recursos en un orden estricto, el sistema deja de encontrar deadlocks tan frecuentemente. Explique por qué se da esa mejoría. ¿Podría implementarse fácilmente la misma estrategia para todo el sistema? Justifique.

Porque evito que se de la espera circular al modificarlos y hacer que se pidan en un orden estricto. De poder implementarlo puedo, nada me lo impide como programador, pero hay que saber que no sería fácil hacerlo y además eso me generaría un sistema demasiado restrictivo.
