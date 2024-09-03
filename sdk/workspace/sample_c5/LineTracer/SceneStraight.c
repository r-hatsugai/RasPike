#include "SceneStraight.h"
#include <stdio.h> 

S32 SceneStraight_pid(S32 diff_brightness,int edge, HSV out)
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
    p = KP * diff[1]; /* P:目標値と現在地との差(偏差)に比例した操作量を調整する制御 */ 
    i = KI * integral; /* I:偏差を時間的に蓄積し、蓄積した量がある大きさになった所で、操作量を増やして偏差をなくすように動作させ、比例動作に積分動作を加えた制御 */
    d = KD * (diff[1] - diff[0]) / DELTA_T; /* D:今回に偏差と前回の偏差を比較し、偏差の大小によって機敏に反応するようにする制御 */
    pid = p + i + d;
    if(pid>PID_MAX){
        pid=PID_MAX;
    }else if(pid<PID_MIN){
        pid=PID_MIN;
    }
    
    //--------------------------------------------------------------------------
    //左右モータ駆動パワーの設定
    //---------------------------------------------------------------------------
    
    if(edge == -1){
        left_motor_power  = (S32)(BASE_SPEED + (pid * LEFT_EDGE)); // int
        right_motor_power = (S32)(BASE_SPEED - (pid * LEFT_EDGE));//steering_amount
    }else{    
        left_motor_power  = (S32)(BASE_SPEED + (pid * RIGHT_EDGE)); // int
        right_motor_power = (S32)(BASE_SPEED - (pid * RIGHT_EDGE));//steering_amount
    }
    /*else if(70 < count){
            left_motor_power = 50;
            right_motor_power = 55;
    }*/
 
 
    /*}else if(out.V <= 10){
        left_motor_power = 65;
        right_motor_power = 60;
    }*/
     ev3_motor_set_power(left_motor, left_motor_power);
    ev3_motor_set_power(right_motor, right_motor_power);
    return;
}