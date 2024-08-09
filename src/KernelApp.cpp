#include "KernelApp.h"
#include <cstring>

extern "C" {
    extern void SystemClock_Config(void);
}
char txBuf[50];
KernelApp::KernelApp(): _usdDriver(&htim2, 20, SR04MDriver::HR04_COMPATIBLE),
    sim_7000_mqtt(&hlpuart1, kURL, kPort, kClientID, kUsername, kPassword) {
}

void KernelApp::process() {
    _usdDriver.process();
    switch (_state)
    {
    case INIT:
        sim_7000_mqtt.waitInit();
        sim_7000_mqtt.setupMQTT();
        _state = SELF_TEST;
        break;
        
    case SELF_TEST:
        _state = MEASURE;
        break;

    case MEASURE:
        _usdDriver.measureRequest();
        _state = WAIT_FOR_MEASUREMENT;
        break;

    case WAIT_FOR_MEASUREMENT:
        if (_usdDriver.getMeasureState() == SR04MDriver::DONE)
        {
            sprintf(txBuf, "%f \n", _usdDriver.getCurrentDistance());
            HAL_UART_Transmit(&huart1, (uint8_t*)txBuf , strlen(txBuf), HAL_MAX_DELAY);

          _state = SEND_DATA;  
        }
        break;

    case SEND_DATA:
        sim_7000_mqtt.enableWirelessConnection();
        sim_7000_mqtt.enableMQTT();
        sim_7000_mqtt.publishMessage("test/test_stm", txBuf);
        sim_7000_mqtt.disableMQTT();
        sim_7000_mqtt.disableWirelessConnection();
        _state = GO_TO_SLEEP;
        break;   

    case GO_TO_SLEEP:
        HAL_UART_Transmit(&huart1, (uint8_t*)"Enter\n" , 6, HAL_MAX_DELAY);

        HAL_Delay(10000);
        // HAL_SuspendTick();
        // HAL_RTCEx_SetWakeUpTimer_IT(&hrtc, 0xA, RTC_WAKEUPCLOCK_CK_SPRE_16BITS);
        // HAL_PWR_EnterSTOPMode(PWR_MAINREGULATOR_ON, PWR_STOPENTRY_WFI);
        // HAL_RTCEx_DeactivateWakeUpTimer(&hrtc);
        // SystemClock_Config();
        // HAL_ResumeTick();

        HAL_UART_Transmit(&huart1, (uint8_t*)"Leave\n" , 6, HAL_MAX_DELAY);
        _state = MEASURE;
        break;
    default:
    break;

    }
}

void MainAppInit()
{
  KernelApp::getInstance();
}

void MainAppProcess()
{    
  KernelApp::getInstance().process();
}