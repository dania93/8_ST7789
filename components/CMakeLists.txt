set(srcs "st7789.c" "fontx.c" "decode_jpeg_v5.c" "decode_png.c" "pngle.c")

idf_component_register(SRCS "${srcs}"
                       PRIV_REQUIRES driver
                       INCLUDE_DIRS ".")
