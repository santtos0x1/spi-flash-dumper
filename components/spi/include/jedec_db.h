#pragma once

#include <stdint.h>

typedef enum {
    MANUF_WINBOND    = 0,
    MANUF_EON_SS_INC = 1,
    MANUF_GIGADEVICE = 2,
    MANUF_MACRONIX   = 3,
    MANUF_SST        = 4,
    MANUF_MICRON     = 5,
    MANUF_PUYA       = 6,
    MANUF_ISSI       = 7,
    MANUF_SPANSION   = 8,
} flash_manuf_t;

typedef enum {
    MODEL_W25Q128JV   = 0,
    MODEL_EN25F80     = 1,
    MODEL_GD25Q32C    = 2,
    MODEL_GD25Q64C    = 3,
    MODEL_MX25L6406E  = 4,
    MODEL_MX25L12835F = 5,
    MODEL_EN25Q64     = 6,
    MODEL_EN25Q32B    = 7,
    MODEL_SST25VF016B = 8,
    MODEL_M25P80      = 9,
    MODEL_P25Q32H     = 10,

    // Winbond
    MODEL_W25Q80      = 11,
    MODEL_W25Q16JV    = 12,
    MODEL_W25Q32JV    = 13,
    MODEL_W25Q64JV    = 14,
    MODEL_W25Q256JV   = 15,

    // GigaDevice
    MODEL_GD25Q80C    = 16,
    MODEL_GD25Q16C    = 17,
    MODEL_GD25Q128C   = 18,

    // Macronix
    MODEL_MX25L8006E  = 19,
    MODEL_MX25L1606E  = 20,
    MODEL_MX25L3206E  = 21,
    MODEL_MX25L25635F = 22,
    
    // Micron
    MODEL_M25P32      = 23,
    MODEL_N25Q064A    = 24,
    MODEL_N25Q128A    = 25,
    
    // ISSI
    MODEL_IS25LP032   = 26,
    MODEL_IS25LP064   = 27,
    MODEL_IS25LP128   = 28,
    MODEL_IS25WP064   = 29,
    MODEL_IS25WP128   = 30,
    
    // Spansion
    MODEL_S25FL064P   = 31,
    MODEL_S25FL128P   = 32,
    MODEL_S25FL256S   = 33,
    
    // Puya
    MODEL_P25Q80H     = 34,
    MODEL_P25Q16H     = 35,
} flash_model_t;
typedef struct
{
    uint8_t manuf_id;
    uint8_t dev_type;
    uint8_t dev_cap;
    
    uint32_t capacity;

    uint8_t manuf_name;
    uint8_t model_name;
} flash_chip_t;

const char *flash_manuf_to_string(flash_manuf_t manuf);
const char *flash_model_to_string(flash_model_t model);
const flash_chip_t *jedec_query_db(uint8_t manuf_id, uint8_t dev_type, uint8_t dev_cap);