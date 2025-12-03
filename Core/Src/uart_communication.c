#include "uart_communication.h"
#include "global.h"
#include "software_timer.h"
#include "stdio.h"
#include "string.h"
void uart_communication_fsm(ADC_HandleTypeDef *hadc1, UART_HandleTypeDef *huart2) {

    if (command_flag == 1) {
        command_flag = 0;

        if (strcmp((char*)command, "RST") == 0) {

            HAL_ADC_Start(hadc1);
            HAL_ADC_PollForConversion(hadc1, 100);
            ADC_value = HAL_ADC_GetValue(hadc1);
            HAL_ADC_Stop(hadc1);

            status_uart = SEND_ADC;
        }
    }

    // ---------------- FSM CHÍNH -----------------
    switch(status_uart) {

    case WAIT_RST:
        break;

    case SEND_ADC:
        sprintf((char*)str, "!ADC=%lu#\r\n", ADC_value);
        HAL_UART_Transmit(huart2, (uint8_t*)str, strlen((char*)str), 50);

        clearTimer(1);
        setTimer(1, 3000);

        status_uart = WAIT_OK;
        break;

    case WAIT_OK:
        if (strcmp((char*)command, "OK") == 0) {
            clearTimer(1);
            status_uart = WAIT_RST;
        }

        if (timer_flag[1] == 1) {
            timer_flag[1] = 0;
            status_uart = SEND_ADC;
        }
        break;
    }
}
