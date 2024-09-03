#ifndef COORDINATECLASS_H
#define COORDINATECLASS_H
#include "math.h"


class CoordinateClass
{
    public:
    #define PI 3.14159265358
    //-----------------------------------
    //関数
    //-----------------------------------
    void Grid_init();/*初期化関数*/
    void Grid_setdistance(int aX, int aY, int bX, int bY);/*座標aから座標bまでの移動距離を設定する関数*/
    float Grid_getdistance();/*座標aから座標bまでの移動距離を取得する関数*/
    void Grid_setdirection(int aX, int aY, int bX, int bY);/*目標座標の方位を設定する関数*/
    float Grid_getdirection();
};
#endif