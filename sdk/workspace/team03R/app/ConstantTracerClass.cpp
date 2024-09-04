#include "ConstantTracerClass.h"

ConstantTracerClass::ConstantTracerClass():
     gyrosensor(PORT_4){
    }
void ConstantTracerClass :: constant_run(int left_motor_power,int right_motor_power)
{
    l_dig = leftWheel.getCount();
    r_dig = rightWheel.getCount();
    
    printf("leftdig%d\n", l_dig);
    printf("rightdig%d\n", r_dig);
    printf("rightdig%d\n", r_dig);

    if(l_dig < 0)
    {
        l_dig = l_dig * -1;
    }
    else if(r_dig < 0)
    {
        r_dig = r_dig * -1;
    }

    dig = r_dig - l_dig;

    turn_p = dig * 0.1176;//0.11~0.12の間,0.1176

    if(l_dig < r_dig)
    {
        leftWheel.setPWM(left_motor_power + turn_p);
        rightWheel.setPWM(right_motor_power);
    }
    else if(l_dig > r_dig)
    {
        turn_P = turn_P * 0.8; ///0.8
        leftWheel.setPWM(left_motor_power - turn_P);
        rightWheel.setPWM(right_motor_power);
    }

}

void ConstantTracerClass :: gyro_run(int left_motor_power,int right_motor_power)
{    
    angle=gyrosensor.getAngle();

    diff[0] = diff[1];
    diff[1] = angle;
    p = KP * diff[1];

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

    turn_p = dig * 0.095;

    leftWheel.setPWM(left_motor_power - turn_p);
    rightWheel.setPWM(right_motor_power + turn_p);
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

    turn_P = Dig * 0.06;

    leftWheel.setPWM(left_motor_power + turn_P);
    rightWheel.setPWM(right_motor_power - turn_P);
}

