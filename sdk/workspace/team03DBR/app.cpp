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



bool d_flag;
bool d_1_flag;
//---------------------------------
//トレーサータスク
//---------------------------------
void tracer_task(intptr_t exinf) {
  //---------------------------------
  //変数
  //---------------------------------
  float getdistance;
  //---------------------------------
  //距離取得
  //---------------------------------
  getdistance=distance.Distance_calculate();
  
  //---------------------------------
  //シーン判断クラスを呼ぶ
  //---------------------------------
  //debris.debris_removal(leftdistance,rightdistance);
  scene.scene_decide(getdistance); 

  if(0 < getdistance){//12430

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
  float distance;
  float leftdistance;
  float rightdistance;
  
  //---------------------------------
  //距離取得
  //---------------------------------
  
  distance = d_distance.Distance_calculate();
  leftdistance = d_distance.Get_distance_left();
  rightdistance = d_distance.Get_distance_right();

  //---------------------------------
  //デブリ(直進→旋回)
  //---------------------------------
  /*
  d_flag = debris.debris_removal(distance, leftdistance, rightdistance);

  if(d_flag){
    d_distance.Distance_reset();
    distance = d_distance.Distance_calculate();
    leftdistance = d_distance.Get_distance_left();
    rightdistance = d_distance.Get_distance_right();
    d_1_flag = debris.debris_short(distance, leftdistance, rightdistance);
  }
  */
  //d_flag = debris.debris_removal(distance, leftdistance, rightdistance);
  debris.debris_action(distance, leftdistance, rightdistance);

  
  //printf("flag%d\n", d_flag);
  
  ext_tsk();
}

void smartcarry_task(intptr_t exinf)
{
  
}
//---------------------------------
//メインタスク
//---------------------------------
void main_task(intptr_t unused) { 
  const uint32_t duration = 10*1000; 

  tracer.init();
  debris.init();
  sta_cyc(TRACER_CYC);
}

