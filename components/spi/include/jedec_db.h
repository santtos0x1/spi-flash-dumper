#ifndef JEDEC_DB_H
#define JEDEC_DB_H

#include <stdint.h>

typedef enum {
    MANUF_WINBOND = 0,
    MANUF_EON_SS_INC = 1,
    MANUF_GIGADEVICE = 2,
    MANUF_MACRONIX = 3,
    MANUF_SST = 4,
    MANUF_MICRON = 5,
    MANUF_PUYA = 6
} flash_manuf_t;

typedef enum {
    MODEL_W25Q128JV = 0,
    MODEL_EN25F80 = 1,
    MODEL_GD25Q32C = 2,
    MODEL_GD25Q64C = 3,
    MODEL_MX25L6406E = 4,
    MODEL_MX25L12835F = 5,
    MODEL_EN25Q64 = 6,
    MODEL_EN25Q32B = 7,
    MODEL_SST25VF016B = 8,
    MODEL_M25P80 = 9,
    MODEL_P25Q32H = 10
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

#endif