/**
 * @file ui.c
 * @brief ???
*/

/* Includes ------------------------------------------------------------------*/
#include "ui.h"


////////////////GET COMMANDS/////////////////////
#define CMD_GET "GET SETTINGS"
#define CMD_GET_LENGTH 12

/////////////////SET COMMANDS/////////////////////
#define CMD_SET "SET "
#define CMD_SET_LENGTH 4

//EXAMPLE
#define CMD_EXAMPLE "EXAMPLE "
#define CMD_EXAMPLE_LENGTH 8

//...

/////////////////CTRL COMMANDS/////////////////////
#define CMD_START "START"
#define CMD_START_LENGTH 5

#define CMD_STOP "STOP"
#define CMD_STOP_LENGTH 4


/* Helper Functions ----------------------------------------------------------*/

int teststr(uint8_t *input, uint32_t in_length, uint8_t *test, uint32_t test_length, uint32_t offset)
{
    // Check if the input buffer is long enough to contain the test string
    if (in_length < test_length + offset)
    {
        return 0;
    }
    // Check if the input buffer contains the test string
    if (strncmp((char*)input + offset, (char*)test, test_length) == 0)
    {
        return 1;
    }
    return 0;
}

int cmd_to_int(uint8_t *input, uint32_t in_length, uint32_t *value, uint32_t offset)
{
    uint32_t i = 0;
    *value = 0;
    while (i < in_length - offset)
    {
        if (input[i + offset] >= '0' && input[i + offset] <= '9')
        {
            *value = *value * 10 + (input[i + offset] - '0');
        }
        else
        {
            return i;
        }
        i++;
    }
    return i;
}


void UI_PhraseCommand(uint8_t *cmd, uint32_t cmd_length)
{
    int offset = 0;

    ///////////////////////////GET COMMANDS/////////////////////
    if (teststr(cmd, cmd_length, (uint8_t*)CMD_GET, CMD_GET_LENGTH, 0))
    {
        UI_printsettings();
    }
    ///////////////////////////SET COMMANDS/////////////////////
    if (teststr(cmd, cmd_length, (uint8_t*)CMD_SET, CMD_SET_LENGTH, offset))
    {
        offset += CMD_SET_LENGTH;
        //EXAMPLE
        if (teststr(cmd, cmd_length, (uint8_t*)CMD_EXAMPLE, CMD_EXAMPLE_LENGTH, offset))
        {
            offset += CMD_EXAMPLE_LENGTH;

            /// ...
        }
    }
    ///////////////////////////CTRL COMMANDS/////////////////////
    if (teststr(cmd, cmd_length, (uint8_t*)CMD_START, CMD_START_LENGTH, 0))
    {
        /// ...
    }
    if (teststr(cmd, cmd_length, (uint8_t*)CMD_STOP, CMD_STOP_LENGTH, 0))
    {
        /// ...
    }
}

void UI_println(char *str)
{
  UI_UART_TX_Blocking((uint8_t*)str, strlen(str));
  UI_UART_TX_Blocking((uint8_t*)"\r\n", 2);
}

void UI_print(char *str)
{
  UI_UART_TX_Blocking((uint8_t*)str, strlen(str));
}

void UI_printBin16(uint16_t data)
{
  char binaryString[17]; 

  for (int i = 15; i >= 0; i--) {
      binaryString[15 - i] = (data & (1 << i)) ? '1' : '0';
  }
  binaryString[16] = '\0'; 

  UI_UART_TX_Blocking((uint8_t*)binaryString, 16);
}

void UI_printDec16(uint16_t data)
{
  char decString[6]; 
  sprintf(decString, "%d", data);
  UI_UART_TX_Blocking((uint8_t*)decString, strlen(decString));
}
