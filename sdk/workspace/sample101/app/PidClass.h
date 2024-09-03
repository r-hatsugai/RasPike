#ifndef PIDCLASS_H
#define PIDCLASS_H
#include "app.h"

class PidClass
{
public:
    //----------------------------
    //関数宣言
    //----------------------------
    int pid_calculate(rgb_raw_t rgb_val, float KP, float KI ,float KD);

    //----------------------------
    //変数
    //----------------------------
    //int distance;
    //int count = 0; 
    float DELTA_T;//周期
    float PID_MAX;//PID変化量の最大値
    float PID_MIN;//
    
    //----------------------------
    //変数S32
    //----------------------------
    typedef int S32;
    typedef unsigned short U16;
    S32 diff[2];//
    S32 integral;//偏差の積分
    S32 diff_brightness; /* 目標輝度値とカラーセンサ値の差分 */
    S32 target_brightness; /* 目標輝度値 uint16_t */  
    //S32 steering_amount;/* ステアリング操舵量 int16_t */
    int Pid;
    S32 p, i, d; 
};
#endif
