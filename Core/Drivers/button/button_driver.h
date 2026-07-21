#ifndef BUTTON_DRIVER_H
#define BUTTON_DRIVER_H

typedef enum
{
    BUTTON_USER = 0,
    BUTTON_COUNT
} ButtonId;

typedef enum
{
    BUTTON_RELEASED = 0,
    BUTTON_PRESSED
} ButtonState;

typedef enum
{
    BUTTON_OK = 0,
    BUTTON_UNKNOWN_ID,
    BUTTON_NULL_PTR
} ButtonStatus;

ButtonStatus ButtonDriver_GetState(ButtonId button, ButtonState *state);

#endif //BUTTON_DRIVER_H