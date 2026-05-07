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
#include "cli.h"
#include "esp_task_wdt.h"

// CLI task stack size
#define TASK_BUFF_SIZE 8192

// CLI task priority
#define TASK_PRIORITY 1

// Command buffer max size
#define CMD_BUF_SIZE 64

// CLI task
void vTaskCode(void *pvParameters)
{
    esp_err_t err;

    // Small delay before starting task
    vTaskDelay(pdMS_TO_TICKS(500));
    
    err = esp_task_wdt_delete(NULL);
    if(err != ESP_OK)
    {
        printf("Watchdog is disabled for this task. Initializing CLI...\n");
    }

    // Buffer used to store terminal input
    char cmd_buff[CMD_BUF_SIZE];

    // Current buffer index
    int idx = 0;

    for(;;)
    {
        cli_init(&idx, cmd_buff);

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

    gpio_config_t boot_conf = {
        .pin_bit_mask = (1ULL << 0),
        .mode = GPIO_MODE_INPUT,
        .pull_down_en = GPIO_PULLDOWN_ENABLE,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .intr_type = GPIO_INTR_POSEDGE
    };

    // Apply GPIO configs
    gpio_config(&di_io_conf);
    gpio_config(&do_io_conf);
    gpio_config(&boot_conf);

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