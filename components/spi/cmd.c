#include "cmd.h"
#include <stdint.h>
#include "driver/gpio.h"
#include "esp_rom_sys.h"
#include "peri.h"
#include "config.h"
#include <stdbool.h>

#define BOOT_GPIO0 0

#define DEFAULT_CHUNK_SIZE 256

// Send and receive one SPI byte using bit-banging
uint8_t spi_send_data(uint8_t data)
{
    // Stores received byte
    uint8_t received_data = 0;

    // Sends 8 bits, MSB first
    for(int i = 7; i >= 0; i--)
    {
        // Set MOSI according current bit
        gpio_set_level(
            (gpio_num_t) spi_p.mosi,
            (data >> i) & 0x01
        );

        esp_rom_delay_us(5);

        // Clock HIGH
        gpio_set_level((gpio_num_t)spi_p.clk, 1);
        esp_rom_delay_us(5);

        // Read MISO bit
        if(gpio_get_level((gpio_num_t)spi_p.miso))
        {
            // Stores received bit
            received_data |= (1 << i);
        }

        // Clock LOW
        gpio_set_level((gpio_num_t)spi_p.clk, 0);
        esp_rom_delay_us(5);
    }

    // Return received SPI byte
    return received_data;
}

// Read JEDEC manufacturer information
void spi_get_manuf(void)
{
    uint8_t man_id_b, type_b, cap_b;
    
    // Enable chip select
    gpio_set_level((gpio_num_t)spi_p.cs, 0);
    esp_rom_delay_us(1);

    // Send JEDEC command
    spi_send_data(FLASH_JEDEC_BYTE);
    esp_rom_delay_us(1);

    // Read JEDEC bytes
    man_id_b = spi_send_data(0x00);
    esp_rom_delay_us(1);

    type_b = spi_send_data(0x00);
    esp_rom_delay_us(1);
    
    cap_b = spi_send_data(0x00);
    esp_rom_delay_us(1);

    // Disable chip select
    gpio_set_level((gpio_num_t)spi_p.cs, 1);

    // Print chip information
    printf(
        "Manufacturer ID: %02X, Type: %02X, Capacity: %02X\n",
        man_id_b,
        type_b,
        cap_b
    );
}

// Read flash memory address
void spi_read_addr(uint32_t addr, uint16_t len, uint8_t fast_read)
{
    if(len == 0)
    {
        len = DEFAULT_CHUNK_SIZE;
    }

    uint16_t ret_data[len];

    // Enable chip select
    gpio_set_level((gpio_num_t)spi_p.cs, 0);
    esp_rom_delay_us(1);


    if(fast_read)
    {
        // Send fast read byte command
        spi_send_data(FLASH_FREAD_BYTE);
        esp_rom_delay_us(1);
    }
    else
    {
        // Send read byte command
        spi_send_data(FLASH_READ_BYTE);
        esp_rom_delay_us(1);
    }

    // Send first address byte
    spi_send_data((addr >> 16) & 0xFF);
    esp_rom_delay_us(1);

    // Send second address byte
    spi_send_data((addr >> 8) & 0xFF);
    esp_rom_delay_us(1);

    // Send third address byte
    spi_send_data(addr & 0xFF);
    esp_rom_delay_us(1);

    if(fast_read)
    {
        // Dummy byte for fast read
        spi_send_data(0x00);
        esp_rom_delay_us(1);
    }

    // Read flash data
    for(int i = 0; i < len; i++)
    {
        // Send dummy byte and receive data
        ret_data[i] = spi_send_data(0x00);
        esp_rom_delay_us(1);
    }

    printf("0x%06X: ", (unsigned int)addr);

    for(int i = 0; i < len; i++)
    {
        // Print received bytes
        printf("%02X ", ret_data[i]);
    }

    esp_rom_delay_us(1);

    printf("\n");

    // Disable chip select
    gpio_set_level((gpio_num_t)spi_p.cs, 1);
}

// Dump full flash content
void spi_dump_cmd(uint32_t ic_capacity, uint16_t chunk_size, uint8_t  fast_read)
{
    // Loop through entire flash
    for(uint32_t addr = 0; addr < ic_capacity; addr += chunk_size)
    {
        if (gpio_get_level(BOOT_GPIO0) == 0)
        {
            printf("Flash dump stopped mannualy!\n");
            break;
        }

        // Read chunk data
        spi_read_addr(addr, chunk_size, fast_read);
        esp_rom_delay_us(MS_TO_US(50));

        // Small delay every 4KB
        // Helps avoid watchdog trigger
        if (addr % 4096 == 0)
        {
            esp_rom_delay_us(MS_TO_US(200));
        }
    }
}