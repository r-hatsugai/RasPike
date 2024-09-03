#ifndef SCENECLASS_H
#define SCENECLASS_H

#include "SonarSensor.h"
#include "Tracer.h"
#include "EdgeExchangeClass.h"
#include "ConstantTracerClass.h"

using namespace ev3api;

class SceneClass
{
public:
    //---------------------------------
    //関数定義
    //---------------------------------
    void scene_decide(float distance);

    //---------------------------------
    //インスタンス
    //---------------------------------
    Tracer tracer;
    EdgeExchangeClass edgeexchange;
    ConstantTracerClass constanttracer;

    //---------------------------------
    //変数宣言
    //---------------------------------
    int edge;
    rgb_raw_t rgb_val;
};
#endif