#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include <stdint.h>
#include "cmd.h"

// Bin chunk size
#define CHUNK_SIZE 16

// Task configs
#define TASK_BUFF_SIZE 4096 // Task buffer size
#define TASK_PRIORITY 5 // Task priority

void vTaskCode(void *pvParameters)
{
    spi_pins_t pins_p;

    // Disables Chip Select
    gpio_set_level((gpio_num_t)pins_p.cs, 1);
    
    // Initial delay to start serial monitor
    vTaskDelay(pdMS_TO_TICKS(2000));

    // Flash size: 8 Mbit
    uint32_t flash_size = 1024 * 1024;
    uint8_t chunk[CHUNK_SIZE];

    

    // Shows manufacturer information
    manufacturer_info(0x9F);
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

    xTaskCreate(vTaskCode, "DUMP_TASK", TASK_BUFF_SIZE, NULL, TASK_PRIORITY, NULL);
}
