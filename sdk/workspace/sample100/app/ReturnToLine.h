#ifndef RETURNTOLINECLASS_H
#define RETURNTOLINECLASS_H

#include "ColorSensor.h"
#include "HsvClass.h"

using namespace ev3api;

class ReturnToLineClass
{
public:
    //----------------------------
    //関数宣言
    //----------------------------
    ReturnToLineClass();
    int return_to_line();

    //----------------------------
    //変数宣言
    //----------------------------
    int flg = 0;
    //int edge= -1;

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