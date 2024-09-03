#ifndef TRACER_H
#define TRACER_H

#include "Motor.h"       // <1>
#include "ColorSensor.h" // <2>
#include "util.h"        // <3>
#include "SonarSensor.h"
#include "PidClass.h"

using namespace ev3api;// <4>

class Tracer {  // <1>
public:
  //---------------------------------
  //関数定義
  //---------------------------------
  Tracer();
  void run(float KP, float KI ,float KD,int BASE_SPEED, int edge);       // <2>
  void init();
  void terminate();

  //----------------------------
  //インスタンス
  //----------------------------
  Motor leftWheel;
  Motor rightWheel;
  SonarSensor sonarSensor;
  PidClass pid;
  
  //----------------------------
  //変数
  //----------------------------
  float pid_val;
  int BASE_SPEED;
  int g_angle;
  int left_motor_power;
  int right_motor_power; /*左右モータ設定パワー int*/
};
#endif

