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



bool d_flag = true;
bool d_1_flag = true;
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
  getdistance=distance.Distance_calculate();
  
  //---------------------------------
  //シーン判断クラスを呼ぶ
  //---------------------------------
  //debris.debris_removal(leftdistance,rightdistance);
  scene.scene_decide(getdistance); 

  if(20000 < getdistance){//12430
    stp_cyc(TRACER_CYC);
    constant.constant_run(true,true);
    distance.Distance_reset();
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
  distance=d_distance.Distance_calculate();
  leftdistance = d_distance.Get_distance_left();
  rightdistance = d_distance.Get_distance_right();
  
  //---------------------------------
  //デブリ
  //---------------------------------
  if(d_flag)
  {
    d_flag = debris.debris_action(distance, leftdistance, rightdistance);
  }
  else
  {
    stp_cyc(DEBRIS_CYC);
    constant.constant_run(true,true);
    d_distance.Distance_reset();
    smartcarry.init();
    printf("スマートキャリーサイクル起動\n");
    sta_cyc(SMARTCARRY_CYC);
  } 
  ext_tsk();
}

void smartcarry_task(intptr_t exinf)
{
  float distance;
  float left_distance;
  float right_distance;


  distance= s_distance.Distance_calculate();
  left_distance = s_distance.Get_distance_left();
  right_distance = s_distance.Get_distance_right();
  printf("distance%f\n", distance);

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
        printf("スマートキャリー起動\n");
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
        printf("バック\n");
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
    printf("ゴール\n");
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

