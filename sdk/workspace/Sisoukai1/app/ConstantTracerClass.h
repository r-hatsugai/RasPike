#ifndef CONSTANTTRACERCLASS_H
#define CONSTANTTRACERCLASS_H
#include "Tracer.h"

class ConstantTracerClass : public Tracer
{
    public:
        void constant_run(S32 left_motor_power,S32 right_motor_power);
};
#endif