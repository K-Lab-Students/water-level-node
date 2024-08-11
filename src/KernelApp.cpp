#include "KernelApp.h"
#include <cstring>

#define LOG(msg) \
 HAL_UART_Transmit(&huart1, (uint8_t*)msg , sizeof(msg) - 1, HAL_MAX_DELAY)

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

        if (sim_7000_mqtt.setupMQTT() == SIM7000MQTT::Status::kOk) {
            LOG("setupMQTT OK\r\n");
        }else {
            LOG("setupMQTT ERR\r\n");
        }

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
        if (sim_7000_mqtt.enableWirelessConnection() == SIM7000MQTT::Status::kOk) {
            LOG("enableWirelessConnection OK\r\n");
        }else {
            LOG("enableWirelessConnection ERR\r\n");
        }

        if (sim_7000_mqtt.enableMQTT() == SIM7000MQTT::Status::kOk) {
            LOG("enableMQTT OK\r\n");
        }else {
            LOG("enableMQTT ERR\r\n");
        }
        
        if (sim_7000_mqtt.publishMessage("test/test_stm", txBuf) == SIM7000MQTT::Status::kOk) {
            LOG("publishMessage OK\r\n");
        }else {
            LOG("publishMessage ERR\r\n");
        }

        if (sim_7000_mqtt.disableMQTT() == SIM7000MQTT::Status::kOk) {
            LOG("disableMQTT OK\r\n");
        }else {
            LOG("disableMQTT ERR\r\n");
        }

        if (sim_7000_mqtt.disableWirelessConnection() == SIM7000MQTT::Status::kOk) {
            LOG("disableWirelessConnection OK\r\n");
        }else {
            LOG("disableWirelessConnection ERR\r\n");
        }

        _state = GO_TO_SLEEP;
        break;   

    case GO_TO_SLEEP:
        LOG("Enter sleep mode\r\n");

        #ifdef DEBUG
        HAL_Delay(10000);
        #else
        HAL_SuspendTick();
        HAL_RTCEx_SetWakeUpTimer_IT(&hrtc, 0x12C, RTC_WAKEUPCLOCK_CK_SPRE_16BITS);
        HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
        HAL_RTCEx_DeactivateWakeUpTimer(&hrtc);
        SystemClock_Config();
        HAL_ResumeTick();
        #endif

        LOG("Exit sleep mode\r\n");
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