set(srcs "main.c" "lcdfunc.c" "init_spiffs.c"
    )

idf_component_register(SRCS ${srcs} INCLUDE_DIRS ".")
