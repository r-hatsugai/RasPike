#ifndef SCENEBLUE_H
#define SCENEBLUE_H

#include <stdio.h>
#include "app.h"
#include "rgbtohsv.h"
#include "LineTracer.h"


//-----------------------------------
//定義
//-----------------------------------
#define DELTA_T 0.001
#define KP 0.125
#define KI 0.1
#define KD 0.0075
#define PID_MAX 40
#define PID_MIN -40
typedef int S32;
typedef unsigned short U16;

//-----------------------------------
//プロトタイプ宣言
//-----------------------------------
S32 SceneBlue_pid(S32 diff_brightness,int edge, HSV out);

#endif