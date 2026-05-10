#ifndef CMD_H
#define CMD_H

#include <stdint.h>

uint8_t spi_send_data(uint8_t data);

void spi_dump_cmd(uint32_t ic_capacity, uint16_t chunk_size);

void spi_read_addr(uint32_t addr, uint16_t len);

void spi_get_manuf(void);

#endif