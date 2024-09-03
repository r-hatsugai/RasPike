#ifndef CONSTANTTRACERCLASS_H
#define CONSTANTTRACERCLASS_H
#include "Tracer.h"
#include "GyroSensor.h"

using namespace ev3api;

class ConstantTracerClass : public Tracer
{
    public:
        ConstantTracerClass();
        void constant_run(S32 left_motor_power,S32 right_motor_power);
        void goal_run(S32 left_motor_power,S32 right_motor_power);
    GyroSensor gyrosensor;

    int angle;
    int past_angle;
};
#endif