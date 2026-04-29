#ifndef CMD_H
#define CMD_H

#include <stdint.h>

typedef struct {
    uint8_t clk;
    uint8_t mosi;
    uint8_t miso;
    uint8_t cs;
} spi_pins_t;

extern spi_pins_t pins;

uint8_t spi_send_data(uint8_t data);

void spi_dumpf_cmd(uint32_t ic_capacity, uint8_t r_cmd);

void spi_read_addr(uint32_t addr, uint8_t len, uint8_t r_cmd);

void manufacturer_info(uint8_t addr);

#endif