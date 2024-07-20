#include "main-app.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "AT24Cxx_stm32_hal.h"
#include "main.h"
#include "i2c.h"
#include "usart.h"
#include "tim.h"
#include "gpio.h"

#ifdef __cplusplus
}
#endif

const unsigned char testString[] = "test\n";

uint8_t test_bytes[66] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,
    17,18,19,20,21,22,23,24,25,26,27,28,29,30,
    31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,
    46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,
    61,62,63,64,65,66};

uint8_t test_receive[66] = {0};

uint8_t i2cData[2] = {0,0};
uint8_t txData[2] = {0x02,0xED};

void MainAppInit()
{
  AT24Cxx_devices_t device_array;

  AT24Cxx_init(&device_array, 0x00, &hi2c1);
}

void MainAppProcess()
{    
    if (!HAL_UART_Transmit(&huart1, testString, sizeof(testString), HAL_MAX_DELAY) == HAL_OK) {
      Error_Handler();
    }
    if (!HAL_UART_Transmit(&hlpuart1, testString, sizeof(testString), HAL_MAX_DELAY) == HAL_OK) {
      Error_Handler();
    }

    // AT24Cxx_write_byte_buffer(device_array.devices[0], 0x0010, test_bytes, 66);

	  // HAL_Delay(2);

	  // AT24Cxx_read_byte_buffer(device_array.devices[0], 0x0010, test_receive, 66);

	  // HAL_Delay(1000);

    HAL_GPIO_TogglePin(outSTATUS_LED_GPIO_Port, outSTATUS_LED_Pin);
    HAL_Delay(500);
}