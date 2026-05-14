#include "jedec_db.h"
#include "stdio.h"

const flash_chip_t flash_ics[] = {
    {
        .manuf_id = 0xEF,
        .dev_type = 0x40,
        .dev_cap = 0x18,
        .capacity = 0x1000000,
        .manuf_name = "Winbond",
        .model_name = "W25Q128JV",
    },
    {
        .manuf_id = 0x1C,
        .dev_type = 0x31,
        .dev_cap = 0x14,
        .capacity = 0x100000,
        .manuf_name = "Eon Silicon Solution Inc.",
        .model_name = "EN25F80",
    },
    {
        .manuf_id = 0xC8,
        .dev_type = 0x40,
        .dev_cap = 0x16,
        .capacity = 0x400000,
        .manuf_name = "GigaDevice",
        .model_name = "GD25Q32C",
    },
    {
        .manuf_id = 0xC8,
        .dev_type = 0x40,
        .dev_cap = 0x17,
        .capacity = 0x800000,
        .manuf_name = "GigaDevice",
        .model_name = "GD25Q64C",
    },
    {
        .manuf_id = 0xC2,
        .dev_type = 0x20,
        .dev_cap = 0x17,
        .capacity = 0x800000,
        .manuf_name = "Macronix",
        .model_name = "MX25L6406E",
    },
    {
        .manuf_id = 0xC2,
        .dev_type = 0x20,
        .dev_cap = 0x18,
        .capacity = 0x1000000,
        .manuf_name = "Macronix",
        .model_name = "MX25L12835F",
    },
    {
        .manuf_id = 0x1C,
        .dev_type = 0x30,
        .dev_cap = 0x17,
        .capacity = 0x800000,
        .manuf_name = "Eon Silicon Solution Inc.",
        .model_name = "EN25Q64",
    },
    {
        .manuf_id = 0x1C,
        .dev_type = 0x30,
        .dev_cap = 0x16,
        .capacity = 0x400000,
        .manuf_name = "Eon Silicon Solution Inc.",
        .model_name = "EN25Q32B",
    },
    {
        .manuf_id = 0xBF,
        .dev_type = 0x25,
        .dev_cap = 0x41,
        .capacity = 0x200000,
        .manuf_name = "SST",
        .model_name = "SST25VF016B",
    },
    {
        .manuf_id = 0x20,
        .dev_type = 0x20,
        .dev_cap = 0x14,
        .capacity = 0x100000,
        .manuf_name = "Micron",
        .model_name = "M25P80",
    },
    {
        .manuf_id = 0x85,
        .dev_type = 0x60,
        .dev_cap = 0x16,
        .capacity = 0x400000,
        .manuf_name = "Puya",
        .model_name = "P25Q32H",
    }
};

const flash_chip_t *jedec_query_db(uint8_t manuf_id, uint8_t dev_type, uint8_t dev_cap)
{
    size_t total_chips = sizeof(flash_ics) / sizeof(flash_ics[0]);

    for(uint8_t i = 0; i < total_chips; i++)
    {
        if((manuf_id == flash_ics[i].manuf_id) && 
        (dev_type == flash_ics[i].dev_type) &&
        (dev_cap == flash_ics[i].dev_cap))
        {
            return &flash_ics[i];
        }
    }

    return NULL;
}