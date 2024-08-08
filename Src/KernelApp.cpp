#include "KernelApp.h"

KernelApp::KernelApp(): _usdDriver(&htim2, 20, SR04MDriver::HR04_COMPATIBLE) {

}

void KernelApp::process() {
    _usdDriver.process();

    switch (_state)
    {
    case INIT:
        /* code */
        break;
        
    case SELF_TEST:
        /* code */
        break;

    case GO_TO_SLEEP:
        /* code */
        break;

    case MEASURE:
        /* code */
        break;

     case SEND_DATA:
        /* code */
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