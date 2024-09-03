#include "app.h"
#include "LineTracer.h"
#include "EdgeExchange.h"
#include "SceneStraight.h"
#include "SceneCorner.h"
#include "SceneLap.h"
#include "SceneExit.h"
#include "SceneBlue.h"
#include "rgbtohsv.h"
#include "distance.h"
#include "run.h"
#include "Scene1.h"
#include "Scene2.h"
#include "Scene3.h"
#include "Scene4.h"
#include "Scene5.h"
#include "Scene6.h"
#include "Scene7.h"
#include <stdio.h>

//-------------------------------------------------------------------------------------
//変数宣言
//-------------------------------------------------------------------------------------
typedef int S32;
typedef unsigned short U16;
//int edge;
int edgePast = -1; /* 過去のエッジ */
float distance = 0; /* 距離 */

//-------------------------------------------------------------------------------------
//構造体変数宣言
//-------------------------------------------------------------------------------------
rgb_raw_t rgb_val;/* カラーセンサ取得値 */
HSV out;

//-------------------------------------------------------------------------------------
//初期化関数
//-------------------------------------------------------------------------------------
first_Distance();

//-------------------------------------------------------------------------------------
//ライントレースタスク(4msec周期で関数コールされる)
//-------------------------------------------------------------------------------------
void tracer_task(intptr_t unused) {
    //-------------------------------------------------------------------------------------
    //変数宣言
    //-------------------------------------------------------------------------------------
    //S32 steering_amount; /* ステアリング操舵量の計算 */
    S32 diff_brightness; /* 目標輝度値とカラーセンサ値の差分 */
    S32 target_brightness; /* 目標輝度値 uint16_t */  
    
    //-------------------------------------------------------------------------------------
    //目標輝度計算
    //-------------------------------------------------------------------------------------
    target_brightness = (WHITE_BRIGHTNESS - BLACK_BRIGHTNESS) / 2;

    //-------------------------------------------------------------------------------------
    //カラーセンサ値取得
    //-------------------------------------------------------------------------------------
    ev3_color_sensor_get_rgb_raw(color_sensor, &rgb_val);

    //-------------------------------------------------------------------------------------
    //RGBtoHSV
    //-------------------------------------------------------------------------------------
    out = rgbtohsv(rgb_val);
    //printf("h %f\n",out.H);
 
    //-------------------------------------------------------------------------------------
    //目標輝度値とカラーセンサ値の差分を計算
    //-------------------------------------------------------------------------------------
    diff_brightness = (float32_t)(target_brightness - rgb_val.g);

    //-------------------------------------------------------------------------------------
    //走行距離計算
    //-------------------------------------------------------------------------------------
    distance=Distance();
    printf("距離 %f\n", distance);

    //-------------------------------------------------------------------------------------
    //エッジ切り替え
    //-------------------------------------------------------------------------------------
    int edge = EdgeExchange(out, distance);

    printf("out.H %f\n", out.H);
    printf("out.S %f\n", out.S);
    printf("out.V %f\n", out.V);

    //-------------------------------------------------------------------------------------
    //シーン切り替え(青線半分まで)
    //-------------------------------------------------------------------------------------
    /*スタート地点からコーナー1までのストレート (GATEピンク枠START側のところまで)*/
    
    /*if(distance<2780)
    {
        SceneStraight_pid(diff_brightness, edge, out);
    }
    */
    /* コーナー1 */
    /*
    else if(2780 < distance && distance < 3300)
    {
        SceneCorner_pid(diff_brightness, edge, out);
    }
    */
    /* コーナー1からコーナー2までのストレート */
    /*
    else if(3300 < distance && distance < 4900)
    {
        SceneStraight_pid(diff_brightness, edge, out);
    }
    */
    /* コーナー2 */
    /*
    else if(4900 < distance && distance < 5400)
    {
        SceneCorner_pid(diff_brightness, edge, out);
    }
    */
    /* コーナー2から青線半分までのストレート */
    /*
    else if(5400 < distance && distance < 6130)
    {
        SceneLap_pid(diff_brightness, edge, out);
    }
    */
    /*
    if(distance < 550)
    {
        SceneLap_pid(diff_brightness, edge, out);
    }
    */
    //-------------------------------------------------------------------------------------
    //シーン切り替え（円1の青線まで）
    //-------------------------------------------------------------------------------------

    /* 青線半分から円1の右側ラインまで(エッジ切り替え) */
    /*
    else if(550 < distance && distance < 770)
    {
        //if(35 <= out.S && 25 <= out.V)
        Scene1_pid(diff_brightness, edge, out);
    }
    */
    /* 円1の右側ラインから円1の青線まで8220 */ 
    /*
    if(distance < 740)
    {
        Scene6_pid(diff_brightness, edge, out);
    }
    else if(740 < distance && distance < 2900)
    {
        Scene7_pid(diff_brightness, edge, out);
    }
    */
    
    /* 青線半分から円1の右側ラインまで(エッジ切り替え) 550-770 */
    /*
    else if(6130 < distance && distance < 6350)
    {
        //if(35 <= out.S && 25 <= out.V)750
        Scene1_pid(diff_brightness, edge, out);
    }
    */
    /* Scene2 770-2460 */ 
    //                                   2550
    /*
    else if(6350 < distance && distance < 8060)
    {
        Scene2_pid(diff_brightness, edge, out);
    }
    */
    //-------------------------------------------------------------------------------------
    //シーン切り替え（ダブルループ出口まで）
    //-------------------------------------------------------------------------------------

    /*青線の直進*/
    /*
    else if(8250 < distance && distance < 8290)
    {
        Scene3_pid(diff_brightness, edge, out);
    }
    */

    /* 円1の青線からダブルループ出口まで */
    /*
    else if(8290 < distance && distance < 9900)
    {
        Scene2_pid(diff_brightness, edge, out);
    }
    */
    /*Scene3 2460-2580*/
    /*
    else if(8060 < distance && distance < 8190)
    {
        Scene3_pid(diff_brightness, edge, out);
    }
    */
    /*Scene4 2580-5080*/
    //2590
    /*
    else if(8190 < distance && distance < 10650)
    {
        Scene4_pid(diff_brightness, edge, out);
    }
    */
    //--------------------------------
    // 変更予定
    //--------------------------------

    /*Scene5 5080-5200*/
    /*
    else if(10650 < distance && distance < 10800)
    {
        Scene5_pid(diff_brightness, edge, out);
    }
    */

    //-------------------------------
    // シーン６
    //-------------------------------

    /*Scene6 5200-5940*/
    /*
    else if(10800 < distance && distance < 11540)
    {
        Scene6_pid(diff_brightness, edge, out);
    }
    */
    //-------------------------------
    // シーン７
    //-------------------------------
    /*Scene7 5940-6158*/
    /*
    else if(11540 < distance && distance < 11758)
    {
        Scene7_pid(diff_brightness, edge, out);
    }
    */
    /*SceneExit 6158-8000*/
    /*
    else if(11758 < distance && distance < 12130)
    {
        SceneExit_pid(diff_brightness, edge, out);
    }
    */
    /*run*/
    /*
    else if(12130 < distance && distance < 20000)
    {
        run_pid(diff_brightness, edge, out);
    }
    */

    /* 過去のエッジに現在のエッジを代入 */
    edgePast = edge;

    //sleep(10000);

    //-------------------------------------------------------------------------------------
    //タスク終了
    //-------------------------------------------------------------------------------------
    ext_tsk();
}


