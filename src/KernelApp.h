#include "main-app.h"
#include "SR04MDriver.h"
#include "sim7000cmqtt/SIM7000MQTT.hpp"

extern "C" {
    #include "rtc.h"
    #include "usart.h"
}

class KernelApp
{
public:
    static KernelApp& getInstance() {
        static KernelApp instance;
        return instance;
    }

    void process();

private:
    enum States{
      INIT,
      SELF_TEST,
      GO_TO_SLEEP,
      MEASURE,
      WAIT_FOR_MEASUREMENT,
      SEND_DATA
    };

    States _state{INIT};
    
    KernelApp();

    SR04MDriver _usdDriver;

    SIM7000MQTT sim_7000_mqtt;

    const uint32_t _measureWaitTimeout{5000};

    const SIM7000MQTT::URL kURL = "212.192.134.141";
    const SIM7000MQTT::Port kPort = 1883;
    const SIM7000MQTT::CliendID kClientID = "dfrobot";
    const SIM7000MQTT::Username kUsername = "homeassistant";
    const SIM7000MQTT::Password kPassword = "up4IxZQaVLvxSeYbzRkJ";
};