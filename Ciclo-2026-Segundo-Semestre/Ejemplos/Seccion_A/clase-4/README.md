# Clase 4: Validación del comando FDISK y reorganización de carpetas

Continúa la [clase 3](../clase-3/README.md).

## ¿Qué se agregó o cambió respecto a la clase 3?

### Reorganización de `Commands/`

Cada comando pasa a tener su **propia subcarpeta**:

```
Commands/
├── CommandResult.h
├── Mkdisk_Command/   # antes: Commands/Mkdisk.h y Mkdisk.cpp (el código no cambia)
│   ├── Mkdisk.h
│   └── Mkdisk.cpp
└── Fdisk_Command/    # NUEVO
    ├── Fdisk.h
    └── Fdisk.cpp
```

### Nuevo comando: `Fdisk_Command`

Igual que `mkdisk` en la clase anterior, **solo valida parámetros** (aún no crea particiones). Usa una regex y valida:

| Parámetro | Obligatorio | Valores | Por defecto |
|---|---|---|---|
| `-size` | Sí | entero positivo | |
| `-path` | Sí | ruta del disco | |
| `-name` | Sí | nombre de la partición | |
| `-unit` | No | `B`, `K`, `M` | `K` |
| `-type` | No | `P` (primaria), `E` (extendida), `L` (lógica) | `P` |
| `-fit` | No | `BF`, `FF`, `WF` | `WF` |

Devuelve un mensaje como `FDISK: Parametros validados con exito -> size=..., unit=..., ...`.

### Cambios en `Analyzer/Analyzer.cpp`

- Se actualizan los `#include` a las nuevas rutas (`Mkdisk_Command/Mkdisk.h`) y se agrega `Fdisk_Command/Fdisk.h`.
- Se comenta el `Fdisk_Command` simulado y la rama `fdisk` ahora llama a `Commands::Fdisk_Command(params)` con el mismo manejo de `CommandResult` que `mkdisk`.

`main.cpp` y el `Makefile` no cambian.

## Compilar y ejecutar

```bash
make run
```
