# Resolucion 1° Parcial virtual 2C 2021

**1)** ¿Cuál de las siguientes afirmaciones es CORRECTA sobre los modos de ejecución?

- A. El modo kernel permite la deshabilitación de interrupciones de todo tipo (enmascarables, no enmascarables, excepciones, etc)
- **B. Las instrucciones privilegiadas siempre pueden ser ejecutadas en modo kernel**
- C. El sistema operativo es el encargado de impedir que un proceso ejecute instrucciones privilegiadas
- D. Ninguna es correcta
- E. Por seguridad, la única forma de transitar de modo usuario a modo kernel es a través de una syscall
- F. En una arquitectura microkernel, todas las rutinas del Sistema Operativo ejecutan en modo kernel

Falsas: 
- A) El modo kernel no puede deshabilitar las interrupciones de tipo no enmascarble por definición de interrupción no enmascarable
- C) El SO no va a impedir que un proceso ejecute una instruccion privilegiada, sino es el modo en el que esté el que lo haga, en todo caso es el HW el que evita la ejecución.
- E) No, para pasar de User a Kernel puede ser también para atender una interrupción
- F) En una arquitectura micro kernel, como su nombre lo dice, es hacer al kernel lo más chiquito posible, relegando rutinas como las del SO.


**2)** El uso de fork() y de execv()
    
- A. Ninguna de las opciones es correcta 
- B. El proceso que ejecuta fork() siempre debe esperar que el nuevo proceso ejecute execv() para proseguir con su lógica.
- C. El proceso que ejecuta fork() debe ejecutar execv() para modificar la imagen del proceso nuevo.  
- D. Como resultado de usar execv() después de un fork(), genera que haya dos procesos nuevos 
- **E. Llamar a fork() no siempre asegura que se creará un proceso nuevo.**

Falsas:
- B) No, el proceso no está obligado a cambiar su imagen. Pueden ser el y su hijo, procesos identicos o cuasidenticos. 
- C) No, execv() va a cambiar la imagen del proceso en el que estoy ejecutando, si es el mismo padre el que ejecuta execv(), va a cambiar su imagen, no la del hijo.
- D) No, execv() no es capaz de generar un proceso nuevo.

**3)** En el uso de hilos ULT en sistemas que no admiten KLT:

- A. Al menos para su creación y finalización, la biblioteca de hilos debe ejecutarse en modo kernel.
- B. Al menos para realizar el cambio de hilo de un mismo proceso, la biblioteca de hilos debe ejecutarse en modo kernel.
- C. Varios hilos ULT de un mismo proceso podrían estar en estado EJECUTANDO. 
- D. La técnica de jacketing es fundamental para que el hilo ejecutando no sea desalojado por una interrupción de Clock.
- **E. Ninguna afirmación es correcta**

Falsas:
- A) No, si necesitaran pasar por kernel, no serían ULT.
- B) Vuelvo a lo mismo, no, no lo necesita, son ULT. El SO no sabe de su existencia
- C) Los ULT no permiten pararelismos entre hilos pares.
- D) No, si el SO decide sacarte, te va a sacar por más que estes ejecutando. 

**4)** Analice la siguiente situación:

Un sistema que planifica con VRR se encuentra ejecutando al PD en el único procesador disponible. Mientras tanto los procesos PA-PB-PC se encuentran en ready (en la cola de menor prioridad en dicho orden). Por otro lado, PE se encuentra esperando una operación de disco en estado suspendido y PH se encuentra bloqueado esperando que se libere un mutex. 
PG se encuentra en estado new esperando ser admitido en el sistema  y por último PF se encuentra en estado finalizado. 
Como información extra, se sabe que PF fue el último proceso que ingresó al sistema y que en su momento fue requerido suspender a PE para poder cargarlo. 

Responda las siguientes preguntas para la situación planteada

**¿Cuál es el nivel de multiprogramación del sistema?**

- 5

**Si en dicho momento el planificador de mediano plazo decide volver a cargar a PE en memoria, ¿esto sería posible?**

- Sí, ya que se liberó la memoria ocupada por PF