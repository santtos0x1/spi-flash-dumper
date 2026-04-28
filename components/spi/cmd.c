#include "cmd.h"
#include <stdint.h>
#include "driver/gpio.h"

uint8_t spi_rcv_data(uint8_t data)
{
    spi_pins_t spi_p;

    uint8_t received_data = 0;

    for(int i = 7; i >= 0; i--)
    {
        // Data is shifted, and send to flash
        gpio_set_level((gpio_num_t)spi_p.mosi, (data >> i) & 0x01);
        esp_rom_delay_us(5);

        // Clocks sets up
        gpio_set_level((gpio_num_t)spi_p.clk, 1);
        esp_rom_delay_us(5);

        if(gpio_get_level((gpio_num_t)spi_p.miso))
        {
            received_data |= (1 << i);
        }

        gpio_set_level((gpio_num_t)spi_p.clk, 0);
        esp_rom_delay_us(5);
    }

    return received_data;
}

void manufacturer_info(uint8_t manu_addr)
{
    spi_pins_t spi_p;

    gpio_set_level((gpio_num_t)spi_p.cs, 0);
    
    // ID command
    spi_send_data(manu_addr);

    uint8_t m_id = SPI_transfer(0x00);
    uint8_t type = SPI_transfer(0x00);
    uint8_t cap = SPI_transfer(0x00);
    
    gpio_set_level((gpio_num_t)spi_p.cs, 1);

    printf("Manufacturer ID: %02X, Type: %02X, Capacity: %02X\n", m_id, type, cap);
}