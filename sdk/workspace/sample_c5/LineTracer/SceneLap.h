#ifndef SCENELAP_H
#define SCENELAP_H

#include <stdio.h>
#include "app.h"
#include "rgbtohsv.h"
#include "LineTracer.h"


//-----------------------------------
//定義
//-----------------------------------
#define DELTA_T 0.004
#define KP 0.0955
#define KI 0.053
#define KD 0.00525
#define PID_MAX 40
#define PID_MIN -40
typedef int S32;
typedef unsigned short U16;

//-----------------------------------
//プロトタイプ宣言
//-----------------------------------
S32 SceneLap_pid(S32 diff_brightness,int edge, HSV out);

#endif