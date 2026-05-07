*Este proyecto ha sido creado como parte del currículo de 42 por joaqumar.*

## 📝 Descripción
`get_next_line` es un proyecto fundamental del currículo de 42 cuyo objetivo es programar una función que devuelva una línea leída desde un **file descriptor**. 

El mayor reto del proyecto consiste en gestionar correctamente la memoria dinámica y las variables estáticas para que la función sea capaz de recordar dónde se quedó en lecturas anteriores, incluso si se manejan múltiples archivos simultáneamente.

### ⚡ Características Técnicas
*   **Buffer Acumulador:** Implementado para optimizar el rendimiento y reducir fragmentación.
*   **Multi-FD:** Capacidad para gestionar hasta 1024 archivos abiertos a la vez.
*   **Gestión de Memoria:** Limpieza estricta de leaks incluso ante errores de lectura.

## 🛠️ Instrucciones

### 📦 Compilación
Para utilizar la función, incluye el header y compila los archivos `.c`. Es obligatorio definir un tamaño de buffer:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl
```

### 🚀 Ejecución
Ejemplo básico de implementación en un `main.c`:

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd = open("test.txt", O_RDONLY);
    char *line;

    if (fd == -1)
        return (1);
    while ((line = get_next_line(fd)))
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

## 📚 Recursos

### 📖 Documentación clásica
*   **Man read(2):** Documentación oficial sobre la lectura de descriptores de archivo.
*   **Variables Estáticas:** Persistencia de datos en memoria durante la ejecución.
*   **Heap Management:** Gestión eficiente de `malloc` y `free`.

### 🤖 Uso de IA
En este proyecto se ha utilizado inteligencia artificial para las siguientes tareas:
*   **Norminette Check:** ⚖️  Refactorización para cumplir el límite de 25 líneas.
*   **Arquitectura:** 🏗️ Diseño y comprensión de la lógica del buffer intermedio.
*   **Documentación:** ✍️ Redacción y formateo del archivo README.md bajo los estándares de 42.
