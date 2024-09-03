#include "app.h" 
#include "SceneClass.h" 
#include "ConstantTracerClass.h"
#include "DebrisScene.h"
#include "DistanceClass.h" 
#include "DirectionClass.h"

#include "Tracer.h"
#include "Debris.h" 
#include "Clock.h"  
using namespace ev3api;

//---------------------------------
//インスタンス
//---------------------------------
Tracer tracer;
Debris debris;
DistanceClass distance;
DirectionClass direction;
SceneClass scene; 
DebrisScene debrisscene; 
Clock clock;    
ConstantTracerClass constant;

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

  printf("Distance: %f, Left: %f, Right: %f\n", getdistance, leftdistance, rightdistance);

  //---------------------------------
  //シーン判断クラスを呼ぶ
  //---------------------------------
  scene.scene_decide(getdistance,leftdistance,rightdistance); 

  if(12430 < getdistance){

    stp_cyc(TRACER_CYC);
    printf("周期ハンドラ停止\n");
    constant.constant_run(true,true);
    printf("モーター停止\n");

    // デブリの周期ハンドラを起動
    sta_cyc(DEBRIS_CYC);
    printf("デブリの周期ハンドラ起動\n");  
  } 

  printf("Tracer Task End\n");
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
  float leftdistance;
  float rightdistance;
//距離をとる場所をメインのところではなく、デブリタスク内で行い、周期ハンドラを終わらせるのをデブリタスク内で終わらせる。

  //---------------------------------
  //距離取得
  //---------------------------------
  getdistance=distance.Distance_calculate();
  leftdistance=distance.Get_distance_left();
  rightdistance=distance.Get_distance_right();

  //---------------------------------
  //シーン判断クラスを呼ぶ
  //シーンクラスのデブリで新たに作った関数を呼ぶ
  //---------------------------------
  debrisscene.scene_debris(getdistance,leftdistance,rightdistance); 
  printf("Debris Task End\n");  
  ext_tsk();
}

//---------------------------------
//メインタスク
//---------------------------------
void main_task(intptr_t unused) { 
  const uint32_t duration = 4*1000; 
  float getdistance;
  float leftdistance;
  float rightdistance;

  getdistance=distance.Distance_calculate();
  leftdistance=distance.Get_distance_left();
  rightdistance=distance.Get_distance_right();

  tracer.init();
  debris.init();
  sta_cyc(TRACER_CYC);
  //printf("トレーサー託す");
  //tracer.terminate(); 
  //sta_cyc(DEBRIS_CYC); 
  //stp_cyc(DEBRIS_CYC); 

  //ext_tsk(); 
}

