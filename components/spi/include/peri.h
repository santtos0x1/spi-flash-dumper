#ifndef PERI_H
#define PERI_H

#include <stdint.h>

typedef struct {
    uint8_t clk;
    uint8_t mosi;
    uint8_t miso;
    uint8_t cs;
} spi_pins_t;

extern const spi_pins_t spi_p;

#endif