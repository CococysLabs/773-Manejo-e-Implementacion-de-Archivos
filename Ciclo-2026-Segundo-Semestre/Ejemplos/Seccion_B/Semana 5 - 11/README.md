# Scanner de Comandos – Linux Proyecto 1


## Descripción

Este módulo está desarrollado en **C++** y forma parte del proyecto **Linux Proyecto 1**, cuyo objetivo es implementar un intérprete de comandos que permita al usuario ingresar instrucciones desde una terminal y ejecutar operaciones relacionadas con la administración de discos virtuales.

El programa presenta una interfaz interactiva en consola, recibe comandos escritos por el usuario, identifica la instrucción principal y procesa sus parámetros. Además, incluye funcionalidades para separar tokens, comparar comandos sin distinguir entre mayúsculas y minúsculas, mostrar mensajes de error y ejecutar instrucciones almacenadas en archivos de texto.

## Funcionalidades principales

- **Interfaz de consola:** muestra un menú interactivo con mensajes y colores ANSI.
- **Lectura de comandos:** recibe instrucciones ingresadas por el usuario mediante `getline()`.
- **Identificación de comandos:** reconoce la instrucción principal ingresada.
- **Análisis de parámetros:** separa y procesa los parámetros de cada comando.
- **Comparación de texto:** permite comparar comandos sin distinguir entre mayúsculas y minúsculas.
- **Validación de comandos:** identifica instrucciones no reconocidas y muestra mensajes de error.
- **Ejecución de operaciones de disco:** integra la clase `Disk` para procesar el comando `MKDISK`.
- **Ejecución de scripts:** lee instrucciones desde archivos de texto y las procesa secuencialmente.
- **Pausa de ejecución:** permite detener temporalmente la lectura de un archivo mediante la instrucción `PAUSE`.
- **Confirmaciones y respuestas:** incluye métodos para solicitar confirmaciones al usuario y mostrar mensajes de respuesta.

## Comandos reconocidos

| Comando | Descripción |
|---|---|
| `MKDISK` | Invoca la función encargada de crear discos virtuales. |
| `RMDISK` | Reconoce la instrucción para eliminar discos;
| `FDISK` | Reconoce la instrucción para administrar particiones;
| `MOUNT` | Reconoce la instrucción para montar discos o particiones; 


## Métodos principales

- `start()`: inicia la interfaz y el ciclo de lectura de comandos.
- `functions()`: identifica el comando ingresado y dirige su ejecución.
- `token()`: obtiene el comando principal de una instrucción.
- `split()`: divide una cadena utilizando un separador.
- `split_tokens()`: analiza los parámetros de una instrucción.
- `upper()`: convierte una cadena a mayúsculas.
- `compare()`: compara dos cadenas sin distinguir entre mayúsculas y minúsculas.
- `errores()`: muestra mensajes de error.
- `respuesta()`: muestra mensajes informativos.


## Ejemplo de uso

El intérprete identifica `MKDISK` como el comando principal, procesa los parámetros y delega la operación a la clase `Disk`.

También es posible ejecutar instrucciones almacenadas en un archivo de texto mediante la funcionalidad de ejecución de scripts.

## Tecnologías utilizadas

- **Lenguaje:** C++.
- **Bibliotecas estándar:** `iostream`, `string`, `vector`, `fstream`, `cstring`, `cstdlib` y `locale`.
- **Procesamiento de cadenas:** identificación y separación de comandos y parámetros.
- **Entrada y salida por consola:** lectura de instrucciones y presentación de resultados.
- **Manejo de archivos:** lectura de scripts con instrucciones.

## Objetivo

Desarrollar un intérprete de comandos que sirva como base para la administración de discos virtuales y particiones, aplicando conceptos de programación orientada a objetos, procesamiento de cadenas, estructuras de datos, manejo de archivos y validación de instrucciones.  

----
## Nota: este proyecto 1 prepara  toda la  parte del proyecto 2  
