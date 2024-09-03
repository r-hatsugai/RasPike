#include "SceneClass.h"

SceneClass::SceneClass():
    colorSensor(PORT_2){
    }


void SceneClass::scene_decide(float distance,float leftdistance,float rightdistance ){
    //---------------------------------
    //エッジ判断
    //---------------------------------
    edge=edgeexchange.edge_exchange();

    firstEdge=edgeexchange.edge_past();


    nt = clock.now();
    seconds = (nt / 100000) % 1000;

    printf("現在時刻 %d\n", seconds);

    //---------------------------------
    //hsv値取得
    //---------------------------------
    colorSensor.getRawColor(rgb_val);
    out=hsv.hsv_calculate(rgb_val);

    //---------------------------------
    //シーン判断
    //---------------------------------
    //-------------------------------------
    //tracer.run関数の引数(KP,KI,KD,BASE SPEED,エッジ)
    //-------------------------------------
    /* スタート → 第一コーナー */
    
    if(seconds <= 8)
    {
        constanttracer.constant_run(30,60);
    }
    else if(8 < seconds && seconds <= 16)
    {
        constanttracer.constant_run(-27,-52);
    }
    else if(16 < seconds && seconds <= 200)
    {
        constanttracer.constant_run(0,0);
    }
    
}