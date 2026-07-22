#include "uart_task.h"
#include "uart_driver.h"
#include "cmsis_os.h"

#define UART_TX_PERIOD 1000U

static const osThreadAttr_t uartTaskAttributes = {
  .name = "UartTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

static void UartTask_Run(void *argument)
{
    (void)argument;

    static const uint8_t message[] = "hello driver\r\n";

    for (;;)
    {
        (void)UartDriver_Write(message, sizeof(message) - 1U);
        osDelay(UART_TX_PERIOD);
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
