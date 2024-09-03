#include "ConstantTracerClass.h"

ConstantTracerClass::ConstantTracerClass():
     gyrosensor(PORT_4){
    }
void ConstantTracerClass :: constant_run(S32 left_motor_power,S32 right_motor_power)
{
    leftWheel.setPWM(left_motor_power);
    rightWheel.setPWM(right_motor_power);
}

void ConstantTracerClass :: gyro_run(S32 left_motor_power,S32 right_motor_power)
{
    // past_angle=gyrosensor.getAngle();
    // angle+=past_angle;
    angle=gyrosensor.getAngle();

    diff[0] = diff[1];
    diff[1] = angle;
    p = KP * diff[1];


    printf("angle%f\n",angle);
    //------------------------------
    //モータに値格納
    //------------------------------
    leftWheel.setPWM(left_motor_power - p);
    rightWheel.setPWM(right_motor_power + p);

}

