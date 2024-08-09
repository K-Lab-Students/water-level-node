#include "KernelApp.h"
#include <cstring>

extern "C" {
    extern void SystemClock_Config(void);
}

KernelApp::KernelApp(): _usdDriver(&htim2, 20, SR04MDriver::HR04_COMPATIBLE) {

}

void KernelApp::process() {
    _usdDriver.process();
    switch (_state)
    {
    case INIT:
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
          _state = SEND_DATA;  
        }
        break;

    case SEND_DATA:
        _state = GO_TO_SLEEP;
        break;   

    case GO_TO_SLEEP:
        HAL_UART_Transmit(&huart1, (uint8_t*)"Enter\n" , 6, HAL_MAX_DELAY);

        // HAL_Delay(10000);
        HAL_SuspendTick();
        HAL_RTCEx_SetWakeUpTimer_IT(&hrtc, 0xA, RTC_WAKEUPCLOCK_CK_SPRE_16BITS);
        HAL_PWR_EnterSTOPMode(PWR_MAINREGULATOR_ON, PWR_STOPENTRY_WFI);
        HAL_RTCEx_DeactivateWakeUpTimer(&hrtc);
        SystemClock_Config();
        HAL_ResumeTick();

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