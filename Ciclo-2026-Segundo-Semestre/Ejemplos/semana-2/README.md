# Clase 2: Analizador de comandos (Analyzer)

Primer ejemplo del proyecto en C++. Se construye el **analizador** que recibe líneas de texto, identifica qué comando se escribió y lo despacha. Por ahora los comandos están **simulados**: solo devuelven un mensaje de éxito.

## Estructura

```
clase-2/
├── Analyzer/
│   ├── Analyzer.h       # Declaración de Analyzer::Analyze
│   └── Analyzer.cpp     # Lógica de análisis y despacho de comandos
├── main.cpp             # Define el script de prueba y lo envía línea por línea
└── Makefile             # Compilación automática de todos los .cpp
```

## ¿Cómo funciona?

1. **`main.cpp`** contiene un texto con varios comandos (`mkdisk`, `fdisk`, `mount`, una línea vacía y un comando inexistente). Lo divide en líneas con `splitLines` y llama a `Analyzer::Analyze` por cada una.
2. **`Analyzer::Analyze`** (en `Analyzer.cpp`):
   - Si no recibe nada, imprime un error.
   - Si la línea está en blanco, la imprime tal cual.
   - Separa la línea en tokens (`fields`), pasa el primero a minúsculas (`toLower`) y el resto son los parámetros.
   - Compara el primer token contra los comandos conocidos: `mkdisk`, `rmdisk`, `fdisk`, `mount`, `mkfs`, `mkusr`, `rmusr`, `mkfile`.
   - Si no coincide con ninguno, imprime `[ERROR] comando no reconocido: ...`.
3. Cada comando es, por ahora, una función `static` que solo retorna `"Comando 'xxx' ejecutado correctamente"`. Más adelante se reemplazan por la implementación real.

## Compilar y ejecutar

```bash
make run      # compila y ejecuta
make clean    # elimina build/ y el ejecutable
make rebuild  # limpia y recompila
```

El `Makefile` busca automáticamente todos los `.cpp` del proyecto, por lo que al agregar carpetas o archivos nuevos no hay que modificarlo.

## Salida esperada

```
Comando 'mkdisk' ejecutado correctamente
Comando 'fdisk' ejecutado correctamente
Comando 'mount' ejecutado correctamente


[ERROR] comando no reconocido: comandoinexistente
```
