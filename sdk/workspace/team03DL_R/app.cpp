#include "app.h" 
#include "SceneClass.h" 
#include "DistanceClass.h" 
#include "DirectionClass.h"
#include "Debris.h"
#include "Tracer.h" 
#include "Clock.h"  
#include "ConstantTracerClass.h"
#include "Smartcarry.h"
#include <stdbool.h>
using namespace ev3api;

//---------------------------------
//インスタンス
//---------------------------------
Tracer tracer;
DistanceClass distance;
DistanceClass d_distance;
DistanceClass s_distance;
DirectionClass direction;
SceneClass scene;  
ConstantTracerClass constant;
Debris debris;
Smartcarry smartcarry;
Clock clock;    

//---------------------------------
//トレーサータスク
//---------------------------------
void tracer_task(intptr_t exinf) {
  //---------------------------------
  //変数
  //---------------------------------
  float getdistance;
  bool t_flag;
  //---------------------------------
  //距離取得
  //---------------------------------
  getdistance=distance.Distance_calculate();
  
  //---------------------------------
  //シーン判断クラスを呼ぶ
  //---------------------------------
  //debris.debris_removal(leftdistance,rightdistance);
  t_flag = scene.scene_decide(getdistance); 

  //t_flag = true;
  if(t_flag == true){//12430

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
  float distance_de;
  float leftdistance;
  float rightdistance;
  bool d_flag;
  //---------------------------------
  //距離取得
  //---------------------------------
  distance_de = d_distance.Distance_calculate();
  leftdistance = d_distance.Get_distance_left();
  rightdistance = d_distance.Get_distance_right();

  //---------------------------------
  //デブリ
  //---------------------------------
  debris.debris_action(distance_de, leftdistance, rightdistance);
  
  if(d_flag == true){//12430

    stp_cyc(DEBRIS_CYC);
    constant.constant_run(true,true);
    distance.Distance_reset();

    // スマキャリの周期ハンドラを起動
    sta_cyc(SMARTCARRY_CYC);
    printf("smartcarryの周期ハンドラ起動\n");  
  } 
  ext_tsk();
}

void smartcarry_task(intptr_t exinf)
{
  float Leftdistance;
  float Rightdistance;

  s_distance.Distance_calculate();
  Leftdistance=s_distance.Get_distance_left();
  Rightdistance=s_distance.Get_distance_right();

  smartcarry.Smart_carry(Leftdistance, Rightdistance);
  
  ext_tsk();
}

//---------------------------------
//メインタスク
//---------------------------------
void main_task(intptr_t unused) { 
  const uint32_t duration = 10*1000; 

  tracer.init();
  debris.init();
  smartcarry.init();
  sta_cyc(TRACER_CYC);
}

