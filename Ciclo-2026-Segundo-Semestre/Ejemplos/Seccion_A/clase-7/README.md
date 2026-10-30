# Clase 7: Comando MKFS (formateo a EXT2)

Continúa la [clase 6](../clase-6/README.md). Se agrega el comando `mkfs`, que formatea una partición montada con un sistema de archivos **EXT2**.

## ¿Qué se agregó o cambió respecto a la clase 6?

### Nuevo comando `Commands/Mkfs_Command/Mkfs.h/.cpp`

- Parámetros: `-id` (obligatorio, id de una partición montada) y `-type` (solo acepta `full`, que es el valor por defecto).
- Ejemplo: `mkfs -id=611A`

### Nuevas estructuras del sistema de archivos (`Structs/`)

| Carpeta | Estructura | Descripción |
|---|---|---|
| `Str_Superblock/` | `SUPERBLOCK` | Metadatos del FS: tipo (2 = EXT2), contadores de inodos/bloques usados y libres, número mágico `0xEF53`, tamaños y posiciones de bitmaps, inodos y bloques. |
| `Str_Inode/` | `INODE` | `uid`, `gid`, `size`, fechas, `I_block[15]` (punteros a bloques, `-1` = sin usar), tipo (`0` carpeta, `1` archivo) y permisos. |
| `Str_Folderblock/` | `FOLDERBLOCK` | Bloque de carpeta: 4 entradas `FOLDERCONTENT` (nombre de 12 bytes + número de inodo). |
| `Str_Fileblock/` | `FILEBLOCK` | Bloque de archivo: 64 bytes de contenido. |

Todas tienen `Serialize`/`Deserialize` para escribir y leer en el disco en un offset dado.

El superbloque se divide en tres archivos: `SUPERBLOCK.cpp` (serialización), `BITMAPS.cpp` (crear y actualizar bitmaps) y `SISEXT2.cpp` (crear la carpeta raíz y `users.txt`).

### Flujo de `Create_MKFS`

1. **`GetMountedPartition`** (nueva función en `Global/MountedPartitions`): a partir del id obtiene una copia de la partición y la ruta del disco.
2. **Calcular `n`**, la cantidad de inodos:
   `n = floor((tamaño_partición − sizeof(SUPERBLOCK)) / (4 + sizeof(INODE) + 3 · sizeof(FILEBLOCK)))`
3. **Crear el superbloque** con la distribución de la partición:

   ```
   [ SUPERBLOCK ][ bitmap inodos (n) ][ bitmap bloques (3n) ][ inodos (n) ][ bloques (3n) ]
   ```
4. **`Create_Bit_Maps`**: inicializa ambos bitmaps con `'0'` (todo libre).
5. **`Create_UsersTXT`**: crea
   - Inodo 0 → carpeta raíz `/` con las entradas `.`, `..` y `users.txt`.
   - Inodo 1 → archivo `users.txt` con el contenido `1,G,root\n1,U,root,root,123\n`.
   - Actualiza bitmaps y contadores del superbloque.
6. **Guarda el superbloque** al inicio de la partición.

### Otros cambios

- `Analyzer.cpp`: la rama `mkfs` llama a `Commands::Mkfs_Command`.
- `main.cpp`: se agrega `mkfs -id=611A` al script de prueba (después del `mount`).

## Requisitos

Graphviz, igual que en la clase 6 (para el reporte `disk`).

## Compilar y ejecutar

```bash
make run
```
