#include "Scene2.h"
#include <stdio.h> 

S32 Scene2_pid(S32 diff_brightness,int edge, HSV out)
{
    //------------------------------------------------------------------------
    //変数宣言
    //------------------------------------------------------------------------
    
    static S32 diff[2];
    static S32 integral;
    S32 steering_amount;/* ステアリング操舵量 int16_t */
    S32 pid;
    S32 p, i, d;
    S32 left_motor_power;
    S32 right_motor_power; /*左右モータ設定パワー int*/
    int count = 0; 

    //-------------------------------------------------------------------------
    //ステアリング操舵量を計算
    //-------------------------------------------------------------------------
    //steering_amount = (int16_t)(diff_brightness * STEERING_COEF);

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
    
    if(edge == -1){
        left_motor_power  = (S32)(BASE_SPEED + (pid * LEFT_EDGE)-23); // int -23
        right_motor_power = (S32)(BASE_SPEED - (pid * LEFT_EDGE)-23);//steering_amount -23
    }else if(edge == 1){
        left_motor_power  = (S32)(BASE_SPEED + (pid * RIGHT_EDGE)-23); // int -23
        right_motor_power = (S32)(BASE_SPEED - (pid * RIGHT_EDGE)-23);//steering_amount -23
    }
        
    /*}else if(out.V <= 10){
        left_motor_power = 65;
        right_motor_power = 60;
   }*/
    ev3_motor_set_power(left_motor, left_motor_power);
    ev3_motor_set_power(right_motor, right_motor_power);
    return;
}