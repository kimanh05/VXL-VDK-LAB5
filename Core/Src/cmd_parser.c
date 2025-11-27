#include "cmd_parser.h"
#include "global.h"
extern UART_HandleTypeDef huart2;

void command_parser_fsm() {

    switch (status_parser) {

    case INIT_STR:
        if (temp == '!') {
            status_parser = WAIT_END;
            command_index = 0;

            char dbg[] = "<START>\r";
            HAL_UART_Transmit(&huart2, (uint8_t*)dbg, strlen(dbg), 10);
        }
        break;

    case WAIT_END:
        if (temp == '#') {
            command[command_index] = '\0';
            command_flag = 1;
            status_parser = INIT_STR;

            char dbg2[50];
            sprintf(dbg2, "\n<CMD=%s>\r\n", command);
            HAL_UART_Transmit(&huart2, (uint8_t*)dbg2, strlen(dbg2), 10);
        }
        else if (temp == '!') {
            command_index = 0;
            char dbg3[] = "<RESTART>\r\n";
            HAL_UART_Transmit(&huart2, (uint8_t*)dbg3, strlen(dbg3), 10);
        }
        else {
            if (command_index < MAX_BUFFER_SIZE - 1) {
                command[command_index++] = temp;
            }
        }
        break;
    }
}
