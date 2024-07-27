#include "SR04MDriver.h"

SR04MDriver* SR04MDriver::driverInstance_ = nullptr;

SR04MDriver::SR04MDriver(TIM_HandleTypeDef *htim, uint8_t averageTaps, Workmode_e workmode):
    timerInstance_(htim), averageTaps_(averageTaps)
{
    driverInstance_ = this;
    HAL_TIM_RegisterCallback(timerInstance_, HAL_TIM_IC_CAPTURE_CB_ID, tim_ic_callback);
}

void SR04MDriver::process()
{
    switch (currentState_)
    {
    case IDLE:
        if (measureRequest_)
        {
            measureRequest_ = false;
            
            currentState_ = PERFORM_MEASURE;
        }
        break;

    case PERFORM_MEASURE:
            HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_1);

            HAL_GPIO_WritePin(outUDS_TRIG_GPIO_Port, outUDS_TRIG_Pin, GPIO_PIN_SET);
            HAL_Delay(1);
            HAL_GPIO_WritePin(outUDS_TRIG_GPIO_Port, outUDS_TRIG_Pin, GPIO_PIN_RESET);
            lastSamplingFinishTime = HAL_GetTick();
            currentState_ = MEASURE_IN_PROGRESS;
        break;

    case MEASURE_IN_PROGRESS:

        if (samplingFinished_ )
        {
            samplingFinished_ = false;

            durationTicks_ = fallingTime_ - risingTime_;
            
            durationS_ = 1.f / (static_cast<float>(HAL_RCC_GetPCLK1Freq()) / 10.f / static_cast<float>(durationTicks_));
            
            distanceRaw_ = durationS_ * speedOfSound_ / 2.f;
    
            HAL_TIM_IC_Stop_IT(&htim2, TIM_CHANNEL_1);

            if (averageTapsCnt_ < averageTaps_) {
                distanceSum_ += distanceRaw_;
                averageTapsCnt_++;
                currentState_ = PERFORM_MEASURE;
            } else {
                distance_ = distanceSum_ / static_cast<float>(averageTaps_);
                distanceSum_ = 0.f;
                averageTapsCnt_ = 0;
                currentState_ = IDLE;
            }
        } else if(HAL_GetTick() - lastSamplingFinishTime >= samplingTimeoutMs)
        {
            distanceSum_ = 0.f;
            averageTapsCnt_ = 0;
            currentState_ = IDLE;
            HAL_TIM_IC_Stop_IT(&htim2, TIM_CHANNEL_1);
        }
        
        break;
    
    default:
        break;
    }
}

uint16_t SR04MDriver::getDurationTicks()
{
    return durationTicks_;
}

float SR04MDriver::getCurrentDistance()
{
    return distance_;
}

void SR04MDriver::signalCaptured()
{
    lastSamplingFinishTime = HAL_GetTick();
    if (callbackCnt_ == 0) {
        risingTime_ = HAL_TIM_ReadCapturedValue(&htim2, TIM_CHANNEL_1);
        callbackCnt_++;
    }else {
        fallingTime_  = HAL_TIM_ReadCapturedValue(&htim2, TIM_CHANNEL_1);
        callbackCnt_ = 0;
        samplingFinished_ = true;
    }
}

void SR04MDriver::tim_ic_callback(TIM_HandleTypeDef *htim)
{
    UNUSED(htim);
    //TODO: поддержка нескольких датчиков
    if (driverInstance_)
    {
        driverInstance_->signalCaptured();
    }
}