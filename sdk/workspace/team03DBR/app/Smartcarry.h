#ifndef SMARTCARRY_H
#define SMARTCARRY_H

#include "DistanceClass.h"
#include "DirectionClass.h"
#include "CoordinateClass.h"
#include "ConstantTracerClass.h"
#include "Motor.h"
#include "GyroSensor.h"
#include "Tracer.h"
#include <stdbool.h>

using namespace ev3api;

class Smartcarry
{
    public:
    Smartcarry();
    void init();
    bool Smart_carry(float leftdistance, float rightdistance);
    
    Motor leftWheel;
    Motor rightWheel;
    DistanceClass distance;
    DirectionClass direction;
    ConstantTracerClass constant;
    CoordinateClass coordinate;
    GyroSensor gyrosensor;
    Tracer tracer;

    int cur_gridX;//現在位置座標のX値
    int cur_gridY;//現在位置座標のY値
    float target_dir;//現在位置座標から目標座標までの距離
    float target_dis;//現在位置座標から目標座標までの方位
    float cur_dir;//方位計の現在値
    float cur_dis;//距離計の現在値
    int grid_count;//目標座標構造体への参照カウンタ
    float leftdistance;
    float rightdistance;
    bool flag;
};
#endif