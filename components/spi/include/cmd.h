#pragma once

#include <stdint.h>
#include <stdbool.h>

void spi_send_data(uint8_t data);
uint8_t spi_recv_data(void);
void spi_cs_toggle(uint8_t cs_level);

void spi_dump_data(uint32_t ic_capacity, uint16_t chunk_size, uint8_t  fast_read);
void spi_read_addr(uint32_t addr, uint16_t len, uint8_t fast_read);
uint32_t spi_get_jedec(void);