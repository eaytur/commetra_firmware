#include "uart_driver.h"
#include "stm32f4xx_hal.h"


#define UART_TIMEOUT_MS    10U

extern UART_HandleTypeDef huart2;

UartDriverStatus UartDriver_Write(const uint8_t *data, size_t length)
{
    if (data == NULL)
    {
        return UART_DRIVER_NULL_PTR;
    }

    HAL_StatusTypeDef halStatus =
        HAL_UART_Transmit(&huart2,
                          (uint8_t *)data,
                          length,
                          UART_TIMEOUT_MS);
   
    switch (halStatus)
    {
        case HAL_OK:
            return UART_DRIVER_OK;

        case HAL_TIMEOUT:
            return UART_DRIVER_TIMEOUT;

        case HAL_BUSY:
        case HAL_ERROR:
        default:
            return UART_DRIVER_ERROR;
    }
}
