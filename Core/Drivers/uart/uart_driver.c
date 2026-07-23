#include "uart_driver.h"
#include "ring_buffer.h"

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_uart.h"

#define UART_TX_TIMEOUT_MS  10U
#define UART_RX_BUFFER_SIZE  128U

extern UART_HandleTypeDef huart2;

static UartDriverNotificationCallback notificationCallback = NULL;

static uint8_t uartRxByte;
static uint8_t uartRxStorage[UART_RX_BUFFER_SIZE];
static RingBuffer uartRxBuffer;

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
    RingBufferStatus ringBufferStatus =
        RingBuffer_Init(&uartRxBuffer,
                    uartRxStorage,
                    UART_RX_BUFFER_SIZE);

    if (ringBufferStatus != RING_BUFFER_OK)
    {
        return UART_DRIVER_ERROR;
    }

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

    RingBufferStatus ringBufferStatus =
        RingBuffer_Push(&uartRxBuffer, uartRxByte);

    (void)HAL_UART_Receive_IT(&huart2,
                              &uartRxByte,
                              1U);
    
    if ((ringBufferStatus == RING_BUFFER_OK) &&
        (notificationCallback != NULL))
    {
        notificationCallback();
    }
}

UartDriverStatus UartDriver_RegisterNotificationCallback(UartDriverNotificationCallback callback)
{
    if (callback == NULL)
    {
        return UART_DRIVER_NULL_PTR;
    }

    notificationCallback = callback;

    return UART_DRIVER_OK;
}
UartDriverStatus UartDriver_ReadByte(uint8_t *data)
{
    if (data == NULL)
    {
        return UART_DRIVER_NULL_PTR;
    }

    RingBufferStatus status =
        RingBuffer_Pop(&uartRxBuffer, data);

    switch (status)
    {
        case RING_BUFFER_OK:
            return UART_DRIVER_OK;

        case RING_BUFFER_EMPTY:
            return UART_DRIVER_NO_DATA;

        case RING_BUFFER_NULL_PTR:
        case RING_BUFFER_INVALID_CAPACITY:
        default:
            return UART_DRIVER_ERROR;
    }
}
