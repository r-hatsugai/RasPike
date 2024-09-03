#include "ConstantTracerClass.h"

void ConstantTracerClass :: constant_run(S32 left_motor_power,S32 right_motor_power)
{
    //------------------------------
    //モータに値格納
    //------------------------------
    leftWheel.setPWM(left_motor_power);
    rightWheel.setPWM(right_motor_power);
}