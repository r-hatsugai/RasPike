#include "ConstantTracerClass.h"

ConstantTracerClass::ConstantTracerClass():
     gyrosensor(PORT_4){
    }
void ConstantTracerClass :: constant_run(int left_motor_power,int right_motor_power)
{
    leftWheel.setPWM(left_motor_power);
    rightWheel.setPWM(right_motor_power);

}

void ConstantTracerClass :: gyro_run(int left_motor_power,int right_motor_power)
{    
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

void ConstantTracerClass :: pid_l_turn(int left_motor_power,int right_motor_power)
{
    l_dig = leftWheel.getCount();
    r_dig = rightWheel.getCount();
    
    if(l_dig < 0)
    {
        l_dig = l_dig * -1;
    }
    else if(r_dig < 0)
    {
        r_dig = r_dig * -1;
    }

    dig = l_dig - r_dig;

    turn_p = dig * 0.01;

    leftWheel.setPWM(left_motor_power - turn_p);
    rightWheel.setPWM(right_motor_power + turn_p);
    // leftWheel.reset();
    // rightWheel.reset();
}


void ConstantTracerClass :: pid_r_turn(int left_motor_power,int right_motor_power)
{
    L_dig = leftWheel.getCount();
    R_dig = rightWheel.getCount();
    
    if(L_dig < 0)
    {
        L_dig = L_dig * -1;
    }
    else if(R_dig < 0)
    {
        R_dig = R_dig * -1;
    }

    Dig = R_dig - L_dig;

    turn_P = Dig * 0.0175;

    leftWheel.setPWM(left_motor_power + turn_P);
    rightWheel.setPWM(right_motor_power - turn_P);
    // leftWheel.reset();
    // rightWheel.reset();

}

