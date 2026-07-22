#include "uart_task.h"
#include "uart_driver.h"
#include "cmsis_os.h"

static const osThreadAttr_t uartTaskAttributes = {
  .name = "UartTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

static void UartTask_Run(void *argument)
{
    (void)argument;

    uint8_t data = 0;

    for (;;)
    {
        UartDriverStatus status = UartDriver_Read(&data, 1U);

        if (status == UART_DRIVER_OK)
        {
            (void)UartDriver_Write(&data, 1U);
        }
    }
}

UartTaskStatus UartTask_Create(void){
    
    osThreadId_t threadId =
        osThreadNew(UartTask_Run, NULL, &uartTaskAttributes);

    if (threadId == NULL)
    {
        return UART_TASK_CREATION_FAILED;
    }

    return UART_TASK_OK;
}
