# Guia Serialización para TP0 y TP

## Índice
- [TAD](#tad)
- [Stream](#stream)
- [Serializar](#serializar)
- [Estructuras Estáticas](#estructuras-estáticas)
- [Estructuras Dinámicas](#estructuras-dinámicas)

### TAD

Tipo abstracto de dato:
- Tiene informacion escondida bajo un nombre.
- Tiene operaciones asociadas.

En C tenemos los structs.

### Stream

Flujo de datos anónimo. Yo no sé que hay dentro, pero hay algo. El void* se usa en general para representar streams, son bytes que podes usarlo a tu conveniencia para interpretar a lo que necesites.

Como tener distintos tipos de datos generalmente va a generar un *padding* entre lo que ocupan en memoria, no se puede enviar todo por red porque no tenemos la certeza de que sean recibidos de la forma en que la necesitamos.

El tamaño de este padding depende de varios factores como, por ejemplo, el compilador, la arquitectura del CPU, el tipo de dato, entre otros. Por esto, es que no tenemos garantías de cuánto espacio ocupará un struct en memoria.

**Un ejemplo**
```
// Estructura de datos
typedef struct {
    uint32_t dni;
    uint8_t edad;
    uint32_t pasaporte;
    char nombre[14];
} t_persona;

// Operaciones asociadas
t_persona persona_crear(uint32_t dni, uint8_t edad, uint32_t pasaporte, char *nombre) {
    t_persona persona;
    persona.dni = dni;
    persona.edad = edad;
    persona.pasaporte = pasaporte;
    strncpy(persona.nombre, nombre, 14);
    return persona;
}
```

### Serializar

Consiste en pasar los datos que tenemos en esa TAD a un Stream, para eso hay que armar protocolos para que puedan interpretarse de la manera que a mi me convenga, es completamente arbitrario.

### Estructuras Estáticas

El protocolo propiciado por la cátedra es { [Header][Payload] } el cual el header es el tipo de mensaje, para que se prepare el servidor, y el payload, la data restante.

Para empezar, se reserva un bloque del heap donde almacenar el struct, y usando `memcpy()` se irá guardando en lo reservado. Así se ignorará el padding. Se empaqueta el buffer y se envía, de ahí se desempaqueta.

### Estructuras Dinámicas

Al no saber cuanto va a pesar el contenido a enviar hasta que se corra el programa, se recomienda colocar al protocolo el tamaño en bytes que necesita el destinatario para almacenar lo que enviamos. De ahú, hacemos los mismos pasos con el `memcpy()`.

Recomiendo leer de acá en adelante el como llevar a código la serialización y deserialización de nuestros streams [acá](https://docs.utnso.com.ar/guias/linux/serializacion#serialicemos)

Para entender un poco más de aritmética de punteros, dejo otro link [acá](https://docs.utnso.com.ar/guias/programacion/punteros)
