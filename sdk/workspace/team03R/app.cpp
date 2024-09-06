#include "app.h" 
#include "SceneClass.h" 
#include "DistanceClass.h" 
#include "DirectionClass.h"
#include "Debris.h"
#include "Tracer.h" 
#include "Clock.h"  
#include "ConstantTracerClass.h"
#include "Smartcarry.h"
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


//bool flag = true;


bool debris_flag = true;
bool trace_flag = true;
// bool trace_flag = false;
// bool debris_flag = false;
bool s_flag = true;
bool s_flag_1 = true;
bool s_flag_2 = true;
bool s_flag_3 = true;
int num = 1;
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
  getdistance = distance.Distance_calculate();
  //---------------------------------
  //シーン判断クラスを呼ぶ
  //---------------------------------
  if(trace_flag)
  {
    trace_flag = scene.scene_decide(getdistance); 
  }
  else
  {
    stp_cyc(TRACER_CYC);
    constant.constant_run(true,true);
    d_distance.Distance_reset();
    // デブリの周期ハンドラを起動
    sta_cyc(DEBRIS_CYC);
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
  //デブリ
  //---------------------------------
  if(debris_flag)
  {
    debris_flag = debris.debris_action(distance, leftdistance, rightdistance);
  }
  else
  {
    stp_cyc(DEBRIS_CYC);
    constant.constant_run(true,true);
    d_distance.Distance_reset();
    // デブリの周期ハンドラを起動
    sta_cyc(SMARTCARRY_CYC);
  }
  ext_tsk();
}

void smartcarry_task(intptr_t exinf)
{
  float distance;
  float left_distance;
  float right_distance;


  distance = s_distance.Distance_calculate();
  left_distance = s_distance.Get_distance_left();
  right_distance = s_distance.Get_distance_right();

  if(s_flag_3)
  {
    if(s_flag_1)
    {
      if(s_flag)
      {
        //-------------------------------------------------------------
        //処理中はtrueを返し,設置したらfalseを返す
        //-------------------------------------------------------------
        s_flag = smartcarry.smart_carry(left_distance, right_distance);
      }
      else 
      {
        //-------------------------------------------------------------
        //距離を初期化し、s_flag_1をfalseにする
        //-------------------------------------------------------------
        s_distance.Distance_reset();
        s_flag_1 = false;
      }
    }
    else
    {
      if(s_flag_2)
      {
        //-------------------------------------------------------------
        //10cm固定値バック
        //-------------------------------------------------------------
        s_flag_2 = smartcarry.back_run(distance);
      }
      else 
      {
        //-------------------------------------------------------------
        //バックしたらs_flag_3にfalse入れる
        //-------------------------------------------------------------
        s_flag_3 = false;
        s_distance.Distance_reset();
        smartcarry.init();
      }
    }
  }
  else
  {
    //-------------------------------------------------------------
    //ゴール
    //-------------------------------------------------------------
    s_flag_3 = smartcarry.goal_run(left_distance, right_distance);
  }  

  ext_tsk();

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

