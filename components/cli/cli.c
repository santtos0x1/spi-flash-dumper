#include "cli.h"
#include "stdio.h"
#include "string.h"
#include "esp_rom_sys.h"
#include "config.h"
#include "cmd.h"

void cli_init(int *idx, char *cmd_buff)
{
    // Command name buffer
    char cmd[16];
    
    // Command arguments
    unsigned int addr_cmd = 0;
    unsigned int data = 0;
    
    // Read one character from terminal
    int c = getchar();
    
    // No character received
    if(c == EOF)
    {
        esp_rom_delay_us(1);
        return;
    }
    
    // Execute command when ENTER is pressed
    if((c == '\n' || c == '\r'))
    {
        // End string with NULL terminator
        cmd_buff[*idx] = '\0';
        
        // Parse command and arguments
        int cmds_found = sscanf(
            cmd_buff,
            "%15s %x %x",
            cmd,
            &addr_cmd,
            &data
        );
        
        // Invalid command
        if(cmds_found < 2)
        {
            printf("ERROR: invalid command length.\n");
        }
        else
        {
            // Dump full flash
            if(strcmp(cmd, "dump") == 0)
            {        
                printf("\n");
                printf("Press the BOOT button on ESP32 to interrupt dump!\n");
                esp_rom_delay_us(MS_TO_US(1000));
                // Example:
                // dump 0x03 0x200000
                spi_dump_cmd(data, addr_cmd);
            }
            else if(strcmp(cmd, "read") == 0)
            {
                // Read specific flash address 

                printf("\n");
                
                // Example:
                // read 0x03 0x000100
                spi_read_addr(data, DEFAULT_24BIT_SET, addr_cmd);
            }
            else if(strcmp(cmd, "getman") == 0)
            {
                // Read JEDEC manufacturer ID
                
                printf("\n");

                // Example:
                // getman 0x9F
                spi_get_manuf(addr_cmd);
            }
            else // Default
            {
                printf("Invalid command!\n");
            }

            // Clear command buffer
            *idx = 0;
            
            memset(cmd_buff, 0, sizeof(cmd_buff));
        }
    }
    
    // Handle backspace
    if(((c == 127 || c == '\b') && *idx > 0))
    {
        (*idx)--;
    
        // Remove character from terminal
        printf("\b \b");

        return;
    }
    
    // Store character if buffer is not full
    if (*idx < CMD_BUF_SIZE - 1)
    {
        cmd_buff[(*idx)++] = (char)c;
    
        // Echo typed character
        putchar(c);
        fflush(stdout);
    }
}