idf_component_register(SRCS "lvgl_sw_rotation.c" "lvgl_port_v9.c"
                    INCLUDE_DIRS ".")
idf_component_get_property(lvgl_lib lvgl__lvgl COMPONENT_LIB)
target_compile_options(${lvgl_lib} PRIVATE -Wno-format)