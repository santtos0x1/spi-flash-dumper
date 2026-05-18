#pragma once

// Converts Ms to Us
#define MS_TO_US(x) (x * 1000)

#define FLASH_JEDEC_BYTE 0x9F // JEDEC byte command
#define FLASH_READ_BYTE 0x03 // Read byte command
#define FLASH_FREAD_BYTE 0x0B // Fast Read byte command