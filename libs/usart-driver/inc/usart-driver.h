#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

typedef struct
{
    TaskHandle_t taskHndlr;
    StackType_t taskStackBuff[configMINIMAL_STACK_SIZE];
    StaticTask_t tcb;
    TickType_t xLastWakeTime;
    UBaseType_t taskStackHighWatermark;

}UsartDriver_t;

void usartDriverInit(UsartDriver_t*);