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
    unsigned int f_arg = 0;
    unsigned int s_arg = 0;
    
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
            "%15s %x %i",
            cmd,
            &f_arg,
            &s_arg
        );
        
        // Dump full flash
        if((strcmp(cmd, "dump") == 0) && (cmds_found >= 2))
        {        
            printf("\n");
            
            printf("Press the BOOT button on ESP32 to interrupt dump!\n");
            esp_rom_delay_us(MS_TO_US(1000));
            
            if(s_arg > 1024)
            {
                printf("Too high value for reading! Setting default value: 256 bytes.\n");
                esp_rom_delay_us(MS_TO_US(1000));
                s_arg = 256;
            }
            
            // Example: dump 0x200000 256
            spi_dump_cmd(f_arg, s_arg);
        }
        else if((strcmp(cmd, "read") == 0) && (cmds_found >= 2)) // Read specific flash address 
        {
            printf("\n");
            
            // Example: read 0x000100 256
            spi_read_addr(f_arg, s_arg);
        }
        else if((strcmp(cmd, "jedec") == 0) && cmds_found == 1) // Read JEDEC manufacturer ID
        {        
            printf("\n");

            // Example: jedec
            spi_get_manuf();
        }
        else // Default
        {
            printf("\nInvalid command!\n");
        }
        
        // Clear command buffer
        *idx = 0;
        memset(cmd_buff, 0, sizeof(cmd_buff));
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