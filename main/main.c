#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include <stdint.h>
#include "cmd.h"
#include "string.h"
#include "esp_rom_sys.h"
#include "peri.h"

// Task configs
#define TASK_BUFF_SIZE 8192 // Task buffer size
#define TASK_PRIORITY 1 // Task priority

#define CMD_BUF_SIZE 64

void vTaskCode(void *pvParameters)
{
    vTaskDelay(pdMS_TO_TICKS(1000));

    char cmd_buff[CMD_BUF_SIZE];
    int idx = 0;

    printf("> ");
    fflush(stdout);

    for(;;)
    {        
        char cmd[16];
        uint8_t addr_cmd = 0;
        uint32_t data = 0;
        
        int c = getchar();

        if(c == EOF)
        {
            vTaskDelay(pdMS_TO_TICKS(10));
            continue;
        }
        
        if((c == '\n' || c == '\r'))
        {
             // Removes "\n" from cmd_buff
            cmd_buff[idx] = '\0';
            
            int cmds_found = sscanf(
                cmd_buff, 
                "%15s %hhu %lu", 
                cmd, 
                &addr_cmd, 
                &data
            );

            if(cmds_found < 2)
            {
                printf("ERROR: invalid command length.\n");
            }
            else
            {
                if(strcmp(cmd, "dumpf") == 0)
                {
                    // Dump all flash data
                    // Example: "dumpf READ_FLASH_ADDRESS"
                    spi_dumpf_cmd(data, addr_cmd);
                }

                if(strcmp(cmd, "read") == 0)
                {
                    // Example: "read READ_FLASH_ADDRESS addr"
                    spi_read_addr(data, 3, addr_cmd);
                }

                if(strcmp(cmd, "getman") == 0)
                {
                    // Example: "getman JEDEC_ADDR"
                    spi_get_manuf(addr_cmd);
                }

                printf("> ");
                fflush(stdout);

                idx = 0;
                memset(cmd_buff, 0, sizeof(cmd_buff));

                continue;
            }
        }

        if(((c == 127 || c == '\b') && idx > 0))
        {
            idx--;
        
            printf("\b \b");
            fflush(stdout);
        
            continue;
        }

        if (idx < CMD_BUF_SIZE - 1)
        {
            cmd_buff[idx++] = (char)c;

            // Echo character
            putchar(c);
            fflush(stdout);
        }

        if (idx >= CMD_BUF_SIZE - 1)
        {
            printf("\nBuffer full!\n");
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void app_main(void)
{
    gpio_config_t di_io_conf = {
        .pin_bit_mask = (1ULL << spi_p.mosi) | (1ULL << spi_p.clk) | (1ULL << spi_p.cs),
        .mode = GPIO_MODE_OUTPUT,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .pull_up_en = GPIO_PULLDOWN_ENABLE,
        .intr_type = GPIO_INTR_DISABLE
    };

    gpio_config_t do_io_conf = {
        .pin_bit_mask = (1ULL << spi_p.miso),
        .mode = GPIO_MODE_INPUT,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .intr_type = GPIO_INTR_DISABLE
    };

    gpio_config(&di_io_conf);
    gpio_config(&do_io_conf);

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
