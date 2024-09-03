#include "CoordinateClass.h"

//-----------------------------------
//変数
//-----------------------------------
float grid_distance;/*現在座標から目標座標までの距離*/
float grid_direction;/*現在座標から目標座標の方位*/
float grid_size;/*マスの幅(250mm)*/


/*初期化関数*/
void CoordinateClass::Grid_init()
{
    grid_distance=0.0;
    grid_direction=0.0;
}

void CoordinateClass::Grid_setdistance(int aX, int aY, int bX, int bY)
{
    grid_size=250.0;
    grid_distance = sqrt( pow((float)(bX-aX),2) + pow((float)(bY-aY),2) ) * grid_size;
}

float Grid_getdistance()
{
    return grid_distance;
}

void Grid_setdirection(int aX, int aY, int bX, int bY)
{
    float targetdir = 0.0;/*目標方位*/

    targetdir=atan2((float)(bY-aY), (float)(bX-aX));
    targetdir=targetdir * 180.0 / 3.14;

    grid_direction = targetdir;
}

float Grid_getdirection()
{
    return grid_direction;
}