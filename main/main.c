#include <stdio.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "cmd.h"
#include "string.h"
#include "esp_rom_sys.h"
#include "peri.h"
#include "config.h"

// CLI task stack size
#define TASK_BUFF_SIZE 8192

// CLI task priority
#define TASK_PRIORITY 1

// Command buffer max size
#define CMD_BUF_SIZE 64

// CLI task
void vTaskCode(void *pvParameters)
{
    // Small delay before starting task
    vTaskDelay(pdMS_TO_TICKS(1000));

    // Buffer used to store terminal input
    char cmd_buff[CMD_BUF_SIZE];

    // Current buffer index
    int idx = 0;

    // Print terminal prompt
    printf("> ");
    fflush(stdout);

    for(;;)
    {
        // Command name buffer
        char cmd[16];

        // Command arguments
        unsigned int addr_cmd = 0;
        unsigned int data = 0;

        // Read one character from terminal
        int c = getchar();

        // No character received
        if(c == EOF)
        {
            vTaskDelay(pdMS_TO_TICKS(10));
            continue;
        }

        // Execute command when ENTER is pressed
        if((c == '\n' || c == '\r'))
        {
            // End string with NULL terminator
            cmd_buff[idx] = '\0';

            // Parse command and arguments
            int cmds_found = sscanf(
                cmd_buff,
                "%15s %x %x",
                cmd,
                &addr_cmd,
                &data
            );

            // Invalid command
            if(cmds_found < 2)
            {
                printf("ERROR: invalid command length.\n");
            }
            else
            {
                // Dump full flash
                if(strcmp(cmd, "dump") == 0)
                {
                    printf("\nVariables: %x - %x\n", addr_cmd, data);

                    // Example:
                    // dump 0x03 0x200000
                    spi_dump_cmd(data, addr_cmd);
                }

                // Read specific flash address
                if(strcmp(cmd, "read") == 0)
                {
                    printf("\nVariables: %x - %x\n", addr_cmd, data);

                    // Example:
                    // read 0x03 0x000100
                    spi_read_addr(data, DEFAULT_24BIT_SET, addr_cmd);
                }

                // Read JEDEC manufacturer ID
                if(strcmp(cmd, "getman") == 0)
                {
                    printf("\nVariables: %x - %x\n", addr_cmd, data);

                    // Example:
                    // getman 0x9F
                    spi_get_manuf(addr_cmd);
                }

                // Print prompt again
                printf("> ");
                fflush(stdout);

                // Clear command buffer
                idx = 0;
                memset(cmd_buff, 0, sizeof(cmd_buff));

                continue;
            }
        }

        // Handle backspace
        if(((c == 127 || c == '\b') && idx > 0))
        {
            idx--;

            // Remove character from terminal
            printf("\b \b");
            fflush(stdout);

            continue;
        }

        // Store character if buffer is not full
        if (idx < CMD_BUF_SIZE - 1)
        {
            cmd_buff[idx++] = (char)c;

            // Echo typed character
            putchar(c);
            fflush(stdout);
        }

        // Small delay to prevent watchdog trigger
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void app_main(void)
{
    // Configure SPI output pins
    gpio_config_t di_io_conf = {
        .pin_bit_mask = (1ULL << spi_p.mosi) | (1ULL << spi_p.clk) 
        | (1ULL << spi_p.cs),

        .mode = GPIO_MODE_OUTPUT,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .pull_up_en = GPIO_PULLDOWN_ENABLE,
        .intr_type = GPIO_INTR_DISABLE
    };

    // Configure SPI input pin
    gpio_config_t do_io_conf = {
        .pin_bit_mask = (1ULL << spi_p.miso),
        .mode = GPIO_MODE_INPUT,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .intr_type = GPIO_INTR_DISABLE
    };

    // Apply GPIO configs
    gpio_config(&di_io_conf);
    gpio_config(&do_io_conf);

    // Create CLI task on CPU core 1
    xTaskCreatePinnedToCore(
        vTaskCode,
        "cli",
        TASK_BUFF_SIZE,
        NULL,
        TASK_PRIORITY,
        NULL,
        1
    );
}