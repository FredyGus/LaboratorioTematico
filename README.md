# Sistema CRUD de Estudiantes 📚✨

A continuación se describe el funcionamiento y la organización interna del código, dividido en tres archivos: **Estudiante.h**, **Estudiante.cpp** y **main.cpp**. Este proyecto gestiona un conjunto de estudiantes mediante operaciones CRUD (Crear, Leer, Actualizar, Eliminar) y almacena la información en un archivo llamado `estudiantes.txt`.

---

## Explicación del Código

### 1. Estudiante.h 📄

En este archivo se definen dos clases principales:

1. **`class Estudiante`**

   - **Atributos privados:**
     - `nombre` (tipo `std::string`)
     - `edad` (tipo `int`)
     - `calificacion` (tipo `float`)
   - **Constructores:**
     - Un constructor por defecto, que inicializa los atributos con valores por defecto.
     - Un constructor con parámetros para asignar valores a los atributos.
   - **Getters y Setters:**
     - Métodos `getNombre()`, `getEdad()`, `getCalificacion()` para leer los valores.
     - Métodos `setNombre()`, `setEdad()`, `setCalificacion()` para asignar nuevos valores.
   - **Método `toString()`**
     - Retorna una cadena con el formato `"nombre,edad,calificacion"`, utilizada para guardar o manipular la información como texto.

2. **`class EstudianteManager`**
   - Esta clase agrupa los métodos que realizan las operaciones CRUD directamente sobre el archivo de texto:
     - `menu()` muestra las opciones disponibles al usuario.
     - `addStudent()` crea un nuevo estudiante y lo escribe en el archivo.
     - `showStudents()` lee todos los estudiantes del archivo y los muestra en pantalla.
     - `averageStudents()` calcula el promedio de calificaciones recorriendo cada línea del archivo.
     - `searchStudent()` busca un estudiante por nombre, leyendo línea a línea y comparando.
     - `deleteStudent()` elimina un estudiante específico, copiando a un archivo temporal aquellos registros que no coincidan con el nombre buscado y reemplazando luego el archivo original.
     - (Opcional) `modifyStudent()` permitiría editar los datos de un estudiante existente siguiendo una lógica similar a la de eliminación (uso de un archivo temporal).

---

### 2. Estudiante.cpp 📝

En este archivo se implementan los métodos declarados en `Estudiante.h`.

#### Clase `Estudiante`

- **Constructores:**

  - Se define el constructor por defecto inicializando `nombre` como cadena vacía, `edad` en 0 y `calificacion` en 0.0.
  - El constructor con parámetros asigna los valores recibidos directamente a los atributos.

- **Getters y Setters:**

  - Se implementan para retornar o asignar valores a `nombre`, `edad` y `calificacion`.
  - De esta forma, se controla el acceso a los atributos privados de la clase.

- **`toString()`**
  - Devuelve una cadena con el formato CSV: `"nombre,edad,calificacion"`.
  - Facilita la escritura en el archivo `estudiantes.txt`.

#### Clase `EstudianteManager`

1. **`menu()`**

   - Muestra en consola las opciones disponibles (Agregar, Mostrar, Promedio, Buscar, Eliminar, etc.).
   - No realiza operaciones de archivo; solo imprime el texto del menú.

2. **`addStudent()`**

   - Crea un objeto `Estudiante` solicitando al usuario los datos: nombre, edad y calificación.
   - Valida que la edad sea positiva y la calificación esté entre 0 y 100.
   - Escribe los datos del estudiante al final de `estudiantes.txt` usando el método `toString()` o concatenando manualmente los campos.
   - ✅ _¡Nuevo estudiante agregado con éxito!_

3. **`showStudents()`**

   - Abre el archivo `estudiantes.txt` en modo lectura.
   - Lee cada línea con `getline`.
   - Divide manualmente la línea para extraer `nombre`, `edad` y `calificacion` (por ejemplo, usando `find` y `substr`).
   - Muestra en consola cada registro con un formato simple, evitando el uso de `<iomanip>`.
   - 👀 _Visualiza la lista completa de estudiantes._

4. **`averageStudents()`**

   - Recorre todas las líneas del archivo.
   - Suma las calificaciones y cuenta la cantidad de registros.
   - Muestra el promedio resultante si hay al menos un estudiante registrado.
   - 📊 _Obtén el promedio de calificaciones._

5. **`searchStudent()`**

   - Pide al usuario un nombre a buscar.
   - Lee línea por línea, extrae el campo `nombre` y lo compara con el que se busca.
   - Si coincide, muestra la información de ese estudiante.
   - Detiene la búsqueda en la primera coincidencia.
   - 🔍 _Encuentra y muestra la información del estudiante buscado._

6. **`deleteStudent()`**

   - Pide al usuario el nombre del estudiante a eliminar.
   - Crea un archivo temporal (por ejemplo, `temp.txt`).
   - Copia solo los registros que **no** coinciden con el nombre buscado, omitiendo el que se desea eliminar.
   - Al terminar, reemplaza el archivo original `estudiantes.txt` con el temporal si se encontró el registro.
   - 🗑️ _Elimina el estudiante seleccionado._

7. **(Opcional) `modifyStudent()`**
   - Similar a `deleteStudent()`, pero en lugar de omitir el registro encontrado, solicita los nuevos datos y los escribe con los valores modificados.
   - Al final, también reemplaza el archivo original por el temporal.
   - ✏️ _Modifica los datos de un estudiante existente._

---

### 3. main.cpp 🚀

- Declara un objeto de la clase `EstudianteManager` y, en un ciclo `do-while`, muestra el menú y solicita al usuario que elija una opción.
- Dependiendo de la opción seleccionada, llama a uno de los métodos CRUD (`addStudent()`, `showStudents()`, etc.).
- El ciclo se repite hasta que el usuario elija la opción de salir (por ejemplo, la opción `6`).
- 🔄 _El flujo principal del programa que permite interactuar con todas las funcionalidades._

---

## Comentarios Generales 📝

- El archivo de datos `estudiantes.txt` se crea o se abre cada vez que se realizan operaciones.
- Cada registro se almacena en una sola línea con el formato `Nombre,Edad,Calificacion`.
- Para la lectura, se utilizan métodos de la clase `std::string` (`find`, `substr`) en lugar de `sstream`, y se evita `<iomanip>` para formatear la salida.
- Los métodos de eliminación y modificación usan la técnica de crear un archivo temporal y luego reemplazar el original para evitar la carga completa de los datos en memoria.
- 🚀 _El diseño del código permite mantener la lógica de operaciones de archivo separada y organizada, facilitando su mantenimiento y ampliación._

¡Disfruta explorando y modificando este sistema CRUD! 😄👍
