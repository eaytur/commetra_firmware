#ifndef UART_DRIVER_H
#define UART_DRIVER_H

#include <stdint.h>
#include <stddef.h>

typedef enum
{
    UART_DRIVER_OK = 0,
    UART_DRIVER_NULL_PTR,
    UART_DRIVER_TIMEOUT,
    UART_DRIVER_ERROR
} UartDriverStatus;

UartDriverStatus UartDriver_Write(const uint8_t *data, size_t length);
UartDriverStatus UartDriver_Read(uint8_t *data, size_t length);

#endif //UART_DRIVER_H