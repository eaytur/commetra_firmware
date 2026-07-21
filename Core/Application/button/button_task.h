#ifndef BUTTON_TASK_H
#define BUTTON_TASK_H

typedef enum
{
    BUTTON_TASK_OK = 0,
    BUTTON_TASK_CREATION_FAILED,
    BUTTON_TASK_SEMAPHORE_CREATION_FAILED
} ButtonTaskStatus;

ButtonTaskStatus ButtonTask_Create(void);
void ButtonTask_Notify(void);

#endif //BUTTON_TASK_H