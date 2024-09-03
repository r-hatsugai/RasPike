#ifndef SCENECLASS_H
#define SCENECLASS_H

#include "SonarSensor.h"
#include "ColorSensor.h"
#include "GyroSensor.h"
#include "Tracer.h"
#include "EdgeExchangeClass.h"
#include "ConstantTracerClass.h"
#include "DirectionClass.h"
#include "Motor.h"
#include <stdbool.h>

using namespace ev3api;

class SceneClass
{
public:
    //---------------------------------
    //関数定義
    //---------------------------------
    SceneClass();
    bool scene_decide(float distance);

    //---------------------------------
    //インスタンス
    //---------------------------------
    Tracer tracer;
    ColorSensor colorSensor;
    Motor leftWheel;
    Motor rightWheel;
    GyroSensor gyrosensor;
    EdgeExchangeClass edgeexchange;
    ConstantTracerClass constanttracer;
    DirectionClass direction;
    
    //---------------------------------
    //変数宣言
    //---------------------------------
    int edge;
    int firstEdge;
    float Direction;
    bool flag;
};
#endif