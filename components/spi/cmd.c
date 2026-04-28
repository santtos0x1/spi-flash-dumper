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

void manufacturer_info(uint8_t addr)
{
    spi_pins_t spi_p;

    gpio_set_level((gpio_num_t)spi_p.cs, 0);
    
    // ID command
    spi_send_data(addr);

    uint8_t m_id = SPI_transfer(0x00);
    uint8_t type = SPI_transfer(0x00);
    uint8_t cap = SPI_transfer(0x00);
    
    gpio_set_level((gpio_num_t)spi_p.cs, 1);

    printf("Manufacturer ID: %02X, Type: %02X, Capacity: %02X\n", m_id, type, cap);
}

void spi_read_addr(uint32_t addr, uint8_t *buff, uint8_t len, uint8_t r_cmd)
{
    spi_pins_t pins_p;

    // Enables CS
    gpio_set_level((gpio_num_t)pins_p.cs, 0);
    esp_rom_delay_us(1);

    // Read command
    SPI_transfer(r_cmd);
    esp_rom_delay_us(1);

    // Send first byte address
    SPI_transfer((addr >> 16) & 0xFF);
    esp_rom_delay_us(1);

    // Send second byte address
    SPI_transfer((addr >> 8) & 0xFF);
    esp_rom_delay_us(1);
    
    // Send third address
    SPI_transfer(addr & 0xFF);
    esp_rom_delay_us(1);

    for(int i = 0; i < len; i++)
    {
        buff[i] = spi_rcv_data(0x00);
    }

    esp_rom_delay_us(1);

    // Disables CS
    gpio_set_level((gpio_num_t)pins_p.cs, 1);
}

void spi_dumpf_cmd(uint32_t ic_capacity, uint8_t r_cmd)
{   
    uint8_t chunk_size = 16;
    uint8_t chunk[chunk_size];

    for(uint32_t addr = 0; addr < ic_capacity; addr += chunk_size)
    {
        spi_read_addr(addr, chunk, chunk_size, r_cmd);

        printf("%06X: ", (uint32_t)addr);
        for(int i = 0; i < chunk_size; i++)
        {
            printf("%02X ", chunk[i]);
        }
        printf("\n");

        // Delay
        if (addr % 1024 == 0) {
            vTaskDelay(pdMS_TO_TICKS(5));
        }
    }
}
