#ifndef RUN_H
#define RUN_H

#include <stdio.h>
#include "app.h"
#include "rgbtohsv.h"
#include "LineTracer.h"


//-----------------------------------
//定義
//-----------------------------------

typedef int S32;
typedef unsigned short U16;

//-----------------------------------
//プロトタイプ宣言
//-----------------------------------
S32 run_pid(S32 diff_brightness,int edge, HSV out);

#endif