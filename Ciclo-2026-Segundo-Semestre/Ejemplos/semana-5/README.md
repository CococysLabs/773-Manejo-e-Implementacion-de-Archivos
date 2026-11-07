# Clase 5: Creación física del disco con MKDISK (MBR)

Continúa la [clase 4](../clase-4/README.md). A partir de aquí `mkdisk` **crea realmente el archivo `.mia`** y le escribe el **MBR** al inicio.

## ¿Qué se agregó o cambió respecto a la clase 4?

### Nuevas carpetas

```
Structs/
├── Str_Mkdisk/   # MKDISK.h/.cpp: struct con los datos validados y creación del archivo
├── Str_Mbr/      # MBR.h/.cpp: estructura del MBR y su (de)serialización
└── Str_Partition/# PARTITION.h/.cpp: estructura de una partición
Utils/
└── Utilities.h/.cpp  # ConvertBytes: convierte size + unidad (K/M) a bytes
```

### Cambios en `Mkdisk_Command/Mkdisk.cpp`

Antes solo imprimía los parámetros validados. Ahora, tras la validación, llena un `Structs::MKDISK` (`Size`, `Unit`, `Fit`, `Path`) y llama a `Structs::Struct_MKDISK`. El mensaje final pasa a ser `MKDISK: Disco creado con exito -> ...`.

### Flujo de creación (`Struct_MKDISK`)

1. **`Utilities::ConvertBytes`**: convierte el tamaño a bytes (`K` = ×1024, `M` = ×1024×1024).
2. **`MakeDisk`**: crea las carpetas del `path` si no existen y escribe el archivo binario relleno de ceros, en bloques de 1 MB.
3. **`CreateMBR`**: arma el MBR y lo escribe en los primeros bytes del archivo.

### Estructuras (`#pragma pack(1)`, sin relleno entre campos)

**`MBR`**

| Campo | Descripción |
|---|---|
| `Mbr_size` | tamaño total del disco en bytes |
| `Mbr_date` | fecha de creación (timestamp Unix) |
| `Mbr_signature_disk` | número aleatorio que identifica el disco |
| `Mbr_disk_fit` | ajuste del disco (`B`, `F`, `W`) |
| `Mbr_partitions[4]` | las 4 particiones posibles |

**`PARTITION`**: `status`, `type`, `fit`, `start`, `size`, `name[16]`, `number`, `id[4]`. Las particiones del MBR se inicializan con `EmptyPartition()` (`status='2'` = disponible, `start=-1`, `size=-1`).

`MBR` incluye `SerializeMBR`/`DeserializeMBR` (escriben/leen la estructura binaria con `seekp`/`read` en la posición 0) y `Print()` para depuración.

### Otros cambios

- `main.cpp`: el `mkdisk` de prueba ahora crea un disco de 30 MB en una ruta real (`/home/jonatan/Descargas/Disco1.mia`). **Cambia la ruta por una válida en tu equipo.**
- `fdisk` y `mount` siguen siendo solo validación/simulación.

## Compilar y ejecutar

```bash
make run
```

Para revisar el MBR escrito puedes usar `xxd Disco1.mia | head`.
