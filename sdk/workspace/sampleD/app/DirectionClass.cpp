#include "DirectionClass.h"

void DirectionClass::Direction_init()
{
    direction=0.0;
}

void DirectionClass::Direction_update(float leftdistance,float rightdistance)
{
    //(360 / (2 * 円周率 * 車体トレッド幅)) * (右進行距離-左進行距離)
    direction += (360.0 / (2.0 * 3.14 * 125)) * (leftdistance - rightdistance);
}

float DirectionClass::Get_direction()
{
    return direction;
}
