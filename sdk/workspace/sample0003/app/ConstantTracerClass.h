#ifndef CONSTANTTRACERCLASS_H
#define CONSTANTTRACERCLASS_H
#include "Tracer.h"
#include "GyroSensor.h"
#include "Motor.h"

using namespace ev3api;

class ConstantTracerClass : public Tracer
{
    public:
        ConstantTracerClass();
        void constant_run(S32 left_motor_power,S32 right_motor_power);
        void gyro_run(S32 left_motor_power,S32 right_motor_power);
        
    GyroSensor gyrosensor;
    //-------------------
    //
    //--------------------
    float angle;
    int diff[2];
    int p;
    #define KP 2
};
#endif