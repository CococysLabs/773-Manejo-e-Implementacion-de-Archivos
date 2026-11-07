# Clase 6: FDISK, MOUNT y reporte DISK

Continúa la [clase 5](../clase-5/README.md). Se implementan las particiones reales (primaria, extendida y lógica), el montaje de particiones y el primer reporte con Graphviz.

## ¿Qué se agregó o cambió respecto a la clase 5?

### 1. Comando FDISK real

- **`Commands/Fdisk_Command/Fdisk.cpp`**: tras validar parámetros, llena un `Structs::FDISK` y llama a `Structs::Struct_FDISK`. El mensaje final es `FDISK: Particion creada correctamente`.
- **Nuevo `Structs/Str_Fdisk/FDISK.h/.cpp`**: convierte el tamaño a bytes y despacha según `-type`:
  - **Primaria**: lee el MBR, cuenta el espacio usado y las particiones primarias/extendidas (máximo 4), valida que quepa y la escribe en el primer slot libre.
  - **Extendida**: igual que la primaria, pero solo puede existir **una** por disco.
  - **Lógica**: se crea dentro de la extendida usando una **lista enlazada de EBR**. Cada EBR guarda `start`, `size` y `next` (`-1` si es el último); la partición lógica va justo después de su EBR.
- **Nuevo `Structs/Str_Ebr/EBR.h`**: estructura `EBR` (`Partition_mount`, `Partition_fit`, `Partition_start`, `Partition_size`, `Partition_next`, `Partition_name[16]`).
- **`Structs/Str_Mbr/MBR`** agrega métodos auxiliares:
  - `GetFirstPartitionAvailable`: primer slot libre y su byte de inicio.
  - `GetPartitionByName` / `GetPartitionByID`: búsqueda de particiones.
  - `UpdatePartitionNumber`: numera las primarias (1, 2, 3…) y deja 0 a la extendida.

### 2. Comando MOUNT (nuevo)

`Commands/Mount_Command/Mount.h/.cpp` con parámetros `-path` y `-name`:

1. Lee el MBR del disco y busca la partición por nombre.
2. Solo permite montar **primarias** (no extendidas ni lógicas) que no estén ya montadas.
3. Genera el **id** con el formato `<carnet><número de partición><letra del disco>`. Ejemplo: `611A` (carnet `61`, partición `1`, disco `A`). La letra se asigna por cada disco distinto (`Utilities::GetLetra`). **Cambia `Utilities::Carnet` por el tuyo.**
4. Registra el id en la tabla global y marca la partición como montada (`status='1'`), guardando el MBR actualizado.

### 3. Estado global (nuevo)

`Global/MountedPartitions.h/.cpp`: mapa `MountedPartitions` (id → ruta del disco) y `GetEssentialRep`, que dado un id devuelve el MBR y la ruta de su disco.

### 4. Comando REP y reporte DISK (nuevos)

- **`Commands/Rep_Command/Rep.h/.cpp`**: parámetros `-name`, `-id`, `-path` y `-path_file_ls`. Los nombres de reporte válidos están definidos (`mbr`, `disk`, `inode`, `block`, `bm_inode`, `bm_bloc`, `sb`, `file`, `ls`, `tree`), pero **en esta clase solo se implementa `disk`**.
- **`Reports/Rep_Disk/Disk.h/.cpp`**: `ReporteDISK` genera un archivo `.dot` con una tabla que muestra el MBR, las particiones, las lógicas y el espacio libre, con su porcentaje del disco, y lo convierte en imagen con `dot`.

### 5. Utilidades y `Analyzer`

- `Utils/Utilities` agrega: `Carnet`, `GetLetra`, `CreateParentDir` y `GetFileNames` (deriva el nombre del `.dot` a partir de la ruta de la imagen).
- `Analyzer.cpp`: `mount` ahora llama a `Mount_Command` y se agrega la rama `rep`.
- `main.cpp`: el script de prueba crea varias particiones (primarias, extendida y lógicas), monta una y genera el reporte `disk`.

## Requisitos

[Graphviz](https://graphviz.org/) instalado (`sudo apt install graphviz`), ya que el reporte ejecuta `dot -Tpng`.

## Compilar y ejecutar

```bash
make run
```
