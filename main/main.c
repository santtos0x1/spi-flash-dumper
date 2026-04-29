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
#define TASK_BUFF_SIZE 4096 // Task buffer size
#define TASK_PRIORITY 5 // Task priority

void vTaskCode(void *pvParameters)
{
    // Initial delay to start serial monitor
    vTaskDelay(pdMS_TO_TICKS(2000));

    // Disables Chip Select
    // gpio_set_level((gpio_num_t)pins.cs, 1);
    
    for(;;)
    {
        char cmd_buff[64];
        char cmd[16];
        uint8_t addr_cmd;
        uint32_t data;

        if((fgets(cmd_buff, sizeof(cmd_buff), stdin)) != NULL)
        {
            // Removes "\n" from cmd_buff
            cmd_buff[strcspn(cmd_buff, "\n")] = '\0';
            
            int cmds_found = sscanf(cmd_buff, "%16s %hhi %li", cmd, &addr_cmd, &data);

            if(cmds_found < 3)
            {
                printf("ERROR: Memory size not specified!\n");
            }

            if(strcmp(cmd, "dumpf"))
            {
                // Dump all flash data
                // Example: "spi dumpf READ_FLASH_ADDRESS"
                spi_dumpf_cmd(data, addr_cmd);
            }

            if(strcmp(cmd, "read"))
            {
                // Example: "spi read READ_FLASH_ADDRESS"
                spi_read_addr(data, 3, addr_cmd);
            }
        }
    }
}

void app_main(void)
{
    gpio_config_t di_io_conf = {
    .pin_bit_mask = (1ULL << pins.mosi) | (1ULL << pins.clk) | (1ULL << pins.cs),
    .mode = GPIO_MODE_OUTPUT,
    .pull_down_en = GPIO_PULLDOWN_DISABLE,
    .pull_up_en = GPIO_PULLDOWN_ENABLE,
    .intr_type = GPIO_INTR_DISABLE
    };

    gpio_config_t do_io_conf = {
        .pin_bit_mask = (1ULL << pins.miso),
        .mode = GPIO_MODE_INPUT,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .intr_type = GPIO_INTR_DISABLE
    };

    gpio_config(&di_io_conf);
    gpio_config(&do_io_conf);

    xTaskCreate(
        vTaskCode, 
        "DUMP_TASK", 
        TASK_BUFF_SIZE, 
        NULL, 
        TASK_PRIORITY, 
        NULL
    );
}
