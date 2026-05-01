#include "cmd.h"
#include <stdint.h>
#include "driver/gpio.h"
#include "esp_rom_sys.h"
#include "peri.h"

uint8_t spi_send_data(uint8_t data)
{
    uint8_t received_data = 0;

    for(int i = 7; i >= 0; i--)
    {
        // Data is shifted, and send to flash
        gpio_set_level((gpio_num_t) spi_p.mosi, (data >> i) & 0x01);
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

void spi_get_manuf(uint8_t jedec_addr)
{
    gpio_set_level((gpio_num_t)spi_p.cs, 0);
    
    // ID command
    spi_send_data(jedec_addr);

    uint8_t m_id = spi_send_data(0x00);
    uint8_t type = spi_send_data(0x00);
    uint8_t cap = spi_send_data(0x00);
    
    gpio_set_level((gpio_num_t)spi_p.cs, 1);

    printf("Manufacturer ID: %02X, Type: %02X, Capacity: %02X\n", m_id, type, cap);
}

void spi_read_addr(uint32_t addr, uint8_t len, uint8_t r_cmd)
{
    uint8_t ret_data;
    
    // Enables CS
    gpio_set_level((gpio_num_t)spi_p.cs, 0);
    esp_rom_delay_us(1);

    // Read command
    spi_send_data(r_cmd);
    esp_rom_delay_us(1);

    // Send first byte address
    spi_send_data((addr >> 16) & 0xFF);
    esp_rom_delay_us(1);

    // Send second byte address
    spi_send_data((addr >> 8) & 0xFF);
    esp_rom_delay_us(1);
    
    // Send third address
    spi_send_data(addr & 0xFF);
    esp_rom_delay_us(1);

    for(int i = 0; i < len; i++)
    {
        ret_data = spi_send_data(0x00);
        printf("0x%d\n", ret_data);
    }

    esp_rom_delay_us(1);

    // Disables CS
    gpio_set_level((gpio_num_t)spi_p.cs, 1);
}

void spi_dumpf_cmd(uint32_t ic_capacity, uint8_t r_cmd)
{   
    uint8_t chunk_size = 16;

    for(uint32_t addr = 0; addr < ic_capacity; addr += chunk_size)
    {
        printf("%06X: ", (unsigned int)addr);
        for(int i = 0; i < chunk_size; i++)
        {
            spi_read_addr(addr, chunk_size, r_cmd);
        }
        printf("\n");

        // Delay
        if (addr % 1024 == 0) {
            esp_rom_delay_us(5000);
        }
    }
}
