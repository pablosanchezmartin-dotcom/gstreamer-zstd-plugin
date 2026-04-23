#include "gstzstddec.h"
#include <zstd.h>
#include <string.h>

#define PACKAGE "gst-zstddec"

G_DEFINE_TYPE (GstZstdDec, gstzstddec, GST_TYPE_BASE_TRANSFORM);

static GstStaticPadTemplate sink_template = GST_STATIC_PAD_TEMPLATE ("sink",
    GST_PAD_SINK, GST_PAD_ALWAYS, GST_STATIC_CAPS ("application/x-zstd"));

static GstStaticPadTemplate src_template = GST_STATIC_PAD_TEMPLATE ("src",
    GST_PAD_SRC, GST_PAD_ALWAYS, GST_STATIC_CAPS ("ANY"));

static void gstzstddec_init (GstZstdDec * self) {}


static gboolean gstzstddec_transform_size (GstBaseTransform * trans,
    GstPadDirection direction, GstCaps * caps, gsize size, GstCaps * othercaps,
    gsize * othersize)
{
  if (direction == GST_PAD_SINK) {
    *othersize = size * 10; 
  } else {
    
    *othersize = size;
  }
  return TRUE;
}

/* * NOTA DE DEPURACIÓN: 
 * La lógica de descompresión es funcional (ZSTD_decompressDCtx). 
 * Actualmente se observa un error 'gst_mini_object_unref'
 * debido a la gestión interna de buffers de GstBaseTransform.
 */

static GstFlowReturn gstzstddec_transform (GstBaseTransform * trans, GstBuffer * inbuf, GstBuffer * outbuf) {
  if (!inbuf || !outbuf) return GST_FLOW_ERROR; 
  GstMapInfo in_map, out_map;
  ZSTD_DCtx *dctx;
  size_t ret;

  if (!gst_buffer_map (inbuf, &in_map, GST_MAP_READ)) return GST_FLOW_ERROR;
  if (!gst_buffer_map (outbuf, &out_map, GST_MAP_WRITE)) {
    gst_buffer_unmap (inbuf, &in_map);
    return GST_FLOW_ERROR;
  }

  dctx = ZSTD_createDCtx();
  ret = ZSTD_decompressDCtx(dctx, out_map.data, out_map.size, in_map.data, in_map.size);
  ZSTD_freeDCtx(dctx);

  gst_buffer_unmap (inbuf, &in_map);
  gst_buffer_unmap (outbuf, &out_map);

  if (ZSTD_isError(ret)) {
    return GST_FLOW_ERROR;
  }

  return GST_FLOW_OK;
}

static void gstzstddec_class_init (GstZstdDecClass * klass) {
  GstElementClass *element_class = GST_ELEMENT_CLASS (klass);
  GstBaseTransformClass *trans_class = GST_BASE_TRANSFORM_CLASS (klass);

  gst_element_class_set_static_metadata (element_class,
      "Zstd Decoder", "Codec/Decoder", "Decompress Zstd streams", "Fluendo Candidate");
  
  gst_element_class_add_pad_template (element_class, gst_static_pad_template_get (&sink_template));
  gst_element_class_add_pad_template (element_class, gst_static_pad_template_get (&src_template));

  trans_class->transform = gstzstddec_transform;
  trans_class->transform_size = gstzstddec_transform_size;
}

static gboolean plugin_init (GstPlugin * plugin) {
  return gst_element_register (plugin, "zstddec", GST_RANK_NONE, GST_TYPE_ZSTDDEC);
}

GST_PLUGIN_DEFINE (GST_VERSION_MAJOR, GST_VERSION_MINOR, zstddec, "Zstd Decoder",
    plugin_init, "1.0", "LGPL", "GStreamer", "GStreamer")