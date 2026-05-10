#ifndef CMD_H
#define CMD_H

#include <stdint.h>
#include <stdbool.h>

uint8_t spi_send_data(uint8_t data);

void spi_dump_cmd(uint32_t ic_capacity, uint16_t chunk_size, uint8_t  fast_read);

void spi_read_addr(uint32_t addr, uint16_t len, uint8_t fast_read);

void spi_get_manuf(void);

#endif