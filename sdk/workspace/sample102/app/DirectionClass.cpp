#include "DirectionClass.h"

float Direction;

void DirectionClass::Direction_init()
{
    Direction=0.0;
}

void DirectionClass::Direction_update(float leftdistance,float rightdistance)
{
    //(360 / (2 * 円周率 * 車体トレッド幅)) * (右進行距離-左進行距離)
    Direction += (360.0 / (2.0 * 3.14 * 125)) * (leftdistance - rightdistance);
    // printf("Direction%f\n",Direction);
}

void DirectionClass::Direction_setdirection(float set_dir)
{
    Direction = set_dir;
}

float DirectionClass::Get_direction()
{
    return Direction;
}


