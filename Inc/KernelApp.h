#include "main-app.h"

#include "SR04MDriver.h"

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

    const uint32_t _measureWaitTimeout{5000};
};