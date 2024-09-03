#include "Motor.h"       // <1>
#include "ColorSensor.h" // <2>
#include "util.h"        // <3>

using namespace ev3api;  // <4>

/* 走行基準スピード */
#define BASE_SPEED        (60)
/* ライントレースエッジ切り替え */
#define LEFT_EDGE         (-1) 
#define RIGHT_EDGE        (1)
