#include "main-app.h"
#include "SR04MDriver.h"
#include "sim7000cmqtt/SIM7000MQTT.hpp"
#ifdef __cplusplus
extern "C" {
#endif
#include "stdio.h"
// #include "AT24Cxx_stm32_hal.h"
#include "main.h"
#include "i2c.h"
#include "usart.h"
#include "tim.h"
#include "gpio.h"
#include <string.h>
#ifdef __cplusplus
}
#endif

const unsigned char testString[] = "test\n";
char txBuf[50];
uint8_t test_bytes[66] = { 1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22,
                           23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44,
                           45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66 };

// uint8_t test_receive[66] = {0};

// uint8_t i2cData[2] = {0,0};
// uint8_t txData[2] = {0x02,0xED};

uint32_t timestp;
SR04MDriver* usdDriver;
const SIM7000MQTT::URL kURL = "212.192.134.141";
const SIM7000MQTT::Port kPort = "1883";
const SIM7000MQTT::CliendID kClientID = "dfrobot";
const SIM7000MQTT::Username kUsername = "homeassistant";
const SIM7000MQTT::Password kPassword = "up4IxZQaVLvxSeYbzRkJ";
SIM7000MQTT* sim_7000_mqtt;
void MainAppInit()
{
    // AT24Cxx_devices_t device_array;

    // AT24Cxx_init(&device_array, 0x00, &hi2c1);
    sim_7000_mqtt = new SIM7000MQTT(&hlpuart1, kURL, kPort, kClientID, kUsername, kPassword);
    sim_7000_mqtt->waitInit();
    sim_7000_mqtt->setupMQTT();

    // sim_7000_mqtt->enableMQTT();

    // sim_7000_mqtt->setupGNSS();

    // sim_7000_mqtt->disableMQTT();

    // usdDriver = new SR04MDriver(&htim2, 20, SR04MDriver::HR04_COMPATIBLE);
    timestp = HAL_GetTick();
}

void MainAppProcess()
{
    // if (!HAL_UART_Transmit(&huart1, testString, sizeof(testString), HAL_MAX_DELAY) == HAL_OK) {
    //   Error_Handler();
    // }
    // if (!HAL_UART_Transmit(&hlpuart1, testString, sizeof(testString), HAL_MAX_DELAY) == HAL_OK) {
    //   Error_Handler();
    // }

    // AT24Cxx_write_byte_buffer(device_array.devices[0], 0x0010, test_bytes, 66);

    // HAL_Delay(2);

    // AT24Cxx_read_byte_buffer(device_array.devices[0], 0x0010, test_receive, 66);

    // HAL_Delay(1000);
    //  HAL_GPIO_TogglePin(outSTATUS_LED_GPIO_Port, outSTATUS_LED_Pin);
    // usdDriver->process();

    if (HAL_GetTick() - timestp >= 5000) {
        // sprintf(txBuf, "%f \n", usdDriver->getCurrentDistance());

        // if (!HAL_UART_Transmit(&huart1, (uint8_t*)txBuf, strlen(txBuf), HAL_MAX_DELAY) == HAL_OK) {
        //   Error_Handler();
        // }
        // if (usdDriver->getMeasureState() == SR04MDriver::MeasureState_e::DONE) {
        //   usdDriver->measureRequest();
        // }

        sim_7000_mqtt->enableMQTT();
        sim_7000_mqtt->publishMessage("test/test_stm", "hi");
        sim_7000_mqtt->disableMQTT();

        timestp = HAL_GetTick();
    }
}