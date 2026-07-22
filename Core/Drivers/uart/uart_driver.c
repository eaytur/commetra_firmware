#include "uart_driver.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_uart.h"


#define UART_TX_TIMEOUT_MS  10U
#define UART_RX_TIMEOUT_MS  HAL_MAX_DELAY

extern UART_HandleTypeDef huart2;
static uint8_t uartRxByte;

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
                          UART_TX_TIMEOUT_MS);
   
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

UartDriverStatus UartDriver_StartReceive(void)
{
    HAL_StatusTypeDef halStatus =
        HAL_UART_Receive_IT(&huart2,
                            &uartRxByte,
                            1U);

    switch (halStatus)
    {
        case HAL_OK:
            return UART_DRIVER_OK;

        case HAL_BUSY:
            return UART_DRIVER_BUSY;

        case HAL_ERROR:
        case HAL_TIMEOUT:
        default:
            return UART_DRIVER_ERROR;
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart != &huart2)
    {
        return;
    }

    (void)HAL_UART_Receive_IT(&huart2,
                              &uartRxByte,
                              1U);
}