#include "usart-driver.h"

static void usartDriverThread(void*);

void usartDriverInit(UsartDriver_t* usartDriverPtr)
{
        /* Create the task without using any dynamic memory allocation. */
        usartDriverPtr->taskHndlr = xTaskCreateStatic(
                      usartDriverThread,       /* Function that implements the task. */
                      "NAME",          /* Text name for the task. */
                      configMINIMAL_STACK_SIZE,      /* Number of indexes in the xStack array. */
                      ( void * ) 1,    /* Parameter passed into the task. */
                      tskIDLE_PRIORITY,/* Priority at which the task is created. */
                      usartDriverPtr->taskStackBuff,          /* Array to use as the task's stack. */
                      &usartDriverPtr->tcb );  /* Variable to hold the task's data structure. */

        configASSERT(usartDriverPtr->taskHndlr);
}

static void usartDriverThread(void *pvParameters)
{
        for (;;) {
            
        }
}