# 2° Parcial Sistemas Operativos 1C 2023 TM

## Teoría

1. Compare el esquema de permisos “Unix” (propietario/grupo/otros) con el esquema de ACL en términos de espacio en disco y granularidad de permisos. ¿Qué impacto tendría copiar un archivo de EXT2 a FAT32 en términos de permisos? ¿Qué sucedería al revés?
2. Compare en qué medida sufren cada tipo de fragmentación los esquemas de paginación y segmentación paginada.
3. Indique si las afirmaciones son verdaderas o falsas, justificando en ambos casos:
   1. Es posible realizar un hardlink entre archivos de diferentes volúmenes, siempre y cuando ambos estén formateados con File Systems de tipo UNIX (ext2).
   2. La principal ventaja de utilizar paginación jerárquica sobre paginación regular es que los accesos son mucho más rápidos si se utiliza una función de hash para realizarlos
4. El acceso a una dirección en segmentación paginada (sin memoria virtual) ¿Cuántos accesos
a memoria principal puede tener como máximo? ¿Cambiaría la respuesta con tabla de
páginas jerárquica?
5. En un FS con asignación de bloques enlazada pura ¿Tendría sentido realizar una
compactación cada determinado tiempo? Justifique.

## Práctica

1. Se dispone de un filesystem de tipo FAT32 en el que existe un directorio “c:\carpeta1” con dos archivos: “a.txt” (de 5002 bytes de tamaño) y “b.txt” (de 140885 bytes de tamaño).
   1. Suponga que se desean realizar las lecturas: Desde el byte 10 al byte 5000 de “a.txt”, y desde el byte 59023 al byte 140875 de “b.txt”. Indique la cantidad de accesos a la tabla FAT y clusters de disco para realizar dichas lecturas.
   2. Suponga que ambos archivos se truncan, pasando a ocupar 100 bytes cada uno. Indique la cantidad de modificaciones sobre entradas de la tabla FAT y sobre clusters de disco para realizar dichas operaciones

*Notas:*

- La fragmentación interna máxima de un archivo es de 4095 B.
- El archivo directorio “c:\carpeta1” no se encuentra en memoria y tiene un tamaño de 1536 B.
- Todos los clusters accedidos recientemente se mantienen en un buffer en memoria.
- La tabla FAT se encuentra en memoria

2. Un sistema utiliza paginación jerárquica bajo demanda, dedicando igual cantidad de bits para sus 2 niveles. Actualmente la TLB está completa y utiliza el algoritmo de reemplazo LRU. Se sabe que la última referencia del proceso A fue la dirección 02013333h la cual no generó ninguna interrupción al ser ejecutada. El proceso PB acaba de ser desalojado y comienza a ejecutar el PA con el siguiente estado (valores de marcos y páginas en hexa).
    1. Indique cantidad de PFs, accesos a la TLB (hit/miss) y las direcciones físicas al traducir las siguientes direcciones lógicas del proceso A: 02031010h – 04021111h – 02002424h – 01044444h.
    2. Muestre el estado final de la TLB y de las TPA actuales y nuevas si hubiere

*Notas:*

- Las últimas referencias fueron a los marcos: 2C - 14 - 15 - 3A, siendo 3A el que hace más tiempo fue accedido y 2C el más reciente.
- Asuma que los frames 10, 1B y 1F están libres para asignarse a las páginas y tablas del proceso A y que las únicas páginas presentes del proceso son las mostradas.

3. Un sistema cuenta con 4 KiB de memoria y utiliza Segmentación simple sin memoria virtual con 16 bits de direccionamiento. Sabiendo que un proceso A en un momento dado cuenta con 3 segmentos de los que se sabe:

- La dirección lógica 0608h corresponde a la última dirección válida del segmento 1.
- El segmento 0 y el segmento 1 están contiguos en memoria y tienen el mismo tamaño.
- El segmento 0 está situado al comienzo de la memoria y el segmento 2 al final.
- El segmento 2 tiene el máximo tamaño posible en este sistema.
    1. Represente la tabla de segmentos del proceso A para el estado actual.
    2. Suponiendo que el resto de la memoria está libre pero que pronto se necesitarán cargar nuevos segmentos, ¿Tendría sentido compactar en este momento?

    El sistema además implementa un FS de tipo ext2 con punteros de 32 bits y tamaño de bloque de 1 KiB. Los inodos contienen 12 punteros directos, 1 indirecto simple y 1 indirecto doble. Sabiendo que un proceso tiene el puntero del archivo en la posición 15000:

    3. ¿Cuántos accesos a bloques serán necesarios para leer 1000 bytes desde esa posición?
    4. ¿Cuál es el tamaño máximo teórico para un archivo en este FS?

## Respuestas Teoría

### 1

||UNIX|ACL|
|-|-|-|
|**Espacio de Disco**|Poco Espacio|Mucho más espacio por tener un permiso por cada usuario|
|**Granularidad**|Poca Granularidad|Mucha granularidad por especificar el permiso de cada usuario|

Copiar de EXT2 a FAT32 implicaría perder los permisos ya que FAT32 no posee un esquema de permisos por archivo. Al revés sería necesario setear algunos permisos por defecto, dado que no existirían en FAT32.
