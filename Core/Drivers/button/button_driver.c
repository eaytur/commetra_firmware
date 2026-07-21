#include "button_driver.h"
#include "main.h"
#include "stm32f4xx_hal_gpio.h"

typedef struct
{
    GPIO_TypeDef *port;
    uint16_t pin;
    GPIO_PinState pressedLevel;
} ButtonInfo;

static const ButtonInfo buttonInfoTable[BUTTON_COUNT] =
{
    [BUTTON_USER] =
    {
        .port = USER_BUTTON_GPIO_Port,
        .pin  = USER_BUTTON_Pin,
        .pressedLevel = GPIO_PIN_SET
    }
};

ButtonStatus ButtonDriver_GetState(ButtonId button, ButtonState *state)
{
    if (state == NULL)
    {
        return BUTTON_NULL_PTR;
    }

    if ((uint32_t)button >= (uint32_t)BUTTON_COUNT)
    {
        return BUTTON_UNKNOWN_ID;
    }

    const ButtonInfo *buttonInfo = &buttonInfoTable[button];

    const GPIO_PinState pinState = HAL_GPIO_ReadPin(buttonInfo->port, buttonInfo->pin);

    *state = (pinState == buttonInfo->pressedLevel) ? BUTTON_PRESSED : BUTTON_RELEASED;

    return BUTTON_OK;
}