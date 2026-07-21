#ifndef BUTTON_TASK_H
#define BUTTON_TASK_H

typedef enum
{
    BUTTON_TASK_OK = 0,
    BUTTON_TASK_CREATION_FAILED
} ButtonTaskStatus;

ButtonTaskStatus ButtonTask_Create(void);

#endif //BUTTON_TASK_H