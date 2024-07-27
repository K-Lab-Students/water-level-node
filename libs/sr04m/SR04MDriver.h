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

    enum MeasureState_e{
        BUSY,
        DONE
    };

    SR04MDriver(TIM_HandleTypeDef *htim, uint8_t averageTaps, Workmode_e workmode);
    ~SR04MDriver() = default;

    void process();

    void measureRequest();

    void signalCaptured();

    float getCurrentDistance();
    MeasureState_e getMeasureState();
    uint16_t getDurationTicks();
private:
    static SR04MDriver* driverInstance_;
    TIM_HandleTypeDef* timerInstance_{nullptr};
    uint16_t risingTime_{0};
    uint16_t fallingTime_{0};
    uint8_t callbackCnt_{0};
    float distanceRaw_{0.f};
    float distance_{0.f};
    bool samplingFinished_{false};
    float durationS_{0.f};
    uint16_t durationTicks_{0};
    uint32_t freq{0};
    uint8_t averageTaps_{0};
    uint8_t averageTapsCnt_{0};
    float distanceSum_{0.f};
    uint32_t lastSamplingFinishTime{0};
    const uint32_t samplingTimeoutMs{200};
    MeasureState_e measureState_{DONE};

    Workmode_e workmode_{HR04_COMPATIBLE};
    enum States_e {
        IDLE,
        PERFORM_MEASURE,
        MEASURE_IN_PROGRESS,
        FAULT
    };

    bool measureRequest_{false};
    States_e currentState_{IDLE};

    const float speedOfSound_ = 346.1f; //При температуре 25C

    static void tim_ic_callback(TIM_HandleTypeDef *htim);
    /* data */
};

