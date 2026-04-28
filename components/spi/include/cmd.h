#ifndef CMD_H
#define CMD_H

#include <stdint.h>

typedef struct {
    uint8_t miso;
    uint8_t mosi;
    uint8_t clk;
    uint8_t cs;
} spi_pins_t;


uint8_t spi_rcv_data(uint8_t data);

void spi_send_data(uint8_t data);

void manufacturer_info(uint8_t addr);

#endif