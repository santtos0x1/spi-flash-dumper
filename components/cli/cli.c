#include "cli.h"
#include "stdio.h"
#include "string.h"
#include "esp_rom_sys.h"
#include "config.h"
#include "cmd.h"

#define CMD_BUFFER_S 8

#define BACKSPACE_KEY 127

void cli_init(int *idx, char *cmd_buff)
{
    // Command name buffer
    char cmd[CMD_BUFFER_S];
    
    // Command arguments
    uint32_t f_arg = 0;
    uint16_t s_arg = 0;
    uint8_t t_arg = 0;
    
    // Read one character from terminal
    int input_char = getchar();
    
    // No character received
    if(input_char == EOF)
    {
        esp_rom_delay_us(1);
        return;
    }
    
    // Execute command when ENTER is pressed
    if((input_char == '\n' || input_char == '\r'))
    {
        // End string with NULL terminator
        cmd_buff[*idx] = '\0';
        
        // Parse command and arguments
        int cmds_found = sscanf(
            cmd_buff,
            "%15s %lx %hu %hhu",
            cmd,
            &f_arg,
            &s_arg,
            &t_arg
        );
        
        //* printf("\nchar: %s\n", cmd_buff); CLI BUFFER DEBUG

        // Dump full flash
        if((strcmp(cmd, "dump") == 0) && (cmds_found >= 2))
        {        
            printf("\n");
            
            printf("Press the BOOT button on ESP32 to interrupt dump!\n");
            esp_rom_delay_us(MS_TO_US(1000));
            
            if ((t_arg != 0) && (t_arg != 1))
            {
                // Sets default value to t_arg (fast_read off);
                printf("Fast read command invalid! Using fast read off\n");
                t_arg = 0;
            }

            if(s_arg > 1024)
            {
                printf("Too high value for reading! Using default value: 256 bytes.\n");
                esp_rom_delay_us(MS_TO_US(1000));
                s_arg = 256;
            }
            
            // Example: dump 0x200000 256 1/0
            spi_dump_cmd(f_arg, s_arg, t_arg);
        }
        else if((strcmp(cmd, "read") == 0) && (cmds_found >= 2)) // Read specific flash address 
        {
            printf("\n");
            
            if ((t_arg != 0) && (t_arg != 1))
            {
                // Sets default value to t_arg (fast_read off);
                printf("Fast read command invalid! Using fast read off\n");
                t_arg = 0;
            }

            // Example: read 0x000100 256 1/0
            spi_read_addr(f_arg, s_arg, t_arg);
        }
        else if((strcmp(cmd, "jedec") == 0) && cmds_found == 1) // Read JEDEC manufacturer ID
        {        
            printf("\n");

            // Example: jedec
            spi_get_manuf();
        }
        else if((strcmp(cmd, "send") == 0) && cmds_found == 2)
        {
            printf("\n");

            uint8_t r_data = spi_send_data((uint8_t)f_arg);
            if(f_arg == 0x00)
            {
                printf("Out-byte: 0x%02x", r_data);
            }
        }
        else if ((strcmp(cmd, "cs") == 0) && cmds_found == 2)
        {
            printf("\n");

            spi_cs_toggle((uint8_t)f_arg);
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
    if(((input_char == BACKSPACE_KEY || input_char == '\b') && *idx > 0))
    {
        (*idx)--;
    
        // Remove character from terminal
        printf("\b \b");
        return;
    }
    
    // Store character if buffer is not full
    if (*idx < CMD_BUF_SIZE - 1)
    {
        cmd_buff[(*idx)++] = (char)input_char;
    
        // Echo typed character
        putchar(input_char);
        fflush(stdout);
    }
}