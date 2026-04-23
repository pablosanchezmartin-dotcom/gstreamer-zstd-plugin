#ifndef __GST_ZSTDDEC_H__
#define __GST_ZSTDDEC_H__

#include <gst/gst.h>
#include <gst/base/gstbasetransform.h>

G_BEGIN_DECLS

#define GST_TYPE_ZSTDDEC (gstzstddec_get_type())
G_DECLARE_FINAL_TYPE (GstZstdDec, gstzstddec, GST, ZSTDDEC, GstBaseTransform)

struct _GstZstdDec {
  GstBaseTransform parent;
};

G_END_DECLS

#endif