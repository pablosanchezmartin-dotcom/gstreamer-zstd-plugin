gst_dep = dependency('gstreamer-1.0', version : '>= 1.14')
gstbase_dep = dependency('gstreamer-base-1.0', version : '>= 1.14')
zstd_dep = dependency('libzstd', version : '>= 1.0')

shared_library('gstzstddec',
  'gstzstddec.c',
  dependencies : [gst_dep, gstbase_dep, zstd_dep],
  install : true,
  install_dir : join_paths(get_option('libdir'), 'gstreamer-1.0')
)
