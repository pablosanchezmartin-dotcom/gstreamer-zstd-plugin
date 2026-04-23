# GStreamer Zstd Decoder Plugin

Plugin experimental para GStreamer diseñado para descomprimir flujos de datos en formato Zstd.

## Estado del Proyecto
El plugin está correctamente registrado y compilado. La lógica central de descompresión está implementada utilizando `ZSTD_decompressDCtx`, aunque actualmente presenta un conflicto en la negociación de buffers (`GstBaseTransform`) que causa errores de `mini_object_unref` durante el procesamiento del pipeline.

## Pasos para Compilar
1. Asegurarse de tener instaladas las dependencias: `gstreamer1.0-dev` y `libzstd-dev`.
2. Compilar con Ninja:
   ```bash
   ninja -C build