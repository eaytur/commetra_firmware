#include "led_driver.h"
#include "main.h"
#include "stm32f4xx_hal_gpio.h"

typedef struct
{
    GPIO_TypeDef *port;
    uint16_t pin;
} LedInfo;

static const LedInfo ledInfoTable[LED_COUNT] =
{
    [LED_BLUE] =
    {
        .port = LED_BLUE_GPIO_Port,
        .pin  = LED_BLUE_Pin
    },

    [LED_YELLOW] =
    {
        .port = LED_YELLOW_GPIO_Port,
        .pin  = LED_YELLOW_Pin
    },

    [LED_RED] =
    {
        .port = LED_RED_GPIO_Port,
        .pin  = LED_RED_Pin
    }
};

LedStatus LedDriver_On(LedId led){

    if ((uint32_t)led >= (uint32_t)LED_COUNT)
    {
        return LED_UNKNOWN_ID;
    }

    HAL_GPIO_WritePin(ledInfoTable[led].port, ledInfoTable[led].pin, GPIO_PIN_SET);

    return LED_OK;
}

LedStatus LedDriver_Off(LedId led){
    
    if ((uint32_t)led >= (uint32_t)LED_COUNT)
    {
        return LED_UNKNOWN_ID;
    }

    HAL_GPIO_WritePin(ledInfoTable[led].port, ledInfoTable[led].pin, GPIO_PIN_RESET);

    return LED_OK;
}

LedStatus LedDriver_Toggle(LedId led){
    
    if ((uint32_t)led >= (uint32_t)LED_COUNT)
    {
        return LED_UNKNOWN_ID;
    }

    HAL_GPIO_TogglePin(ledInfoTable[led].port, ledInfoTable[led].pin);

    return LED_OK;
}

LedStatus LedDriver_GetState(LedId led, LedState *state){

    if(state == NULL){
        return LED_NULL_PTR;
    }
    
    if ((uint32_t)led >= (uint32_t)LED_COUNT)
    {
        return LED_UNKNOWN_ID;
    }

    GPIO_PinState pinState = HAL_GPIO_ReadPin(ledInfoTable[led].port, ledInfoTable[led].pin);
    *state = (pinState == GPIO_PIN_SET) ? LED_ON : LED_OFF;    
   
    return LED_OK;
}