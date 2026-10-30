# Registro de Personas y Manejo de Archivos Binarios en C++

## Descripción

Este programa está desarrollado en **C++** y permite registrar información personal, almacenarla en un vector de estructuras y guardar los registros en un archivo binario para su posterior lectura.

El sistema solicita al usuario los nombres, apellidos y correo electrónico de una persona. Posteriormente, permite almacenar los datos en un archivo binario y leerlos para mostrar la información registrada en la consola.

## Funcionalidades principales

- **Ingreso de datos:** solicita los nombres, apellidos y correo electrónico de una persona.
- **Almacenamiento en memoria:** utiliza un vector de objetos `Persona` para guardar los registros.
- **Creación de archivos binarios:** genera un archivo en modo binario para almacenar los datos.
- **Escritura de registros:** guarda la información de las personas utilizando `ofstream` y el método `write()`.
- **Lectura de archivos binarios:** recupera los registros almacenados mediante `ifstream` y el método `read()`.
- **Visualización de información:** muestra los nombres, apellidos y correos electrónicos recuperados del archivo.
- **Validación de archivos:** verifica si el archivo puede abrirse correctamente antes de realizar operaciones de lectura o escritura.

## Estructura de los datos

Cada persona contiene los siguientes campos, definidos en el archivo `datos.h`:

| Campo | Descripción |
|---|---|
| `nombre` | Nombres de la persona. |
| `apellido` | Apellidos de la persona. |
| `correo` | Correo electrónico de la persona. |

## Funciones principales

- `ingresarDatos()`: solicita la información de una persona y agrega el registro al vector.
- `crearArchivoBinario()`: crea un archivo binario y escribe los registros almacenados en el vector.
- `leerArchivoBinario()`: lee los registros del archivo binario y muestra sus datos en la consola.

## Tecnologías utilizadas

- **Lenguaje:** C++.
- **Biblioteca `iostream`:** entrada y salida de datos por consola.
- **Biblioteca `limits`:** permite limpiar el búfer de entrada utilizando `numeric_limits`.
- **Biblioteca `fstream`:** lectura y escritura de archivos.
- **Biblioteca `vector`:** almacenamiento dinámico de registros en memoria.
- **Archivos binarios:** almacenamiento de datos mediante `ios::binary`, `write()` y `read()`.

## Flujo de funcionamiento

1. Se solicita la información personal del usuario.
2. Los datos se almacenan en un vector de tipo `Persona`.
3. Se crea un archivo binario para guardar los registros.
4. Se escriben los datos en el archivo.
5. Se abre el archivo para leer la información almacenada.
6. Se muestran los registros recuperados en la consola.

## Objetivo

Practicar el manejo de estructuras de datos, vectores y archivos binarios en C++, comprendiendo cómo almacenar y recuperar registros de forma persistente mediante operaciones de lectura y escritura de archivos.