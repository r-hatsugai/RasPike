#include "app.h" 
#include "SceneClass.h" 
#include "DistanceClass.h" 
#include "DirectionClass.h"

#include "Tracer.h" 
#include "Clock.h"  
using namespace ev3api;

//---------------------------------
//インスタンス
//---------------------------------
Tracer tracer;
DistanceClass distance;
DirectionClass direction;
SceneClass scene;  
Clock clock;    

//---------------------------------
//トレーサータスク
//---------------------------------
void tracer_task(intptr_t exinf) {
  //---------------------------------
  //距離を格納する変数の宣言
  //---------------------------------
  float getdistance;
  float leftdistance;
  float rightdistance;
  //---------------------------------
  //距離取得
  //---------------------------------
  getdistance=distance.Distance_calculate();
  leftdistance=distance.Get_distance_left();
  rightdistance=distance.Get_distance_right();

  //---------------------------------
  //シーン判断クラスを呼ぶ
  //---------------------------------
  scene.scene_decide(getdistance,leftdistance,rightdistance); 
  
  ext_tsk();
}

//---------------------------------
//メインタスク
//---------------------------------
void main_task(intptr_t unused) { 
  const uint32_t duration = 4*1000; 

  tracer.init(); 
  sta_cyc(TRACER_CYC); 
  
  while (!ev3_button_is_pressed(LEFT_BUTTON)) {
      clock.sleep(duration);   
  }

  stp_cyc(TRACER_CYC); 
  tracer.terminate(); 
  ext_tsk(); 
}

