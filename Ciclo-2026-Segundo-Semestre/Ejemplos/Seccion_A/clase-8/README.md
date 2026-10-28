# Clase 8: Reporte MBR y EBR

Continúa la [clase 7](../clase-7/README.md). Solo se agrega un nuevo reporte al comando `rep`.

## ¿Qué se agregó o cambió respecto a la clase 7?

### Nuevo reporte `mbr`

- **`Reports/Rep_Mbr/Mbr.h/.cpp`**: función `Reports::ReporteMBR`, que genera un `.dot` con una tabla y lo convierte en imagen con Graphviz (`dot -Tpng`).
- Contenido del reporte:
  - Datos generales del MBR: `MBR_SIZE`, `MBR_DATE` (fecha legible) y `MBR_DISK_SIGNATURE`.
  - Las **4 particiones** del MBR (incluso las vacías) con `PART_STATUS`, `PART_TYPE`, `PART_FIT`, `PART_START`, `PART_SIZE` y `PART_NAME`.
  - Si una partición es **extendida**, recorre la cadena de **EBR** (siguiendo `Partition_next` hasta `-1`) y muestra cada partición lógica con `EBR_STATUS`, `EBR_FIT`, `EBR_START`, `EBR_SIZE`, `EBR_NEXT` y `EBR_NAME`.

### Cambios en archivos existentes

- **`Commands/Rep_Command/Rep.cpp`**: se incluye `Rep_Mbr/Mbr.h` y se agrega la rama `reporte.Name == "mbr"` que llama a `ReporteMBR`.
- **`main.cpp`**: se agrega al script `rep -id=611A -path=.../repMBR.jpg -name=mbr`.

El resto del proyecto (comandos, estructuras, `Makefile`) es idéntico a la clase 7.

## Requisitos

- Graphviz instalado (`sudo apt install graphviz`).
- El formato de fecha usa `localtime_r`, por lo que se compila en Linux.

## Compilar y ejecutar

```bash
make run
```

Las imágenes se generan en la ruta indicada en `-path` del comando `rep`. Cambia las rutas del `main.cpp` por unas válidas en tu equipo.
