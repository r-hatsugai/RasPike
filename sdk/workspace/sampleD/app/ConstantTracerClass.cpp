#include "ConstantTracerClass.h"

void ConstantTracerClass :: constant_run(int left_motor_power,int right_motor_power)
{
    //------------------------------
    //モータに値格納
    //------------------------------
    leftWheel.setPWM(left_motor_power);
    rightWheel.setPWM(right_motor_power);
}