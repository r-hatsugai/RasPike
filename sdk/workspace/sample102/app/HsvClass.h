#ifndef HSVCLASS_H
#define HSVCLASS_H

#include "app.h"
//----------------------------------
//構造体宣言
//----------------------------------
typedef struct{
    double H;
    double S;
    double V;
}HSV;


class HsvClass
{
public:
    
    //----------------------------------
    //関数宣言
    //----------------------------------
    HSV hsv_calculate(rgb_raw_t rgb_val);

    //----------------------------------
    //変数宣言
    //----------------------------------
    double R,G,B;
    double MAX;
    double MIN;

    //----------------------------------
    //構造体変数
    //----------------------------------
    HSV out;

};
#endif