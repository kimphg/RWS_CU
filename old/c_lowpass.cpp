
#include "c_lowpass.h"

#define ERROR_CHECK 1

#if ERROR_CHECK
#include <iostream>
#endif

c_lowpass::c_lowpass():
    output(0),
    ePow(0){}

c_lowpass::c_lowpass(float iCutOffFrequency, float iDeltaTime):
    output(0),
    ePow(1-exp(-iDeltaTime * 2 * M_PI * iCutOffFrequency))
{
    #if ERROR_CHECK
    if (iDeltaTime <= 0){
        std::cout << "Warning: A LowPassFilter instance has been configured with 0 s as delta time.";
        ePow = 0;
    }
    if(iCutOffFrequency <= 0){
        std::cout << "Warning: A LowPassFilter instance has been configured with 0 Hz as cut-off frequency.";
        ePow = 0;
    }
    #endif
}

float c_lowpass::update(float input){
    return output += (input - output) * ePow;
}

float c_lowpass::update(float input, float deltaTime, float cutoffFrequency){
    reconfigureFilter(deltaTime, cutoffFrequency); //Changes ePow accordingly.
    return output += (input - output) * ePow;
}

void c_lowpass::reconfigureFilter(float deltaTime, float cutoffFrequency){
    #if ERROR_CHECK
    if (deltaTime <= 0){
        std::cout << "Warning: A LowPassFilter instance has been configured with 0 s as delta time.";
        ePow = 0;
    }
    if(cutoffFrequency <= 0){
        std::cout << "Warning: A LowPassFilter instance has been configured with 0 Hz as cut-off frequency.";
        ePow = 0;
    }
    #endif
    ePow = 1-exp(-deltaTime * 2 * M_PI * cutoffFrequency);
}
