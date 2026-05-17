#include "jedec_db.h"
#include "stdio.h"
const flash_chip_t flash_ics[] = {
    {
        .manuf_id = 0xEF,
        .dev_type = 0x40,
        .dev_cap = 0x18,
        .capacity = 0x1000000,
        .manuf_name = MANUF_WINBOND,
        .model_name = MODEL_W25Q128JV,
    },
    {
        .manuf_id = 0x1C,
        .dev_type = 0x31,
        .dev_cap = 0x14,
        .capacity = 0x100000,
        .manuf_name = MANUF_EON_SS_INC,
        .model_name = MODEL_EN25F80,
    },
    {
        .manuf_id = 0xC8,
        .dev_type = 0x40,
        .dev_cap = 0x16,
        .capacity = 0x400000,
        .manuf_name = MANUF_GIGADEVICE,
        .model_name = MODEL_GD25Q32C,
    },
    {
        .manuf_id = 0xC8,
        .dev_type = 0x40,
        .dev_cap = 0x17,
        .capacity = 0x800000,
        .manuf_name = MANUF_GIGADEVICE,
        .model_name = MODEL_GD25Q64C,
    },
    {
        .manuf_id = 0xC2,
        .dev_type = 0x20,
        .dev_cap = 0x17,
        .capacity = 0x800000,
        .manuf_name = MANUF_MACRONIX,
        .model_name = MODEL_MX25L6406E,
    },
    {
        .manuf_id = 0xC2,
        .dev_type = 0x20,
        .dev_cap = 0x18,
        .capacity = 0x1000000,
        .manuf_name = MANUF_MACRONIX,
        .model_name = MODEL_MX25L12835F,
    },
    {
        .manuf_id = 0x1C,
        .dev_type = 0x30,
        .dev_cap = 0x17,
        .capacity = 0x800000,
        .manuf_name = MANUF_EON_SS_INC,
        .model_name = MODEL_EN25Q64,
    },
    {
        .manuf_id = 0x1C,
        .dev_type = 0x30,
        .dev_cap = 0x16,
        .capacity = 0x400000,
        .manuf_name = MANUF_EON_SS_INC,
        .model_name = MODEL_EN25Q32B,
    },
    {
        .manuf_id = 0xBF,
        .dev_type = 0x25,
        .dev_cap = 0x41,
        .capacity = 0x200000,
        .manuf_name = MANUF_SST,
        .model_name = MODEL_SST25VF016B,
    },
    {
        .manuf_id = 0x20,
        .dev_type = 0x20,
        .dev_cap = 0x14,
        .capacity = 0x100000,
        .manuf_name = MANUF_MICRON,
        .model_name = MODEL_M25P80,
    },
    {
        .manuf_id = 0x85,
        .dev_type = 0x60,
        .dev_cap = 0x16,
        .capacity = 0x400000,
        .manuf_name = MANUF_PUYA,
        .model_name = MODEL_P25Q32H,
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
const char *flash_manuf_to_string(flash_manuf_t manuf)
{
    switch(manuf)
    {
        case MANUF_WINBOND:     return  "Winbond";   
        case MANUF_EON_SS_INC:  return  "Eon";       
        case MANUF_GIGADEVICE:  return  "GigaDevice";
        case MANUF_MACRONIX:    return  "Macronix";  
        case MANUF_SST:         return  "SST";       
        case MANUF_MICRON:      return  "Micron";
        case MANUF_PUYA:        return  "Puya";

        default: return "Not found";
    }
}

const char *flash_model_to_string(flash_model_t model)
{
    switch(model)
    {
        case MODEL_W25Q128JV:   return "W25Q128JV";
        case MODEL_EN25F80:     return "EN25F80";
        case MODEL_GD25Q32C:    return "GD25Q32C";
        case MODEL_GD25Q64C:    return "GD25Q64C";
        case MODEL_MX25L6406E:  return "MX25L6406E";
        case MODEL_MX25L12835F: return "MX25L12835F";
        case MODEL_EN25Q64:     return "EN25Q64";
        case MODEL_EN25Q32B:    return "EN25Q32B";
        case MODEL_SST25VF016B: return "SST25VF016B";
        case MODEL_M25P80:      return "M25P80";
        case MODEL_P25Q32H:     return "P25Q32H";
 
        default: return "Not found";
    }
}