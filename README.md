*Este proyecto ha sido creado como parte del currículo de 42 por gamercha.*

# Get Next Line

## Descripción

**Get Next Line** es un proyecto del currículo de 42 cuyo objetivo principal es implementar una función en C capaz de leer un archivo línea a línea, de forma eficiente y controlada.

La función `get_next_line` devuelve una línea completa leída desde un descriptor de archivo en cada llamada, incluyendo el salto de línea (`\n`) si existe. Este comportamiento permite manejar archivos grandes o flujos de datos sin necesidad de cargarlos completamente en memoria.

El proyecto pone el foco en:

* Gestión de memoria dinámica.
* Manipulación de buffers.
* Uso de descriptores de archivo (`file descriptors`).
* Manejo eficiente de lectura incremental.

---

## Instrucciones

### Compilación

Para compilar el proyecto, puedes usar `gcc` junto con los archivos obligatorios:

```bash
gcc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c -o gnl
```


---

### Uso

Ejemplo básico de uso:

```c
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd;
    char *line;

    fd = open("archivo.txt", O_RDONLY);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return 0;
}
```

---

### Ejecución

```bash
./gnl
```

Asegúrate de que el archivo a leer existe y tiene permisos adecuados.

---

## Características

* Lectura línea a línea sin cargar todo el archivo en memoria.
* Soporte para múltiples llamadas consecutivas.
* Manejo de buffers con tamaño configurable (`BUFFER_SIZE`).
* (Bonus) Soporte para múltiples descriptores de archivo simultáneamente.

---

## Algoritmo y Justificación

El algoritmo se basa en el uso de un **stash estático**, que permite guardar información entre llamadas a la función.

### Flujo del algoritmo:

1. **Lectura del archivo**
   - Se leen bloques de tamaño `BUFFER_SIZE` usando `read`.

2. **Acumulación**
   - El contenido leído se concatena con el stash usando `ft_strjoin`.

3. **Detección de salto de línea**
   - Se busca `\n` en el stash mediante `find_n`.

4. **Extracción de línea**
   - Se extrae la línea completa con `read_and_storage`.

5. **Actualización del stash**
   - Se elimina la línea ya leída con `update_stash`.

### Justificación

- Permite manejar archivos de cualquier tamaño.
- Evita perder información entre llamadas.
- Garantiza que cada llamada devuelve exactamente una línea.
- Divide la lógica en funciones pequeñas para cumplir la Norma.

---

## Decisiones Técnicas

* Uso de funciones auxiliares para:

  * Concatenación de strings.
  * Búsqueda de caracteres.
  * Gestión de memoria.
* Separación clara entre lógica principal y utilidades.
* Control estricto de errores en `read()` y `malloc()`.

---

## Recursos

### Documentación

* Manual de `read()` (man 2 read)
* Manual de `open()` (man 2 open)
* Documentación estándar de C (stdlib, unistd)

### Tutoriales y referencias

* Gestión de memoria dinámica en C
* Gestion de parametros de funcion `read()`
* Lectura de archivos en sistemas Unix

### Uso de IA

Se ha utilizado IA como apoyo en:

* Comprensión conceptual del flujo del algoritmo.
* Revisión de buenas prácticas en gestión de memoria.
* Mejora de la claridad en la documentación (README).

No se ha utilizado IA para la implementación directa del código principal, sino como herramienta de apoyo educativo.

---
