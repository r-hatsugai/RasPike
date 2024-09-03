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
    bool debris_removal(float d_distance,float leftdistance, float rightdistance);
    bool debris_short(float d_distance,float leftdistance, float rightdistance);

    bool debris_action(float d_distance,float leftdistance, float rightdistance);
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
    bool flag;
    bool turn_flag;
    bool run_flag;

    bool reset = true;
    bool a_flag = true;
    bool b_flag = true;
    bool c_flag = true;
    float distance2;
    float leftdistance2;
    float rightdistance2;
    bool d_flag;
    bool d_flag2;
};
#endif