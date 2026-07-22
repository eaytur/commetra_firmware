#include "uart_task.h"
#include "uart_driver.h"
#include "cmsis_os.h"

#define UART_TASK_PERIOD 1000

static const osThreadAttr_t uartTaskAttributes = {
  .name = "UartTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

static void UartTask_Run(void *argument)
{
    (void)argument;

    UartDriverStatus status = UartDriver_StartReceive();

    if (status != UART_DRIVER_OK)
    {
        // TODO: add error management
    }

    for (;;)
    {
        osDelay(UART_TASK_PERIOD);
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
