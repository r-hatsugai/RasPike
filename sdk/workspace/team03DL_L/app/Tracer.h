#ifndef TRACER_H
#define TRACER_H

#include "Motor.h"
#include "util.h"
#include "SonarSensor.h"
#include "PidClass.h"

using namespace ev3api;

class Tracer {
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
  int g_angle;
  int left_motor_power;
  int right_motor_power; /*左右モータ設定パワー*/
};
#endif

