#include "app.h" 
#include "SceneClass.h" 
#include "DistanceClass.h" 
#include "DirectionClass.h"
#include "Debris.h"
#include "Tracer.h" 
#include "Clock.h"  
#include "ConstantTracerClass.h"
using namespace ev3api;

//---------------------------------
//インスタンス
//---------------------------------
Tracer tracer;
DistanceClass distance;
DistanceClass d_distance;
DirectionClass direction;
SceneClass scene;  
ConstantTracerClass constant;
Debris debris;
Clock clock;    

//---------------------------------
//トレーサータスク
//---------------------------------
void tracer_task(intptr_t exinf) {
  //---------------------------------
  //変数
  //---------------------------------
  float getdistance;
  float leftdistance;
  float rightdistance;
  //---------------------------------
  //距離取得
  //---------------------------------
  getdistance=distance.Distance_calculate();
  leftdistance=d_distance.Get_distance_left();
  rightdistance=d_distance.Get_distance_right();

  
  //---------------------------------
  //シーン判断クラスを呼ぶ
  //---------------------------------
  //debris.debris_removal(leftdistance,rightdistance);
  scene.scene_decide(getdistance,leftdistance,rightdistance); 

  if(12340 < getdistance){//12430

    stp_cyc(TRACER_CYC);
    constant.constant_run(true,true);
    distance.Distance_reset();

    // デブリの周期ハンドラを起動
    sta_cyc(DEBRIS_CYC);
    printf("デブリの周期ハンドラ起動\n");  
  } 
  ext_tsk();
}

//---------------------------------
//デブリタスク
//---------------------------------
void debris_task(intptr_t exinf) {
  //---------------------------------
  //変数
  //---------------------------------
  float leftdistance;
  float rightdistance;

  //---------------------------------
  //距離取得
  //---------------------------------
  d_distance.Distance_calculate();
  leftdistance=d_distance.Get_distance_left();
  rightdistance=d_distance.Get_distance_right();

  //---------------------------------
  //デブリ
  //---------------------------------
  debris.debris_removal(leftdistance,rightdistance);
  
  ext_tsk();
}

//---------------------------------
//メインタスク
//---------------------------------
void main_task(intptr_t unused) { 
  const uint32_t duration = 4*1000; 

  tracer.init();
  debris.init();
  sta_cyc(TRACER_CYC);
}

