#ifndef INC_UART_COMMUNICATION_H_
#define INC_UART_COMMUNICATION_H_

#include <cmd_parser.h>
#include "main.h"
#include "software_timer.h"
#include "stdio.h"
#include "stdlib.h"
#include "global.h"

void uart_communication_fsm(ADC_HandleTypeDef *hadc1, UART_HandleTypeDef *huart2);


#endif /* INC_UART_COMMUNICATION_H_ */
