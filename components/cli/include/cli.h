#pragma once

#include <stdint.h>

// Command buffer max size
#define CMD_BUF_SIZE 64

void cli_init(uint8_t *idx, char *cmd_buff);