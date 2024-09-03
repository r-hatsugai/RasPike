#include "ConstantTracerClass.h"

ConstantTracerClass::ConstantTracerClass():
    gyrosensor(PORT_4){
    }

void ConstantTracerClass :: constant_run(int left_motor_power,int right_motor_power)
{
    // past_angle=gyrosensor.getAngle();
    // angle+=past_angle;
    angle=gyrosensor.getAngle();

    printf("angle%f\n",angle);
    //------------------------------
    //モータに値格納
    //------------------------------
    if(0 == angle)
    {
        leftWheel.setPWM(left_motor_power);
        rightWheel.setPWM(right_motor_power);
    }
    else if(angle >= 1)
    {
        leftWheel.setPWM(left_motor_power-4);//50は6,80は(-7,-6)100は5
        rightWheel.setPWM(right_motor_power);
    }
    else if(angle <= -1)
    {
        leftWheel.setPWM(left_motor_power);
        rightWheel.setPWM(right_motor_power-6);
    
    }
}

