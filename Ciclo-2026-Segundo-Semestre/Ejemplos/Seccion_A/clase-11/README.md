# Clase 11: API en Flask desplegada con Docker en AWS EC2

Ejemplo independiente de las clases anteriores (no usa el código en C++). Es una API mínima en **Python/Flask** empaquetada en un contenedor **Docker**, pensada para desplegarse en una instancia **EC2** de AWS.

## Estructura

```
clase-11/
├── app.py             # API con Flask
├── requirements.txt   # Dependencias: flask y gunicorn
├── Dockerfile         # Imagen del contenedor
└── .dockerignore      # Archivos excluidos de la imagen
```

## La API (`app.py`)

| Método | Ruta | Respuesta |
|---|---|---|
| GET | `/` | `{"message": "Hola desde Docker en EC2 🐳"}` |
| GET | `/health` | `{"status": "ok"}` (útil para comprobar que el servicio está vivo) |

Escucha en el puerto **8000**. El bloque `app.run(...)` es solo para desarrollo local; dentro del contenedor se usa **gunicorn**.

## El Dockerfile

1. Parte de `python:3.12-slim`.
2. Copia primero `requirements.txt` e instala dependencias (así Docker reutiliza la caché si el código cambia pero las dependencias no).
3. Copia `app.py`.
4. Crea y usa un usuario sin privilegios (`appuser`) por seguridad.
5. Expone el puerto 8000 y arranca con `gunicorn --bind 0.0.0.0:8000 app:app`.

## Probar localmente

```bash
docker build -t api-clase11 .
docker run -d -p 8000:8000 --name api-clase11 api-clase11
curl http://localhost:8000/
curl http://localhost:8000/health
```

## Desplegar en EC2

1. Crear una instancia EC2 (por ejemplo Ubuntu) y, en su **Security Group**, abrir el puerto **8000** (y el 22 para SSH).
2. Conectarse por SSH e instalar Docker:
   ```bash
   sudo apt update
   sudo apt install docker.io -y
   sudo systemctl enable --now docker
   ```
3. Llevar los archivos a la instancia (con `git clone` o `scp`), construir y ejecutar:
   ```bash
   sudo docker build -t api-clase11 .
   sudo docker run -d -p 8000:8000 --restart unless-stopped --name api-clase11 api-clase11
   ```
4. Probar desde el navegador: `http://<IP-PÚBLICA-EC2>:8000/`.

## Comandos útiles

```bash
docker ps                    # contenedores en ejecución
docker logs api-clase11      # ver logs
docker stop api-clase11      # detener
docker rm api-clase11        # eliminar el contenedor
```
