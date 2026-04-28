#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include <stdint.h>
#include "cmd.h"
#include "string.h"

// Task configs
#define TASK_BUFF_SIZE 4096 // Task buffer size
#define TASK_PRIORITY 5 // Task priority

void vTaskCode(void *pvParameters)
{
    spi_pins_t pins_p;

    // Initial delay to start serial monitor
    vTaskDelay(pdMS_TO_TICKS(2000));

    // Disables Chip Select
    // gpio_set_level((gpio_num_t)pins_p.cs, 1);
    
    for(;;)
    {
        char cmd_buff[64];
        char cmd[16];
        uint8_t addr_cmd;
        uint32_t f_size;

        if((fgets(cmd_buff, sizeof(cmd_buff), stdin)) != NULL)
        {
            // Removes "\n" from cmd_buff
            cmd_buff[strcspn(cmd_buff, "\n")] = "\0";
            
            int cmds_found = sscanf(cmd_buff, "%16s %i %i", cmd, &addr_cmd, &f_size);

            if(cmds_found < 3)
            {
                printf("ERROR: Memory size not specified!\n");
            }

            if(strcmp(cmd, "dumpf"))
            {
                // Dump all flash data
                spi_dumpf_cmd(f_size, addr_cmd);   
            }
        }
    }
}

void app_main(void)
{
    spi_pins_t pins_p;
    
    gpio_config_t di_io_conf = {
    .pin_bit_mask = (1ULL << pins_p.mosi) | (1ULL << pins_p.clk) | (1ULL << pins_p.cs),
    .mode = GPIO_MODE_OUTPUT,
    .pull_down_en = GPIO_PULLDOWN_DISABLE,
    .pull_up_en = GPIO_PULLDOWN_ENABLE,
    .intr_type = GPIO_INTR_DISABLE
    };

    gpio_config_t do_io_conf = {
        .pin_bit_mask = (1ULL << pins_p.miso),
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
