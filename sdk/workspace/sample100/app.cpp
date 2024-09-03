#include "app.h" 
#include "SceneClass.h" 
#include "DistanceClass.h" 

#include "Tracer.h" 
#include "Clock.h"  
using namespace ev3api;

//---------------------------------
//インスタンス
//---------------------------------
Tracer tracer;
DistanceClass distance;
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

  //---------------------------------
  //距離取得
  //---------------------------------
  getdistance=distance.Distance_calculate();

  //---------------------------------
  //シーン判断クラスを呼ぶ
  //---------------------------------
  scene.scene_decide(getdistance); 
  
  ext_tsk();
}

//---------------------------------
//デブリタスク
//---------------------------------
void debris_task(intptr_t exinf) {
  //---------------------------------
  //距離を格納する変数の宣言
  //---------------------------------
  float getdistance;

  //---------------------------------
  //距離取得
  //---------------------------------
  getdistance=distance.Distance_calculate();

  //---------------------------------
  //シーン判断クラスを呼ぶ
  //---------------------------------
  scene.scene_decide(getdistance); 
  
  ext_tsk();
}

//---------------------------------
//メインタスク
//---------------------------------
void main_task(intptr_t unused) { 
  const uint32_t duration = 4*1000; 

  tracer.init();

  sta_cyc(TRACER_CYC); 
  stp_cyc(TRACER_CYC); 
  tracer.terminate(); 
  sta_cyc(DEBRIS_CYC); 
  stp_cyc(DEBRIS_CYC); 

  ext_tsk(); 
}

