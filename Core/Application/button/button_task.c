#include "button_task.h"
#include "led_driver.h"
#include "button_driver.h"
#include "cmsis_os.h"

#define BUTTON_TASK_LED LED_YELLOW
#define BUTTON_DEBOUNCE_MS    30

static const osThreadAttr_t buttonTaskAttributes = {
  .name = "buttonTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

static osSemaphoreId_t buttonSemaphore;

static void ButtonTask_Run(void *argument)
{
    (void)argument;

    for (;;)
    {
        osStatus_t status =
            osSemaphoreAcquire(buttonSemaphore, osWaitForever);

        if (status != osOK)
        {
            continue;
        }

        osDelay(BUTTON_DEBOUNCE_MS);

        ButtonState state;

        if (ButtonDriver_GetState(BUTTON_USER, &state) != BUTTON_OK)
        {
            continue;
        }

        if (state == BUTTON_PRESSED)
        {
            (void)LedDriver_Toggle(BUTTON_TASK_LED);
        }
        (void)osSemaphoreAcquire(buttonSemaphore, 0U);
    }
}


ButtonTaskStatus ButtonTask_Create(void){

    buttonSemaphore = osSemaphoreNew(1, 0, NULL);
    
    if (buttonSemaphore == NULL)
    {
        return BUTTON_TASK_SEMAPHORE_CREATION_FAILED;
    }

    osThreadId_t threadId =
        osThreadNew(ButtonTask_Run, NULL, &buttonTaskAttributes);

    if (threadId == NULL)
    {
        return BUTTON_TASK_CREATION_FAILED;
    }

    return BUTTON_TASK_OK;
}

void ButtonTask_Notify(void)
{
    if (buttonSemaphore != NULL)
    {
        (void)osSemaphoreRelease(buttonSemaphore);
    }
}
