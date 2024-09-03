#ifndef CONSTANTTRACERCLASS_H
#define CONSTANTTRACERCLASS_H
#include "Tracer.h"

class ConstantTracerClass : public Tracer
{
    public:
        void constant_run(int left_motor_power,int right_motor_power);
};
#endif