#include "jedec_db.h"

#include <stdio.h>

const flash_chip_t flash_ics[] = {
    // ---- WINBOND ----
    {
        .manuf_id   = 0xEF,
        .dev_type   = 0x40,
        .dev_cap    = 0x14,
        .capacity   = 0x100000,
        .manuf_name = MANUF_WINBOND,
        .model_name = MODEL_W25Q80,
    },
    {
        .manuf_id   = 0xEF,
        .dev_type   = 0x40,
        .dev_cap    = 0x15,
        .capacity   = 0x200000,
        .manuf_name = MANUF_WINBOND,
        .model_name = MODEL_W25Q16JV,
    },
    {
        .manuf_id   = 0xEF,
        .dev_type   = 0x40,
        .dev_cap    = 0x16,
        .capacity   = 0x400000,
        .manuf_name = MANUF_WINBOND,
        .model_name = MODEL_W25Q32JV,
    },
    {
        .manuf_id   = 0xEF,
        .dev_type   = 0x40,
        .dev_cap    = 0x17,
        .capacity   = 0x800000,
        .manuf_name = MANUF_WINBOND,
        .model_name = MODEL_W25Q64JV,
    },
    {
        .manuf_id   = 0xEF,
        .dev_type   = 0x40,
        .dev_cap    = 0x18,
        .capacity   = 0x1000000,
        .manuf_name = MANUF_WINBOND,
        .model_name = MODEL_W25Q128JV,
    },
    {
        .manuf_id   = 0xEF,
        .dev_type   = 0x40,
        .dev_cap    = 0x19,
        .capacity   = 0x2000000,
        .manuf_name = MANUF_WINBOND,
        .model_name = MODEL_W25Q256JV,
    },

    // ---- GIGADEVICE ----
    {
        .manuf_id   = 0xC8,
        .dev_type   = 0x40,
        .dev_cap    = 0x14,
        .capacity   = 0x100000,
        .manuf_name = MANUF_GIGADEVICE,
        .model_name = MODEL_GD25Q80C,
    },
    {
        .manuf_id   = 0xC8,
        .dev_type   = 0x40,
        .dev_cap    = 0x15,
        .capacity   = 0x200000,
        .manuf_name = MANUF_GIGADEVICE,
        .model_name = MODEL_GD25Q16C,
    },
    {
        .manuf_id   = 0xC8,
        .dev_type   = 0x40,
        .dev_cap    = 0x16,
        .capacity   = 0x400000,
        .manuf_name = MANUF_GIGADEVICE,
        .model_name = MODEL_GD25Q32C,
    },
    {
        .manuf_id   = 0xC8,
        .dev_type   = 0x40,
        .dev_cap    = 0x17,
        .capacity   = 0x800000,
        .manuf_name = MANUF_GIGADEVICE,
        .model_name = MODEL_GD25Q64C,
    },
    {
        .manuf_id   = 0xC8,
        .dev_type   = 0x40,
        .dev_cap    = 0x18,
        .capacity   = 0x1000000,
        .manuf_name = MANUF_GIGADEVICE,
        .model_name = MODEL_GD25Q128C,
    },

    // ---- MACRONIX ----
    {
        .manuf_id   = 0xC2,
        .dev_type   = 0x20,
        .dev_cap    = 0x14,
        .capacity   = 0x100000,
        .manuf_name = MANUF_MACRONIX,
        .model_name = MODEL_MX25L8006E,
    },
    {
        .manuf_id   = 0xC2,
        .dev_type   = 0x20,
        .dev_cap    = 0x15,
        .capacity   = 0x200000,
        .manuf_name = MANUF_MACRONIX,
        .model_name = MODEL_MX25L1606E,
    },
    {
        .manuf_id   = 0xC2,
        .dev_type   = 0x20,
        .dev_cap    = 0x16,
        .capacity   = 0x400000,
        .manuf_name = MANUF_MACRONIX,
        .model_name = MODEL_MX25L3206E,
    },
    {
        .manuf_id   = 0xC2,
        .dev_type   = 0x20,
        .dev_cap    = 0x17,
        .capacity   = 0x800000,
        .manuf_name = MANUF_MACRONIX,
        .model_name = MODEL_MX25L6406E,
    },
    {
        .manuf_id   = 0xC2,
        .dev_type   = 0x20,
        .dev_cap    = 0x18,
        .capacity   = 0x1000000,
        .manuf_name = MANUF_MACRONIX,
        .model_name = MODEL_MX25L12835F,
    },
    {
        .manuf_id   = 0xC2,
        .dev_type   = 0x20,
        .dev_cap    = 0x19,
        .capacity   = 0x2000000,
        .manuf_name = MANUF_MACRONIX,
        .model_name = MODEL_MX25L25635F,
    },

    // ---- EON SS INC ----
    {
        .manuf_id   = 0x1C,
        .dev_type   = 0x31,
        .dev_cap    = 0x14,
        .capacity   = 0x100000,
        .manuf_name = MANUF_EON_SS_INC,
        .model_name = MODEL_EN25F80,
    },
    {
        .manuf_id   = 0x1C,
        .dev_type   = 0x30,
        .dev_cap    = 0x16,
        .capacity   = 0x400000,
        .manuf_name = MANUF_EON_SS_INC,
        .model_name = MODEL_EN25Q32B,
    },
    {
        .manuf_id   = 0x1C,
        .dev_type   = 0x30,
        .dev_cap    = 0x17,
        .capacity   = 0x800000,
        .manuf_name = MANUF_EON_SS_INC,
        .model_name = MODEL_EN25Q64,
    },

    // ---- ISSI ----
    {
        .manuf_id   = 0x9D,
        .dev_type   = 0x60,
        .dev_cap    = 0x16,
        .capacity   = 0x400000,
        .manuf_name = MANUF_ISSI,
        .model_name = MODEL_IS25LP032,
    },
    {
        .manuf_id   = 0x9D,
        .dev_type   = 0x60,
        .dev_cap    = 0x17,
        .capacity   = 0x800000,
        .manuf_name = MANUF_ISSI,
        .model_name = MODEL_IS25LP064,
    },
    {
        .manuf_id   = 0x9D,
        .dev_type   = 0x60,
        .dev_cap    = 0x18,
        .capacity   = 0x1000000,
        .manuf_name = MANUF_ISSI,
        .model_name = MODEL_IS25LP128,
    },
    {
        .manuf_id   = 0x9D,
        .dev_type   = 0x70,
        .dev_cap    = 0x17,
        .capacity   = 0x800000,
        .manuf_name = MANUF_ISSI,
        .model_name = MODEL_IS25WP064,
    },
    {
        .manuf_id   = 0x9D,
        .dev_type   = 0x70,
        .dev_cap    = 0x18,
        .capacity   = 0x1000000,
        .manuf_name = MANUF_ISSI,
        .model_name = MODEL_IS25WP128,
    },

    // ---- MICRON ----
    {
        .manuf_id   = 0x20,
        .dev_type   = 0x20,
        .dev_cap    = 0x14,
        .capacity   = 0x100000,
        .manuf_name = MANUF_MICRON,
        .model_name = MODEL_M25P80,
    },
    {
        .manuf_id   = 0x20,
        .dev_type   = 0x20,
        .dev_cap    = 0x16,
        .capacity   = 0x400000,
        .manuf_name = MANUF_MICRON,
        .model_name = MODEL_M25P32,
    },
    {
        .manuf_id   = 0x20,
        .dev_type   = 0xBA,
        .dev_cap    = 0x17,
        .capacity   = 0x800000,
        .manuf_name = MANUF_MICRON,
        .model_name = MODEL_N25Q064A,
    },
    {
        .manuf_id   = 0x20,
        .dev_type   = 0xBA,
        .dev_cap    = 0x18,
        .capacity   = 0x1000000,
        .manuf_name = MANUF_MICRON,
        .model_name = MODEL_N25Q128A,
    },

    // ---- SPANSION ----
    {
        .manuf_id   = 0x01,
        .dev_type   = 0x20,
        .dev_cap    = 0x17,
        .capacity   = 0x800000,
        .manuf_name = MANUF_SPANSION,
        .model_name = MODEL_S25FL064P,
    },
    {
        .manuf_id   = 0x01,
        .dev_type   = 0x20,
        .dev_cap    = 0x18,
        .capacity   = 0x1000000,
        .manuf_name = MANUF_SPANSION,
        .model_name = MODEL_S25FL128P,
    },
    {
        .manuf_id   = 0x01,
        .dev_type   = 0x02,
        .dev_cap    = 0x19,
        .capacity   = 0x2000000,
        .manuf_name = MANUF_SPANSION,
        .model_name = MODEL_S25FL256S,
    },

    // ---- SST ----
    {
        .manuf_id   = 0xBF,
        .dev_type   = 0x25,
        .dev_cap    = 0x41,
        .capacity   = 0x200000,
        .manuf_name = MANUF_SST,
        .model_name = MODEL_SST25VF016B,
    },

    // ---- PUYA ----
    {
        .manuf_id   = 0x85,
        .dev_type   = 0x60,
        .dev_cap    = 0x14,
        .capacity   = 0x100000,
        .manuf_name = MANUF_PUYA,
        .model_name = MODEL_P25Q80H,
    },
    {
        .manuf_id   = 0x85,
        .dev_type   = 0x60,
        .dev_cap    = 0x15,
        .capacity   = 0x200000,
        .manuf_name = MANUF_PUYA,
        .model_name = MODEL_P25Q16H,
    },
    {
        .manuf_id   = 0x85,
        .dev_type   = 0x60,
        .dev_cap    = 0x16,
        .capacity   = 0x400000,
        .manuf_name = MANUF_PUYA,
        .model_name = MODEL_P25Q32H,
    },
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
        case MANUF_WINBOND:    return "Winbond";
        case MANUF_EON_SS_INC: return "Eon";
        case MANUF_GIGADEVICE: return "GigaDevice";
        case MANUF_MACRONIX:   return "Macronix";
        case MANUF_SST:        return "SST";
        case MANUF_MICRON:     return "Micron";
        case MANUF_PUYA:       return "Puya";
        case MANUF_ISSI:       return "ISSI";
        case MANUF_SPANSION:   return "Spansion";
        
        default:               return "Not found";
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

        // Winbond
        case MODEL_W25Q80:      return "W25Q80";
        case MODEL_W25Q16JV:    return "W25Q16JV";
        case MODEL_W25Q32JV:    return "W25Q32JV";
        case MODEL_W25Q64JV:    return "W25Q64JV";
        case MODEL_W25Q256JV:   return "W25Q256JV";
        
        // GigaDevice
        case MODEL_GD25Q80C:    return "GD25Q80C";
        case MODEL_GD25Q16C:    return "GD25Q16C";
        case MODEL_GD25Q128C:   return "GD25Q128C";
        
        // Macronix
        case MODEL_MX25L8006E:  return "MX25L8006E";
        case MODEL_MX25L1606E:  return "MX25L1606E";
        case MODEL_MX25L3206E:  return "MX25L3206E";
        case MODEL_MX25L25635F: return "MX25L25635F";
        
        // Micron
        case MODEL_M25P32:      return "M25P32";
        case MODEL_N25Q064A:    return "N25Q064A";
        case MODEL_N25Q128A:    return "N25Q128A";
        
        // ISSI
        case MODEL_IS25LP032:   return "IS25LP032";
        case MODEL_IS25LP064:   return "IS25LP064";
        case MODEL_IS25LP128:   return "IS25LP128";
        case MODEL_IS25WP064:   return "IS25WP064";
        case MODEL_IS25WP128:   return "IS25WP128";
        
        // Spansion
        case MODEL_S25FL064P:   return "S25FL064P";
        case MODEL_S25FL128P:   return "S25FL128P";
        case MODEL_S25FL256S:   return "S25FL256S";
        
        // Puya
        case MODEL_P25Q80H:     return "P25Q80H";
        case MODEL_P25Q16H:     return "P25Q16H";
        
        default:                return "Not found";
    }
}