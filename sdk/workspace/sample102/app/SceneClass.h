#ifndef SCENECLASS_H
#define SCENECLASS_H

#include "SonarSensor.h"
#include "ColorSensor.h"
#include "Tracer.h"
#include "EdgeExchangeClass.h"
#include "ConstantTracerClass.h"
#include "HsvClass.h"
#include "DirectionClass.h"
#include <stdbool.h>

using namespace ev3api;

class SceneClass
{
public:
    //---------------------------------
    //関数定義
    //---------------------------------
    SceneClass();
    void scene_decide(float distance);

    //---------------------------------
    //インスタンス
    //---------------------------------
    Tracer tracer;
    ColorSensor colorSensor;
    EdgeExchangeClass edgeexchange;
    ConstantTracerClass constanttracer;
    HsvClass hsv;
    //---------------------------------
    //変数宣言
    //---------------------------------
    int edge;
    float Direction;
    bool flag;
    rgb_raw_t rgb_val;
    HSV out;
};
#endif