#ifndef CONSTANTTRACERCLASS_H
#define CONSTANTTRACERCLASS_H
#include "Tracer.h"
#include "jikoiti.h"
//#include "GyroSensor.h"

class ConstantTracerClass : public Tracer
{
    public:
        void constant_run(S32 left_motor_power,S32 right_motor_power);

        //----------------------------
        //インスタンス
        //----------------------------
        //GyroSensor gyro;
};
#endif