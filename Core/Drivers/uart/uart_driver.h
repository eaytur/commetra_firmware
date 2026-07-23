#ifndef UART_DRIVER_H
#define UART_DRIVER_H

#include <stdint.h>
#include <stddef.h>

typedef enum
{
    UART_DRIVER_OK = 0,
    UART_DRIVER_NULL_PTR,
    UART_DRIVER_TIMEOUT,
    UART_DRIVER_BUSY,
    UART_DRIVER_ERROR
} UartDriverStatus;

typedef void (*UartDriverNotificationCallback)(void);

UartDriverStatus UartDriver_Write(const uint8_t *data, size_t length);
UartDriverStatus UartDriver_StartReceive(void);
UartDriverStatus UartDriver_RegisterNotificationCallback(UartDriverNotificationCallback callback);

#endif //UART_DRIVER_H