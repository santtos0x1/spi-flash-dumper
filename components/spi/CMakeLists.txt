idf_component_register(SRCS "peri.c" "cmd.c"
                    INCLUDE_DIRS "include"
                    REQUIRES esp_driver_gpio)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)                    