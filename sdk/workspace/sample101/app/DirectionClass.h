#ifndef DIRECTIONCLASS_H
#define DIRECTIONCLASS_H

#include "DistanceClass.h"

class DirectionClass
{
    public:
    void Direction_init();//初期化関数
    void Direction_update(float leftdistance, float rightdistance);//方位取得
    float Get_direction();

    DistanceClass distance;
    float direction;
};
#endif