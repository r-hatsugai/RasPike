#ifndef DEBRISSCENE_H
#define DEBRISSCENE_H

#include "SonarSensor.h"
#include "ColorSensor.h"
#include "Debris.h"
#include "EdgeExchangeClass.h"
#include "ConstantTracerClass.h"
#include "HsvClass.h"
#include "DirectionClass.h"
#include <stdbool.h>

using namespace ev3api;

class DebrisScene
{
public:
    //---------------------------------
    //関数定義
    //---------------------------------
    DebrisScene();

    //デブリ用の新たな関数（app.cppに呼ばれる）
    void scene_debris(float distance,float leftdistance,float rightdistance);

    //---------------------------------
    //インスタンス
    //---------------------------------
    Debris debris;
    ColorSensor colorSensor;
    EdgeExchangeClass edgeexchange;
    ConstantTracerClass constanttracer;
    HsvClass hsv;
    DirectionClass direction;


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