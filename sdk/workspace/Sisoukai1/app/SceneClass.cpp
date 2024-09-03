#include "SceneClass.h"

SceneClass::SceneClass():
    colorSensor(PORT_2){
    }


void SceneClass::scene_decide(float distance,float leftdistance,float rightdistance){
    //---------------------------------
    //エッジ判断
    //---------------------------------
    edge=edgeexchange.edge_exchange();

    firstEdge=edgeexchange.edge_past();

    //---------------------------------
    //hsv値取得
    //---------------------------------
    //colorSensor.getRawColor(rgb_val);
    //out=hsv.hsv_calculate(rgb_val);

    //printf("E out.H %f\n", out.H);
    //printf("E out.S %f\n", out.S);
    //printf("E out.V %f\n", out.V);

    //---------------------------------
    //シーン判断
    //---------------------------------
    //-------------------------------------
    //tracer.run関数の引数(KP,KI,KD,BASE SPEED,エッジ)
    //-------------------------------------
    
    
    /* スタート → 第一コーナー */
    if(distance <= 1100)
    {
        //tracer.run(0.08,0.0035,0.00116,68,edge);
        //tracer.run(0.097,0.04,0.0012,60,edge);
        tracer.run(0.097,0.051,0.0014,50,edge);
    }
    else if(1100 < distance && distance <= 1800)
    {
        //tracer.run(0.08,0.0035,0.00116,68,edge);
        //tracer.run(0.097,0.04,0.0012,60,edge);
        tracer.run(0.097,0.051,0.0014,50,edge);
    }
    else if(1800 < distance && distance <= 2580)
    {
        //tracer.run(0.08,0.0035,0.00116,68,edge);
        //tracer.run(0.097,0.04,0.0012,60,edge);
        tracer.run(0.097,0.051,0.0014,50,edge);
    }
    /* 第一コーナー */ //2630 3300
    else if(2580 < distance && distance <= 3500)
    {
        tracer.run(0.26,0.11,0.0012,40,edge);
    }
    /* 第一コーナー → 第二コーナー */ //3500 4750
    else if(3500 < distance && distance <= 4650)
    {
        tracer.run(0.097,0.051,0.0014,50,edge);
        //tracer.run(0.046,0.003,0.0013,68,edge);
    }
    /* 第二コーナー */
    else if(4650 < distance && distance <= 5450)
    {
        tracer.run(0.26,0.11,0.0012,40,edge);
    }
    /* 第二コーナー → シーン➀ */ //5450 6130
    else if(5450 < distance && distance <= 6130)
    {
        tracer.run(0.097,0.051,0.0014,50,edge);
    }
    /* シーン➀ */ //6130 6350
    else if(6130 < distance && distance <= 6130)
    {
        if(firstEdge == -1){
            constanttracer.constant_run(39, 28);//39,28走らないから無理やり変える
        }else if(firstEdge == 1){
            constanttracer.constant_run(28, 32);
        }
    }
    /* シーン➁ */ //6350 8060
    else if(6130 < distance && distance <= 8070)
    {
       tracer.run(0.2106,0.07,0.0023,40,edge);
    }
    /* シーン➂ */ //8060 8190
    else if(8070 < distance && distance <= 8130)
    {
        if(firstEdge == -1){
            constanttracer.constant_run(47, 37);
        }else if(firstEdge == 1){
            constanttracer.constant_run(37, 41);
        }
    }
    /* シーン➃ */ //8190 10650
    else if(8130 < distance && distance <= 10650)
    {
        tracer.run(0.33,0.2,0.0015,37,edge);
        //tracer.run(0.3,0.26,0.0015,37,edge);
    }
    /* シーン➄ */ //10650 10800
    else if(10650 < distance && distance <= 10800)
    {
        if(firstEdge == -1){
            constanttracer.constant_run(28, 43);
        }else if(firstEdge == 1){
            constanttracer.constant_run(38, 28);
        }
    }
    /* シーン➅ */ //10800 11540
    else if(10800 < distance && distance <= 11440)
    {
        tracer.run(0.2106,0.07,0.0023,40,edge);
    }
    /* シーン➆ */ //11540 11758
    else if(11440 < distance && distance <= 11708)
    {
        if(firstEdge == -1){
            constanttracer.constant_run(35, 30);//45,30
        }else if(firstEdge == 1){
            constanttracer.constant_run(30, 33);
        }
    }
    /* ダブルループ出口 → デブリリムーバル入り口 */
    else if(11708 < distance && distance <= 12130)
    {
        tracer.run(0.097,0.051,0.0014,50,edge);
    }  
    else if(12130 < distance)
    {
        tracer.run(0.097,0.051,0.0014,0,edge);
    }  
}