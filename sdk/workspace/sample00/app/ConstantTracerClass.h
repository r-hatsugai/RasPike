#ifndef CONSTANTTRACERCLASS_H
#define CONSTANTTRACERCLASS_H
#include "Tracer.h"
#include "GyroSensor.h"

using namespace ev3api;

class ConstantTracerClass : public Tracer
{
    public:
        ConstantTracerClass();
        void constant_run(int left_motor_power,int right_motor_power);
        void goal_run(int left_motor_power,int right_motor_power);

    GyroSensor gyrosensor;

    float angle;
    int past_angle;
    float distance;
};
#endif