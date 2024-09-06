#ifndef DEBRIS_H
#define DEBRIS_H

#include "DistanceClass.h"
#include "DirectionClass.h"
#include "CoordinateClass.h"
#include "ConstantTracerClass.h"
#include "Motor.h"
#include "GyroSensor.h"
#include "Tracer.h"
#include <stdbool.h>

using namespace ev3api;

class Debris
{
    public:
    Debris();
    void init();
    //４マス直進、左に90度旋回
    bool debris_removal(float d_distance,float leftdistance, float rightdistance);
    //１マス直進、左に90度旋回
    bool debris_short(float d_distance,float leftdistance, float rightdistance);
    //4マス直進、右に90度旋回
    bool debris_Column_2(float d_distance,float leftdistance, float rightdistance);
    //１マス直進、右に90度旋回
    bool debris_short_2(float d_distance,float leftdistance, float rightdistance);


    //appに呼ばれる関数
    bool debris_action(float d_distance,float leftdistance, float rightdistance);
    //初期化
    void debris_reset();

    //(L字の後半)
    bool debris_removal2(float d_distance, float leftdistance, float rightdistance);
    
    Motor leftWheel;
    Motor rightWheel;
    DistanceClass distance;
    ConstantTracerClass constant;
    GyroSensor gyrosensor;
    Tracer tracer;
    DirectionClass direction;

    float Direction;
    float s_Direction;
    float c_Direction;
    float s2_Direction;

    float P = 0.000001;
    float RD = 0.009;
    float RP = 0.18;
    
    bool flag = true;
    bool turn_flag;
    bool run_flag = true;

    bool sho_2_flag = true;
    bool col_2_flag = true;

    bool reset = true;
    bool a_flag = true;
    bool b_flag = true;
    bool c_flag = true;
    bool d_flag = true;
    bool e_flag = true;
    bool f_flag = true;
    bool g_flag = true;
    bool h_flag = true;

    bool flag2 = true;
    float distance2;
    float leftdistance2;
    float rightdistance2;
    bool d_flag2;
};
#endif