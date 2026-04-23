# GStreamer Zstd Decoder Plugin

Plugin experimental para GStreamer diseñado para descomprimir flujos de datos en formato Zstd.

## Estado del Proyecto
El plugin está correctamente registrado y compilado. La lógica central de descompresión está implementada utilizando `ZSTD_decompressDCtx`, aunque actualmente presenta un conflicto en la negociación de buffers (`GstBaseTransform`) que causa errores de `mini_object_unref` durante el procesamiento del pipeline.

## Pasos para Compilar
1. Asegurarse de tener instaladas las dependencias: `gstreamer1.0-dev` y `libzstd-dev`.
2. Compilar con Ninja:
   ```bash
   ninja -C build

 ## Diagnóstico Realizado
Para validar el entorno y el plugin, se han seguido los siguientes pasos de depuración:
- **Verificación de registro:** Confirmado con `GST_DEBUG=GST_PLUGIN_LOADING:4 gst-inspect-1.0 zstddec` que el archivo `.so` se carga correctamente desde la carpeta local.
- **Validación del Pipeline:** Se probó la integridad del entorno y del archivo de prueba mediante un pipeline con `identity`:
GST_PLUGIN_PATH=$PWD/build/src gst-launch-1.0 filesrc location=test.txt.zst ! identity ! filesink location=test_output.txt

## Nota 
El plugin está funcionalmente registrado y la lógica de descompresión está implementada. He identificado que el fallo actual reside en la gestión de memoria de GstBaseTransform durante la negociación de buffers (gst_mini_object_unref), lo cual es un problema recurrente al intentar portar una lógica de descompresión a esta clase base. He validado el entorno y el pipeline con identity para confirmar que la arquitectura de GStreamer en mi entorno es correcta.
