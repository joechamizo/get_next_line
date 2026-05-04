Este proyecto ha sido creado como parte del currículo de 42 por joaqumar.📑 get_next_line📝 DescripciónEl proyecto get_next_line consiste en programar una función que devuelva una línea leída de un file descriptor.El objetivo principal es entender el comportamiento de las variables estáticas en C y aprender a gestionar la memoria dinámica de forma eficiente para que la lectura sea fluida y sin fugas.Esta implementación permite leer tanto de archivos como de la entrada estándar, devolviendo una línea completa (incluyendo el salto de línea) en cada llamada, bajo las estrictas restricciones de la Norma de 42.📂 Estructura del ProyectoEl código se organiza siguiendo la restricción de archivos exigida por el proyecto y la modularidad necesaria para el soporte de múltiples FDs:ArchivoResponsabilidad🚀 get_next_line.cLógica principal: coordinación de lectura, extracción y limpieza del stash.🛠️ get_next_line_utils.cFunciones de apoyo: gestión de memoria (substr, strdup) y manipulación de punteros.📋 get_next_line.hDefinición de prototipos, macros y la estructura necesaria para el buffer.⚙️ InstruccionesCompilaciónEl proyecto se compila junto a tu código principal definiendo el tamaño del buffer deseado mediante el flag -D:bashgcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl
Usa el código con precaución.EjecuciónPara utilizar get_next_line en tu programa, incluye el encabezado y llama a la función en un bucle:c#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd;
    char    *line;

    fd = open("test.txt", O_RDONLY);
    while ((line = get_next_line(fd)))
    {
        printf("%s", line);
        free(line);
    }
    return (0);
}
Usa el código con precaución.📚 RecursosDocumentación: Referencia de la llamada al sistema read(2) y gestión de variables estáticas.Tutoriales: Guías sobre manipulación de archivos en sistemas Unix y aritmética de punteros.Uso de IA: Se ha utilizado inteligencia artificial generativa para:Optimizar la búsqueda del salto de línea para lograr una complejidad O(n).Refactorizar las funciones de utilidad hacia un estilo basado íntegramente en punteros.Diseñar la estructura visual, la redacción y los saltos de línea de este archivo README.🏗️ Decisiones Técnicas: Algoritmo y Estructura de Datos💾 Gestión de Estado: static char *stashSe ha seleccionado un array de punteros estáticos para gestionar el "stash" o almacenamiento persistente.Justificación: Permite que la función sea multi-FD, manteniendo un almacén de memoria independiente para cada archivo (hasta 1024) sin que los datos se mezclen entre llamadas de distintos descriptores.⚡ Algoritmo de Búsqueda: Optimización O(n)A diferencia de versiones convencionales, este algoritmo solo busca el carácter \n en el nuevo fragmento leído, no en todo el acumulado.Justificación: Esto garantiza que la función sea instantánea incluso con archivos de miles de líneas y buffers gigantes, evitando la degradación de rendimiento por búsquedas redundantes.🎯 Manipulación de Datos: Aritmética de PunterosSe ha eliminado el uso de índices manuales (i, j) en favor de punteros directos y aritmética de direcciones.Justificación: El uso de expresiones como *dest++ = *s++ y la resta de punteros para calcular longitudes reduce la carga de la CPU y resulta en un código más profesional, compacto y eficiente.
