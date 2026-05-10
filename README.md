*Este proyecto ha sido creado como parte del currículo de 42 por joaqumar.*

# 📑 Get_Next_Line - 42 Project

---

## 📝 Descripción

El objetivo de este proyecto es desarrollar una función que devuelva una línea leída de un **File Descriptor (fd)**. 

**Get_Next_Line (GNL)** es un reto fundamental en el currículo de 42 que profundiza en:
*   El uso de **variables estáticas** para preservar datos entre llamadas.
*   La gestión de **memoria dinámica** (`malloc` y `free`) para manejar strings de tamaño desconocido.
*   El manejo eficiente de buffers de lectura.
*   La capacidad de gestionar múltiples descriptores de archivo simultáneamente (Bonus).
*	Como característica adicional, esta versión permite configurar dinámicamente el carácter de finalización de línea mediante la macro `CUT_CHAR`.

---

## ⚙️ Instrucciones

### Compilación
Es necesario compilar la función definiendo el tamaño del buffer y, opcionalmente, el carácter de corte. Por defecto, `CUT_CHAR` es `\n`.

```bash
# Compilación estándar (corte por salto de línea)
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c

# Compilación personalizada (ejemplo: corte por comas para archivos CSV)
cc -D BUFFER_SIZE=42 -D CUT_CHAR="','" get_next_line.c get_next_line_utils.c main.c
```

### Ejecución
Una vez compilado, puedes ejecutar el binario resultante:

```bash
./a.out
```

---

## 🧠 Algoritmo y Decisiones Técnicas

### Justificación del uso de Listas Enlazadas
Para esta implementación, se ha optado por un algoritmo basado en **Listas Enlazadas Simples**. Las razones principales son:

1.  **Flexibilidad Dinámica**: La lista permite almacenar fragmentos de lectura de cualquier tamaño sin necesidad de reasignar y copiar la string completa en cada iteración, optimizando el uso del heap.
2.  **Gestión de Residuos**: El sobrante de una lectura (lo que queda después del carácter definido en `CUT_CHAR`) se gestiona de forma natural al limpiar la lista, manteniendo solo el nodo necesario para la siguiente llamada.
3.  **Modularidad y Norma**: El uso de listas facilita la división del código en funciones lógicas breves (menos de 25 líneas), encargadas de tareas atómicas como la creación de nodos y la extracción de la línea final.
4.  **Adaptabilidad**: La lógica de listas facilita la búsqueda de cualquier carácter delimitador sin comprometer la estructura de los datos almacenados.

---

## 📚 Recursos

### Referencias
*   [Documentación de la función `read(2)`](https://man7.org)
*   [Variables estáticas en C](https://geeksforgeeks.org)
*   [Linked Lists in C](https://learn-c.org)

### Uso de Inteligencia Artificial
En el desarrollo de este proyecto se ha empleado IA para las siguientes tareas:
*   **Refactorización**: Optimización de las funciones para cumplir con la Norminette tras la implementación de la lógica `CUT_CHAR`.
*   **Diseño Algorítmico**: Adaptación del algoritmo de búsqueda para soportar caracteres delimitadores dinámicos definidos mediante macros de preprocesamiento.
*   **Documentación**: Creación y formateo de este archivo `README.md`.
*   **Debugging**: Análisis de casos borde al utilizar caracteres de corte no convencionales (como espacios o caracteres nulos).

---

## 🛠️ Características
- [x] Lectura de archivos locales y entrada estándar (`stdin`).
- [x] Gestión de múltiples File Descriptors.
- [x] **Carácter de corte configurable** mediante `CUT_CHAR`.
- [x] Comportamiento estable con `BUFFER_SIZE` variable (1 a 10M).
- [x] Cero fugas de memoria comprobadas con Valgrind.

---
