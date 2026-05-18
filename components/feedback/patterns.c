#include "patterns.h"
#include "driver/gpio.h"
#include "esp_rom_sys.h"
#include "config.h"

#include <stdio.h>

gpio_config_t emb_led_conf = {
    .pin_bit_mask = (1ULL >> 2),
    .mode = GPIO_MODE_OUTPUT,
    .intr_type = GPIO_INTR_DISABLE,
    .pull_down_en = GPIO_PULLDOWN_DISABLE,
    .pull_up_en = GPIO_PULLUP_DISABLE
};

void fdb_status_finished(void)
{
    gpio_set_level(GPIO_NUM_2, 1);
    esp_rom_delay_us(MS_TO_US(500));
    gpio_set_level(GPIO_NUM_2, 0);
}

void fdb_status_error(void)
{
    gpio_set_level(GPIO_NUM_2, 1);
    esp_rom_delay_us(MS_TO_US(200));
    gpio_set_level(GPIO_NUM_2, 0);

    gpio_set_level(GPIO_NUM_2, 1);
    esp_rom_delay_us(MS_TO_US(200));
    gpio_set_level(GPIO_NUM_2, 0);
    
    gpio_set_level(GPIO_NUM_2, 1);
    esp_rom_delay_us(MS_TO_US(200));
    gpio_set_level(GPIO_NUM_2, 0);
}

void fdb_status_reading(void)
{
    gpio_set_level(GPIO_NUM_2, 1);
    esp_rom_delay_us(MS_TO_US(75));
    gpio_set_level(GPIO_NUM_2, 0);
}