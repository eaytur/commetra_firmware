#include "uart_task.h"
#include "cmsis_os2.h"
#include "uart_driver.h"

static const osThreadAttr_t uartTaskAttributes = {
  .name = "UartTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
    
static osSemaphoreId_t uartRxSemaphore;


static void UartTask_Run(void *argument)
{
    (void)argument;
    uint8_t receivedByte;

    if (UartDriver_StartReceive() != UART_DRIVER_OK)
    {
        // TODO: add error management
    }

    for (;;)
    {
        if (osSemaphoreAcquire(uartRxSemaphore, osWaitForever) != osOK)
        {
            continue;
        }

        while (UartDriver_ReadByte(&receivedByte) == UART_DRIVER_OK)
        {
            (void)UartDriver_Write(&receivedByte, 1U);
        }
    }
}

static void UartTask_Notify(void)
{
    if (uartRxSemaphore != NULL)
    {
        (void)osSemaphoreRelease(uartRxSemaphore);
    }
}

UartTaskStatus UartTask_Create(void){

    uartRxSemaphore = osSemaphoreNew(1U, 0U, NULL);

    if (uartRxSemaphore == NULL)
    {
        return UART_TASK_CREATION_FAILED;
    }

    if (UartDriver_RegisterNotificationCallback(UartTask_Notify)
        != UART_DRIVER_OK)
    {
        return UART_TASK_CREATION_FAILED;
    }    

    osThreadId_t threadId =
        osThreadNew(UartTask_Run, NULL, &uartTaskAttributes);

    if (threadId == NULL)
    {
        return UART_TASK_CREATION_FAILED;
    }

    return UART_TASK_OK;
}
