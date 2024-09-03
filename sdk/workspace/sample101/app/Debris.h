#ifndef DEBRIS_H
#define DEBRIS_H

#include "Motor.h"       // <1>
#include "ColorSensor.h" // <2>
#include "util.h"        // <3>
#include "SonarSensor.h"
#include "PidClass.h"
#include "HsvClass.h"

using namespace ev3api;// <4>

class Debris {  // <1>
public:
  //---------------------------------
  //関数定義
  //---------------------------------
  Debris();
  void run(float KP, float KI ,float KD,int BASE_SPEED, int edge);       // <2>
  void init();
  void terminate();

  //----------------------------
  //インスタンス
  //----------------------------
  Motor leftWheel;
  Motor rightWheel;
  SonarSensor sonarSensor;
  ColorSensor colorSensor; // <3>
  PidClass pid;
  HsvClass hsv;
  
  //----------------------------
  //変数
  //----------------------------
  typedef int S32;
  typedef unsigned short U16;
  int pid_val;
  int BASE_SPEED;
  int LEFT_EDGE;
  int RIGHT_EDGE;
  int g_angle;
  // double *hsv_get;
  //float getdistance;
  S32 left_motor_power;
  S32 right_motor_power; /*左右モータ設定パワー int*/

  //----------------------------
  //構造体変数
  //----------------------------
  rgb_raw_t rgb_val;
  HSV out;
  
};
#endif

