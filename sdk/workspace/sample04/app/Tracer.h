#include "Motor.h"       // <1>
#include "ColorSensor.h" // <2>
#include "util.h"        // <3>
#include "SonarSensor.h"

using namespace ev3api;  // <4>
/* ステアリング操舵量の係数 */
//#define STEERING_COEF     (0.2F)
 
/* 走行基準スピード */
#define BASE_SPEED        (80) //74
/* ライントレースエッジ切り替え */
#define LEFT_EDGE         (-1) 
#define RIGHT_EDGE        (1)

typedef int S32;
typedef unsigned short U16;

class Tracer {  // <1>
public:
  Tracer();
  void run();       // <2>
  void init();
  void terminate();

protected:
  //----------------------------
  //インスタンス
  //----------------------------
  Motor leftWheel;
  Motor rightWheel;
  ColorSensor colorSensor; // <3>
  SonarSensor sonarSensor;
  
  //----------------------------
  //変数int
  //----------------------------
  int distance;
  int count = 0; 
  //----------------------------
  //変数float
  //----------------------------
  float DELTA_T;
  float KP;
  float KI;
  float KD;
  float PID_MAX;
  float PID_MIN;
  //----------------------------
  //変数S32
  //----------------------------
  float diff[2];
  float integral;
  S32 diff_brightness; /* 目標輝度値とカラーセンサ値の差分 */
  S32 target_brightness; /* 目標輝度値 uint16_t */  
  S32 steering_amount;/* ステアリング操舵量 int16_t */
  float pid;
  float p, i, d; 
  S32 left_motor_power;
  S32 right_motor_power; /*左右モータ設定パワー int*/

#ifndef MAKE_RASPIKE
  const int8_t pwm = (Motor::PWM_MAX) / 6;
#else
  const int8_t pwm = 60;
#endif
};
