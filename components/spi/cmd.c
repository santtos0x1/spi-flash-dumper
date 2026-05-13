#include "cmd.h"
#include "peri.h"
#include "config.h"

#include <stdint.h>
#include <stdbool.h>
#include "driver/gpio.h"
#include "esp_rom_sys.h"

#define BOOT_GPIO0 0

#define DEFAULT_CHUNK_SIZE 256

#define ADDR_DELAY_LM 4096

void spi_cs_toggle(uint8_t cs_level)
{
    // Set Chip-Select level to 1 if cs_level == 1
    if(cs_level)
    {
        gpio_set_level((gpio_num_t)spi_p.cs, 1);
    }
    else // Set Chip-Select level to 1 if cs_level == 0
    {
        gpio_set_level((gpio_num_t)spi_p.cs, 0);
    }
}

// Send and receive one SPI byte using bit-banging
void spi_send_data(uint8_t addr)
{
    // Sends 8 bits, MSB first
    for(int i = 7; i >= 0; i--)
    {
        // Set MOSI according current bit
        gpio_set_level(
            (gpio_num_t)spi_p.mosi,
            (addr >> i) & 0x01
        );

        esp_rom_delay_us(5);

        // Clock HIGH
        gpio_set_level((gpio_num_t)spi_p.clk, 1);
        esp_rom_delay_us(5);

        // Clock LOW
        gpio_set_level((gpio_num_t)spi_p.clk, 0);
        esp_rom_delay_us(5);
    }
}

uint8_t spi_recv_data(void)
{
    // Stores received byte
    uint8_t recv_data = 0;

    for(int i = 7; i >= 0; i--)
    {
        // Clock HIGH
        gpio_set_level((gpio_num_t)spi_p.clk, 1);
        esp_rom_delay_us(5);

        // Read MISO bit
        if(gpio_get_level((gpio_num_t)spi_p.miso))
        {
            // Stores received bit
            recv_data |= (1 << i);
        }

        // Clock LOW
        gpio_set_level((gpio_num_t)spi_p.clk, 0);
        esp_rom_delay_us(5);
    }

    return recv_data;
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
    man_id_b = spi_recv_data();
    esp_rom_delay_us(1);

    type_b = spi_recv_data();
    esp_rom_delay_us(1);
    
    cap_b = spi_recv_data();
    esp_rom_delay_us(1);

    // Disable chip select
    gpio_set_level((gpio_num_t)spi_p.cs, 1);

    // Print chip information
    printf(
        "1-byte: %02X, 2-byte: %02X, 3-byte: %02X\n",
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
        ret_data[i] = spi_recv_data();
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
            printf("Dump interrupted!\n");
            break;
        }

        // Read chunk data
        spi_read_addr(addr, chunk_size, fast_read);
        esp_rom_delay_us(MS_TO_US(50));

        // Small delay
        // Helps avoid watchdog trigger
        if (addr % ADDR_DELAY_LM == 0)
        {
            esp_rom_delay_us(MS_TO_US(200));
        }
    }
}