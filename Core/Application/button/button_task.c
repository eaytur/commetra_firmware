#include "button_task.h"
#include "button_driver.h"
#include "led_driver.h"
#include "cmsis_os.h"

#define BUTTON_TASK BUTTON_USER
#define BUTTON_TASK_LED LED_YELLOW
#define BUTTON_PERIOD_MS 100

static const osThreadAttr_t buttonTaskAttributes = {
  .name = "buttonTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

static void ButtonTask_Run(void *argument)
{
    (void)argument;

    for (;;)
    {
        ButtonState state;

        ButtonStatus status =
            ButtonDriver_GetState(BUTTON_TASK, &state);

        if (status != BUTTON_OK)
        {
            osDelay(BUTTON_PERIOD_MS);
            continue;
        }

        if (state == BUTTON_PRESSED)
        {
            (void)LedDriver_Toggle(BUTTON_TASK_LED);
        }

        osDelay(BUTTON_PERIOD_MS);
    }
}


ButtonTaskStatus ButtonTask_Create(void){
    
    osThreadId_t threadId =
        osThreadNew(ButtonTask_Run, NULL, &buttonTaskAttributes);

    if (threadId == NULL)
    {
        return BUTTON_TASK_CREATION_FAILED;
    }

    return BUTTON_TASK_OK;
}

