#include "ConstantTracerClass.h"

ConstantTracerClass::ConstantTracerClass():
    gyrosensor(PORT_4){
    }

void ConstantTracerClass :: constant_run(S32 left_motor_power,S32 right_motor_power)
{
    // past_angle=gyrosensor.getAngle();
    // angle+=past_angle;
    angle=gyrosensor.getAngle();

    printf("angle%d\n",angle);
    //------------------------------
    //モータに値格納
    //------------------------------
    if(-1<angle && angle<1)
    {
        leftWheel.setPWM(left_motor_power);
        rightWheel.setPWM(right_motor_power);
    }
    else if(angle > 1)
    {
        leftWheel.setPWM(left_motor_power-6);//50は6,100は5
        rightWheel.setPWM(right_motor_power);
    }
    else if(angle < -1)
    {
        leftWheel.setPWM(left_motor_power);
        rightWheel.setPWM(right_motor_power-6);
    
    }
}
void ConstantTracerClass :: goal_run(S32 left_motor_power,S32 right_motor_power)
{
    // past_angle=gyrosensor.getAngle();
    // angle+=past_angle;
    angle=gyrosensor.getAngle();

    printf("angle%d\n",angle);
    //------------------------------
    //モータに値格納
    //------------------------------
    if(-1<angle && angle<1)
    {
        leftWheel.setPWM(-left_motor_power);
        rightWheel.setPWM(-right_motor_power);
    }
    /*else if(angle > 1)
    {
        leftWheel.setPWM(left_motor_power-6);//50は6,100は5
        rightWheel.setPWM(right_motor_power);
    }
    else if(angle < -1)
    {
        leftWheel.setPWM(left_motor_power);
        rightWheel.setPWM(right_motor_power-6);
    
    }*/
}