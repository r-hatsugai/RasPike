#include "Scene1.h"
#include <stdio.h> 

S32 Scene1_pid(S32 diff_brightness,int edge, HSV out)
{
    //------------------------------------------------------------------------
    //変数宣言
    //------------------------------------------------------------------------

    static S32 diff[2];
    static S32 integral;
    S32 steering_amount;/* ステアリング操舵量 int16_t */
    S32 pid;
    S32 p, i, d; 
    int count = 0; 
 
    S32 left_motor_power;
    S32 right_motor_power; /*左右モータ設定パワー int*/

    //-------------------------------------------------------------------------
    //センサーの値　ー　目標値
    //-------------------------------------------------------------------------
    diff[0] = diff[1];
    diff[1] = diff_brightness;
    integral += (diff[1] + diff[0]) / 2.0 * DELTA_T;

    //-------------------------------------------------------------------------
    //PID制御
    //-------------------------------------------------------------------------
    p = KP * diff[1]; 
    i = KI * integral; 
    d = KD * (diff[1] - diff[0]) / DELTA_T; 
    pid = p + i + d;
    if(pid>PID_MAX){
        pid=PID_MAX;
    }else if(pid<PID_MIN){
        pid=PID_MIN;
    }
    printf("pid %d\n", pid);

    //--------------------------------------------------------------------------
    //左右モータ駆動パワーの設定
    //---------------------------------------------------------------------------

    left_motor_power  = BASE_SPEED - 21; // int18 -21
    right_motor_power = BASE_SPEED - 32;//steering_amount25 -32
    
    ev3_motor_set_power(left_motor, left_motor_power);
    ev3_motor_set_power(right_motor, right_motor_power);
    return;
}