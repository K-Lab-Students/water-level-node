#include "SR04MDriver.h"

SR04MDriver* SR04MDriver::driverInstance_ = nullptr;


SR04MDriver::SR04MDriver(Workmode_e workmode)
{
    driverInstance_ = this;
    HAL_TIM_RegisterCallback(&htim2, HAL_TIM_IC_CAPTURE_CB_ID, tim_ic_callback);
}

void SR04MDriver::process()
{
    switch (currentState_)
    {
    case IDLE:
        if (measureRequest_)
        {
            measureRequest_ = false;
            currentState_ = MEASURE_IN_PROGRESS;
            HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_1);
            HAL_GPIO_WritePin(outUDS_TRIG_GPIO_Port, outUDS_TRIG_Pin, GPIO_PIN_SET);
            HAL_Delay(1);
            HAL_GPIO_WritePin(outUDS_TRIG_GPIO_Port, outUDS_TRIG_Pin, GPIO_PIN_RESET);
        }
        break;
    case MEASURE_IN_PROGRESS:
        if (measureFinished_)
        {
            measureFinished_ = false;

            durationTicks_ = fallingTime_ - risingTime_;

            duration = 1.f / ((float)HAL_RCC_GetPCLK1Freq() / 10.f / durationTicks_);
            
            distance_ = duration * 344.f / 2.f;

            currentState_ = IDLE;
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
    if (callbackCnt_ == 0) {
        risingTime_ = HAL_TIM_ReadCapturedValue(&htim2, TIM_CHANNEL_1);
        callbackCnt_++;
    }else {
        fallingTime_  = HAL_TIM_ReadCapturedValue(&htim2, TIM_CHANNEL_1);
        callbackCnt_ = 0;
        measureFinished_ = true;
    }
}

void SR04MDriver::tim_ic_callback(TIM_HandleTypeDef *htim)
{
    if (driverInstance_)
    {
        driverInstance_->signalCaptured();
    }
}