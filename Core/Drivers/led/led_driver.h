#ifndef LED_DRIVER_H
#define LED_DRIVER_H

typedef enum{
    LED_BLUE = 0,
    LED_YELLOW,
    LED_RED,
    LED_COUNT
}LedId;

typedef enum{
    LED_OK = 0,
    LED_UNKNOWN_ID,
    LED_NULL_PTR
}LedStatus;

typedef enum{
    LED_OFF = 0,
    LED_ON
}LedState;

LedStatus LedDriver_On(LedId led);
LedStatus LedDriver_Off(LedId led);
LedStatus LedDriver_Toggle(LedId led);
LedStatus LedDriver_GetState(LedId led, LedState *state);

#endif //LED_DRIVER_H