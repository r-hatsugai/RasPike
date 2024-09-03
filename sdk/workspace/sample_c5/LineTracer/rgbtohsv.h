#ifndef RGBTOHSV_H
#define RGBTOHSV_H
//------------------------------------
#include <stdio.h>
#include "app.h"
 
typedef struct {
    double H;
    double S;
    double V;
}HSV;
//------------------------------------
//プロトタイプ宣言
//------------------------------------
HSV rgbtohsv(rgb_raw_t rgb_val);
 
#endif