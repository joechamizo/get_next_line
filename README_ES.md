# Get_Next_Line

## 👤 Descripción General del Proyecto y Colaboración con IA

Para mantener el proyecto comprensible, mantenible y alineado con el proceso de evaluación de 42, el desarrollo se estructuró en torno a requisitos de lectura dinámicos, una arquitectura rigurosa y segura para la memoria, y un flujo de trabajo adaptativo de revisión de código.

- **Arquitectura de memoria y estructura:** Diseñado e implementado un mecanismo personalizado de gestión de memoria utilizando listas enlazadas simples para salvaguardar los datos entre llamadas de ejecución sin depender de reasignaciones masivas de buffers.
- **Parseo dinámico:** Implementado una característica personalizada mediante la macro `CUT_CHAR`, lo que permite que la función se adapte a cualquier carácter delimitador dinámicamente en tiempo de compilación, en lugar de codificar de forma fija el tradicional carácter de salto de línea.
- **Arquitectura de bonus:** Desarrollado un sistema de seguimiento de múltiples descriptores de archivo (FD) utilizando arrays estáticos, permitiendo flujos de lectura independientes desde varios descriptores simultáneamente sin contaminación cruzada de datos.

---

## 📝 Descripción

**Get_Next_Line** es un proyecto algorítmico y de gestión de memoria escrito en C. El objetivo es programar una función que devuelva una línea leída desde un descriptor de archivo (file descriptor), produciendo una ejecución estable y libre de fugas de memoria independientemente del tamaño del buffer.

El proyecto se centra en:
- manipulación de variables estáticas para preservar el estado de seguimiento;
- movimiento de nodos dinámicos seguro para punteros dentro de listas enlazadas;
- parseo de flujos de archivos de entrada y manejo de errores;
- propiedad de la memoria en el heap y limpieza;
- optimización estructural del código bajo las restricciones de la Norminette de 42.

El programa lee de un descriptor de archivo o de la entrada estándar y devuelve la siguiente línea encontrada, terminando con el carácter de corte especificado.

---

## 📐 Decisiones Técnicas y Algorítmicas

El proyecto está construido alrededor de una arquitectura modular de listas enlazadas. El flujo de entrada se procesa en fragmentos (chunks), se guarda en nodos temporales y luego se aplana en una única asignación limpia de memoria una vez que se alcanza el delimitador.

### Justificación del Uso de Listas Enlazadas

Para esta implementación, se ha optado por un algoritmo basado en Listas Enlazadas Simples. Las razones principales son:
- **Flexibilidad Dinámica:** La lista permite almacenar fragmentos de lectura de cualquier tamaño sin necesidad de reasignar y copiar la string completa en cada iteración, optimizando el uso del heap.
- **Gestión de Residuos:** El sobrante de una lectura (lo que queda después del carácter definido en `CUT_CHAR`) se gestiona de forma natural al limpiar la lista, manteniendo solo el nodo necesario para la siguiente llamada.
- **Modularidad y la Norma:** El uso de listas facilita la división del código en funciones lógicas breves (menos de 25 líneas), encargadas de tareas atómicas como la creación de nodos y la extracción de la línea final.
- **Adaptabilidad:** La lógica de listas facilita la búsqueda de cualquier carácter delimitador sin comprometer la estructura de los datos almacenados.

---

## 🧠 Principios de Ingeniería Central y Guía de Defensa

### 1. Teoría de Variables Estáticas

Una variable estática en C se almacena en el Segmento de Datos (o segmento BSS si no está inicializada) de la memoria del programa, en lugar de en la pila (stack) o en el heap. Esto le permite preservar su valor entre llamadas consecutivas a funciones y persistir durante toda la vida útil de la ejecución del programa.

En esta implementación, el puntero estático actúa como el punto de entrada persistente a nuestra lista enlazada. Cuando se llama a get_next_line, verifica esta referencia estática para ver si hay datos sobrantes del flujo de lectura anterior.

Para la parte del bonus, en lugar de un único puntero, declaramos un array de punteros estáticos indexados por el descriptor de archivo: `static t_list *stack[OPEN_MAX]`. Esto asegura que cada descriptor de archivo retenga su propio estado independiente de la lista enlazada, permitiendo lecturas entrelazadas de múltiples fuentes sin contaminación cruzada de datos.

### 2. Gestión del Residuo del Buffer (Remainder)

Cuando el bucle de lectura detecta el carácter delimitador (definido por `CUT_CHAR`), la lista contiene la línea corriente más algunos datos residuales posteriores del último buffer leído. La seguridad de la memoria y la eficiencia se manejan en tres pasos sincronizados:

1. **Extracción de la Línea:** La función calcula la longitud exacta desde el inicio de la lista hasta el carácter delimitador, asigna la cantidad precisa de memoria en el heap y aplana el contenido del nodo en una sola cadena limpia y terminada en nulo para devolverla.
2. **Aislamiento del Residuo:** Una función de utilidad dedicada busca el delimitador dentro del último nodo procesado, aísla los datos sobrantes que lo siguen y crea un nodo completamente nuevo específicamente para albergar este residuo.
3. **Limpieza del Heap:** Todos los nodos precedentes que formaban la línea extraída se liberan por completo mediante `free()`. Luego, la variable estática se actualiza para apuntar exclusivamente al nuevo nodo residual. Esto deja el heap perfectamente optimizado y listo para la próxima llamada de get_next_line.

### 3. Manejo de Casos Borde (Edge Cases)

Para cumplir con los rigurosos estándares de 42, el código aborda explícitamente varias situaciones críticas en tiempo de ejecución:

- **Buffers Ultra Grandes (ej. BUFFER_SIZE=10M):** Evita el desbordamiento de la pila (stack overflow) asignando el buffer de lectura directamente en el heap (`malloc`) en lugar de definir arrays locales en la pila (`char buf[BUFFER_SIZE]`), eludiendo los límites del kernel.
- **Archivos sin Delimitador / EOF:** Si el archivo termina abruptamente sin encontrar `CUT_CHAR`, la estructura restante del buffer se extrae limpiamente como la cadena final, y el puntero estático de seguimiento se establece en `NULL` para indicar el final exitoso del flujo.
- **Errores Entrelazados a mitad del flujo:** Si una operación `read()` devuelve un error (`-1`) a mitad de la ejecución, la función libera inmediatamente todos los nodos acumulados previamente en la lista para eliminar por completo las fugas de memoria antes de devolver `NULL`.
- **Cadenas vacías o Archivos Binarios:** La lógica de la lista evalúa los bytes nulos y los bytes no convencionales de forma segura sin truncar los segmentos de lectura válidos de manera impredecible.

---

## 📊 Objetivos de Rendimiento

De acuerdo con los requerimientos del proyecto, el programa debe mantenerse dentro de los límites esperados bajo diferentes restricciones de buffer sin colapsar ni fugar memoria:

### Buffers Pequeños y Estándar (BUFFER_SIZE=1 a 42)
- Requisito mínimo: recuperación exitosa de la línea sin fugas de memoria.
- Buen rendimiento: mínima sobrecarga en la asignación de nodos.
- Rendimiento excelente: lectura instantánea con almacenamiento preciso del residuo.

### Buffers Grandes (BUFFER_SIZE=10M)
- Requisito mínimo: ejecución segura para la pila sin fallos de asignación de memoria.
- Buen rendimiento: uso estable de la memoria bajo cargas pesadas continuas.
- Rendimiento excelente: cero fragmentación del heap durante intercambios grandes de buffer.

---

## 🛠️ Uso

### Requisitos
- `cc`, `clang` o `gcc`
- Sistema basado en Unix como Linux o macOS

### Compilación

Compilación estándar (corte por carácter de salto de línea):
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c
```

Compilación personalizada (ejemplo: corte por comas para el procesamiento de archivos CSV):
```bash
cc -D BUFFER_SIZE=42 -D CUT_CHAR="','" get_next_line.c get_next_line_utils.c main.c
```

### Ejecución del Binario

Una vez compilado, puedes ejecutar el archivo binario resultante:
```bash
./a.out
```

---

## ❌ Manejo de Errores

El programa maneja descriptores de archivo inválidos y eventos inesperados en tiempo de ejecución con solvencia:
- devuelve `NULL` ante descriptores de archivo inválidos (`fd < 0`);
- devuelve `NULL` ante errores en la llamada al sistema de lectura (`read() == -1`);
- libera de forma segura todos los nodos de la lista asignados internamente si ocurre un error a mitad del flujo;
- se comporta de manera estable bajo caracteres de corte no convencionales (como espacios o caracteres nulos).

---

## 📚 Recursos y Uso de IA

### Referencias
- Enunciado de Get_Next_Line de 42
- Directrices de la Norminette de 42
- Documentación para la llamada al sistema `read(2)`
- Referencias generales sobre el alcance de las variables estáticas y listas enlazadas en C

### Declaración de Uso de IA

La asistencia de IA se utilizó como herramienta de apoyo durante el flujo de trabajo del proyecto, principalmente para:
- **Refactorización:** Optimización de funciones para cumplir con la Norminette tras implementar la lógica `CUT_CHAR`.
- **Diseño Algorítmico:** Adaptación del algoritmo de búsqueda para soportar caracteres delimitadores dinámicos definidos mediante macros de preprocesamiento.
- **Documentación:** Creación y formateo de la estructura de este archivo README.md.
- **Debugging:** Análisis de casos borde al utilizar caracteres de corte no convencionales (como espacios o caracteres nulos).

Todas las sugerencias generadas fueron revisadas, adaptadas, probadas y validadas manualmente con:
- `norminette`;
- `valgrind` (cero fugas de memoria verificadas);
- configuraciones de prueba extremas utilizando tamaños de buffer variables desde 1 hasta 10M.

La responsabilidad final del código, las pruebas y la defensa del proyecto sigue siendo del autor.
