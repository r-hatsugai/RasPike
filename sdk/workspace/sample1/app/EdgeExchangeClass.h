#ifndef EDGEEXCHANGECLASS_H
#define EDGEEXCHANGECLASS_H

#include "ColorSensor.h"
#include "HsvClass.h"

using namespace ev3api;

class EdgeExchangeClass
{
public:
    //----------------------------
    //関数宣言
    //----------------------------
    EdgeExchangeClass();
    int edge_exchange();
    int edge_past();

    //----------------------------
    //変数宣言
    //----------------------------
    int flg = 0;
    int edge= -1;
    int firstEdge = edge;

    //----------------------------
    //インスタンス
    //----------------------------
    ColorSensor colorSensor;
    HsvClass hsv;

    //----------------------------
    //構造体変数
    //----------------------------
    HSV out;
    rgb_raw_t rgb_val;
};
#endif