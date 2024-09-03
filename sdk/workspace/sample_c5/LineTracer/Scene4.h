#ifndef SCENE4_H
#define SCENE4_H

#include <stdio.h>
#include "app.h"
#include "rgbtohsv.h"
#include "LineTracer.h"


//-----------------------------------
//定義
//-----------------------------------
#define DELTA_T 0.001
#define KP 0.3
#define KI 0.26
#define KD 0.015
#define PID_MAX 40
#define PID_MIN -40
typedef int S32;
typedef unsigned short U16;

//-----------------------------------
//プロトタイプ宣言
//-----------------------------------
S32 Scene4_pid(S32 diff_brightness,int edge, HSV out);

#endif