#include "peri.h"
#include "cmd.h"

// Default ESP32 SPI pins
const spi_pins_t spi_p = {
    .clk  = 18,
    .mosi = 19,
    .miso = 5,
    .cs   = 22
};