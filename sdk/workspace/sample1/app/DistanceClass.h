#ifndef DISTANCECLASS_H
#define DISTANCECLASS_H
#include "Motor.h"

using namespace ev3api;

class DistanceClass
{
public:
    //----------------------------
    //定義
    //----------------------------
    #define PI 3.14159265358
    #define TIRE_DIAMETER 100.0  //タイヤ直径（81mm）
    
    //----------------------------
    //関数宣言
    //----------------------------
    DistanceClass();
    int Distance_reset();
    float Distance_calculate(void);
    float Get_distance_left(void);
    float Get_distance_right(void);
    
    //----------------------------
    //変数宣言
    //----------------------------
    float distance;     //走行距離
    float distance4msL; //左タイヤの4ms間の距離
    float distance4msR; //右タイヤの4ms間の距離
    float pre_angleL, pre_angleR; // 左右モータ回転角度の過去値

    //----------------------------
    //インスタンス
    //----------------------------
    Motor leftWheel;
    Motor rightWheel;
};
#endif