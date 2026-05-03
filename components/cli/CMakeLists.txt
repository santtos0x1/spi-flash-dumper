idf_component_register(SRCS "cli.c"
                    INCLUDE_DIRS "include"
                    REQUIRES esp_driver_gpio spi)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)                    