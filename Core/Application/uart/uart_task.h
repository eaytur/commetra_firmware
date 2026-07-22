#ifndef UART_TASK_H
#define UART_TASK_H

typedef enum
{
    UART_TASK_OK = 0,
    UART_TASK_CREATION_FAILED
} UartTaskStatus;

UartTaskStatus UartTask_Create(void);

#endif //UART_TASK_H