#include "main-app.h"

#include "SR04MDriver.h"

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
      SEND_DATA
    };

    States _state{INIT};
    
    KernelApp();

    SR04MDriver _usdDriver;

};