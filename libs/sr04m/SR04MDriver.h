#ifdef __cplusplus
extern "C" {
#endif
#include "tim.h"
#ifdef __cplusplus
}
#endif

class SR04MDriver
{
public:
    enum Workmode_e{
        HR04_COMPATIBLE,
        LOW_POWER_PULSE
    };

    SR04MDriver(Workmode_e);
    ~SR04MDriver() = default;

    void process();

    void measureRequest() {measureRequest_ = true;};

    void signalCaptured();

    float getCurrentDistance();
    uint16_t getDurationTicks();
private:

    static SR04MDriver* driverInstance_;

    uint16_t risingTime_{0};
    uint16_t fallingTime_{0};
    uint8_t callbackCnt_{0};
    float distance_{0.f};
    bool measureFinished_{false};
    float duration{0.f};
    uint16_t durationTicks_{0};
    uint32_t freq{0};
    
    enum States_e {
        IDLE,
        MEASURE_IN_PROGRESS,
        FAULT
    };

    bool measureRequest_{false};
    States_e currentState_{IDLE};

    static void tim_ic_callback(TIM_HandleTypeDef *htim);
    /* data */
};

