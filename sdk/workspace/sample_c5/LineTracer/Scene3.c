#include "Scene3.h"
#include <stdio.h> 

S32 Scene3_pid(S32 diff_brightness,int edge, HSV out)
{
    //------------------------------------------------------------------------
    //変数宣言
    //------------------------------------------------------------------------
    
    S32 left_motor_power;
    S32 right_motor_power; /*左右モータ設定パワー int*/

    //--------------------------------------------------------------------------
    //左右モータ駆動パワーの設定
    //---------------------------------------------------------------------------
    
    if(edge == -1){
        left_motor_power  = BASE_SPEED - 25; // int -25
        right_motor_power = BASE_SPEED - 24;//steering_amount -24
    }
        
    ev3_motor_set_power(left_motor, left_motor_power);
    ev3_motor_set_power(right_motor, right_motor_power);
    return;
}