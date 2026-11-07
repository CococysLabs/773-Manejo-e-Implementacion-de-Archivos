# Clase 3: Validación del comando MKDISK

Continúa la [clase 2](../clase-2/README.md). Se reemplaza el `mkdisk` simulado por una **implementación real de la validación de parámetros**.

## ¿Qué se agregó o cambió respecto a la clase 2?

### Nuevos archivos (carpeta `Commands/`)

| Archivo | Descripción |
|---|---|
| `Commands/CommandResult.h` | Struct genérico `CommandResult { bool success; std::string message; }` que devuelven todos los comandos: indica si los parámetros fueron válidos y el mensaje de éxito o error. |
| `Commands/Mkdisk.h` / `Mkdisk.cpp` | Declara e implementa `Commands::Mkdisk_Command(tokens)`. |

### Cambios en `Analyzer/Analyzer.cpp`

- Se incluye `Commands/Mkdisk.h`.
- Se comenta el `Mkdisk_Command` simulado.
- En la rama `mkdisk` ahora se llama a `Commands::Mkdisk_Command(params)`. Si `result.success` es `true` se imprime el mensaje; si no, se marca el error con `hasError`/`errorMsg`.

`main.cpp` y el `Makefile` no cambian.

## ¿Cómo valida `Mkdisk_Command`?

1. Une los tokens en un solo string y busca los parámetros válidos con una **expresión regular** (insensible a mayúsculas):
   `-size=\d+ | -unit=[km] | -fit=[bfw]{2} | -path="..." | -path=...`
2. Si la cantidad de coincidencias no calza con la cantidad de tokens, identifica el token inválido y devuelve `Parametro no reconocido`.
3. Recorre cada parámetro (`clave=valor`, quitando comillas si las hay) y valida:
   - `-size`: entero positivo (se usa `std::stoi` y se verifica que consumió todo el texto).
   - `-unit`: `K` o `M`.
   - `-fit`: `BF`, `FF` o `WF`.
   - `-path`: no vacío.
4. Valida que existan los obligatorios (`-size`, `-path`) y asigna **valores por defecto**: `unit = M`, `fit = FF`.
5. Devuelve un `CommandResult` con un mensaje del estilo:
   `MKDISK: Parametros validados con exito -> size=3000, unit=M, fit=FF, path=...`

> En esta clase **todavía no se crea ningún archivo**: solo se reconocen y validan los parámetros.

## Compilar y ejecutar

```bash
make run
```
