#ifndef C_LOWPASS_H
#define C_LOWPASS_H
#include <cmath>
#define M_PI 3.1415926535
class c_lowpass{
public:
    //constructors
    c_lowpass();
    c_lowpass(float iCutOffFrequency, float iDeltaTime);
    //functions
    float update(float input);
    float update(float input, float deltaTime, float cutoffFrequency);
    //get and configure funtions
    float getOutput() const{return output;}
    void reconfigureFilter(float deltaTime, float cutoffFrequency);
private:
    float output;
    float ePow;
};

#endif // C_LOWPASS_H
