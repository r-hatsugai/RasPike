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
        void constant_run(int left_motor_power,int right_motor_power);
        void gyro_run(int left_motor_power,int right_motor_power);
        void pid_l_turn(int left_motor_power, int right_motor_power);
        void pid_r_turn(int left_motor_power, int right_motor_power);
        
    GyroSensor gyrosensor;
    //-------------------
    //
    //--------------------
    float angle;
    int diff[2];
    int p;
    int turn_p;
    int turn_P;
    int l_dig;
    int r_dig;
    int L_dig;
    int R_dig;
    int dig;
    int Dig;
    #define KP 1.69
};
#endif