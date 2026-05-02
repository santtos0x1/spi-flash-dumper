#include "cmd.h"
#include <stdint.h>
#include "driver/gpio.h"
#include "esp_rom_sys.h"
#include "peri.h"

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
void spi_get_manuf(uint8_t jedec_addr)
{
    uint8_t m_id, type, cap;
    
    // Enable chip select
    gpio_set_level((gpio_num_t)spi_p.cs, 0);
    esp_rom_delay_us(1);

    // Send JEDEC command
    spi_send_data(jedec_addr);
    esp_rom_delay_us(1);

    // Read manufacturer bytes
    m_id = spi_send_data(0x00);
    esp_rom_delay_us(1);

    type = spi_send_data(0x00);
    esp_rom_delay_us(1);
    
    cap = spi_send_data(0x00);
    esp_rom_delay_us(1);

    // Disable chip select
    gpio_set_level((gpio_num_t)spi_p.cs, 1);

    // Print chip information
    printf(
        "Manufacturer ID: %02X, Type: %02X, Capacity: %02X\n",
        m_id,
        type,
        cap
    );
}

// Read flash memory address
void spi_read_addr(uint32_t addr, uint8_t len, uint8_t r_cmd)
{
    uint8_t ret_data;

    // Enable chip select
    gpio_set_level((gpio_num_t)spi_p.cs, 0);
    esp_rom_delay_us(1);

    // Send read command
    spi_send_data(r_cmd);
    esp_rom_delay_us(1);

    // Send first address byte
    spi_send_data((addr >> 16) & 0xFF);
    esp_rom_delay_us(1);

    // Send second address byte
    spi_send_data((addr >> 8) & 0xFF);
    esp_rom_delay_us(1);

    // Send third address byte
    spi_send_data(addr & 0xFF);
    esp_rom_delay_us(1);

    // Read flash data
    for(int i = 0; i < len; i++)
    {
        // Send dummy byte and receive data
        ret_data = spi_send_data(0x00);
        esp_rom_delay_us(1);

        // Print received byte
        printf("0x%02X\n", ret_data);
    }

    esp_rom_delay_us(1);

    // Disable chip select
    gpio_set_level((gpio_num_t)spi_p.cs, 1);
}

// Dump full flash content
void spi_dump_cmd(uint32_t ic_capacity, uint8_t r_cmd)
{
    // Bytes read per iteration
    uint8_t chunk_size = 16;

    // Loop through entire flash
    for(uint32_t addr = 0; addr < ic_capacity; addr += chunk_size)
    {
        // Print current address
        printf("%06X: ", (unsigned int)addr);

        // Read chunk data
        spi_read_addr(addr, chunk_size, r_cmd);
        esp_rom_delay_us(MS_TO_US(50));

        printf("\n");
        
        // Small delay every 1KB
        // Helps avoid watchdog trigger
        if (addr % 1024 == 0)
        {
            esp_rom_delay_us(MS_TO_US(100));
        }
    }
}