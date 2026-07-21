#include "heartbeat_task.h"
#include "led_driver.h"
#include "cmsis_os.h"

#define HEARTBEAT_PERIOD_MS 500U
#define HEARTBEAT_LED       LED_BLUE

static const osThreadAttr_t heartbeatTaskAttributes = {
  .name = "HeartbeatTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

static void HeartbeatTask_Run(void *argument)
{
    (void)argument;

    for (;;)
    {
        LedDriver_Toggle(HEARTBEAT_LED);
        osDelay(HEARTBEAT_PERIOD_MS);
    }
}


HeartbeatTaskStatus HeartbeatTask_Create(void){
    
    osThreadId_t threadId =
        osThreadNew(HeartbeatTask_Run, NULL, &heartbeatTaskAttributes);

    if (threadId == NULL)
    {
        return HEARTBEAT_TASK_CREATION_FAILED;
    }

    return HEARTBEAT_TASK_OK;
}
