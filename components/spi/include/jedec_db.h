#ifndef JEDEC_DB_H
#define JEDEC_DB_H

#include <stdint.h>

typedef struct
{
    uint8_t manuf_id;
    uint8_t dev_type;
    uint8_t dev_cap;
    
    uint32_t capacity;

    const char *manuf_name;
    const char *model_name;
} flash_chip_t;

const flash_chip_t *jedec_query_db(uint8_t manuf_id, uint8_t dev_type, uint8_t dev_cap);

#endif