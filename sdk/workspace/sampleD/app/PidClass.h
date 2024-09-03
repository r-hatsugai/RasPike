#ifndef PIDCLASS_H
#define PIDCLASS_H
#include "app.h"
#include "ColorSensor.h"

using namespace ev3api;

class PidClass
{
public:
    PidClass();
    ColorSensor colorSensor;
    //----------------------------
    //関数宣言
    //----------------------------
    float pid_calculate(float KP, float KI ,float KD);

    //----------------------------
    //変数
    //----------------------------
    float DELTA_T;//周期
    float PID_MAX;//PID変化量の最大値
    float PID_MIN;//
    
    //----------------------------
    //変数S32
    //----------------------------
    float diff[2];//
    float integral;//偏差の積分
    float diff_brightness; /* 目標輝度値とカラーセンサ値の差分 */
    float target_brightness; /* 目標輝度値 uint16_t */  
    //S32 steering_amount;/* ステアリング操舵量 int16_t */
    float Pid;
    float p, i, d; 
    rgb_raw_t rgb_val;
};
#endif
