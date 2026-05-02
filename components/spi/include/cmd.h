#ifndef CMD_H
#define CMD_H

#include <stdint.h>

uint8_t spi_send_data(uint8_t data);
void spi_dump_cmd(uint32_t ic_capacity, uint8_t r_cmd);
void spi_read_addr(uint32_t addr, uint8_t len, uint8_t r_cmd);
void spi_get_manuf(uint8_t jedec_addr);

#endif