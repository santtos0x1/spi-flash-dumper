/*
    * Instead of relying on the ESP32 hardware SPI peripheral, the project implements a software-driven 
    * SPI interface (**bit-banging**), giving full control over GPIO timing and communication behavior. 
    * This approach makes the tool flexible for interacting with a wide range of external SPI flash chips 
    * and low-level hardware targets.
    * 
    * The tool provides a serial command-line interface through `idf.py monitor`, allowing direct 
    * interaction with flash devices using simple commands for reading memory, dumping firmware contents,
    * and retrieving JEDEC manufacturer information.
    * © santtos0x1 2026
*/

#include "cmd.h"
#include "peri.h"
#include "config.h"
#include "cli.h"

#include <stdio.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "string.h"
#include "esp_rom_sys.h"
#include "esp_task_wdt.h"

// CLI task stack size
#define TASK_BUFF_SIZE 4096

// CLI task priority
#define TASK_PRIORITY 3

// Command buffer max size
#define CMD_BUFF_SIZE 64

// CLI task
void vTaskCode(void *pvParameters)
{
    esp_err_t err;

    // Small delay before starting task
    vTaskDelay(pdMS_TO_TICKS(500));
    
    err = esp_task_wdt_delete(NULL);
    if(err != ESP_OK)
    {
        printf("Watchdog is disabled for this task...\n");
    }

    // Buffer used to store terminal input
    char cmd_buff[CMD_BUFF_SIZE];

    // Current buffer index
    uint8_t idx = 0;

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

    // Configure BOOT button
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