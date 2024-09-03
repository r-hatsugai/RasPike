#include "SceneClass.h"

SceneClass::SceneClass():
    colorSensor(PORT_2){
    }


void SceneClass::scene_decide(float distance,float leftdistance,float rightdistance){
    //---------------------------------
    //エッジ判断
    //---------------------------------
    edge=edgeexchange.edge_exchange();

    firstEdge=edgeexchange.edge_past();//firstEdge = -1:L ,firstEdge = 1:R
    //---------------------------------
    //シーン判断
    //---------------------------------
    //-------------------------------------
    //tracer.run関数の引数(KP,KI,KD,BASE SPEED,エッジ)
    //-------------------------------------
    
    /* スタート → 第一コーナー */ //2580 2770
    if(distance <= 2770)
    {
        //tracer.run(0.0162,0.0001,0.00074,85,edge);
        tracer.run(0.0211,0.0001,0.00074,80,edge);
        //tracer.run(0.196,0,0.00181,55,edge);
        //tracer.run(0.198,0.11,0.00163,50,edge);
        //tracer.run(0.036,0.0001,0.0008,75,edge);
        //tracer.run(0.097,0.04,0.0012,60,edge);
    }
    /* 第一コーナー */ //2630 3300 2580 3500
    else if(2770 < distance && distance <= 3280) //0.298,0.25,0.003,  0.26,,0.00238
    {
        tracer.run(0.1978,0.11,0.00163,45,edge);
    }
    /* 第一コーナー → 第二コーナー */ //3500 4750 4800
    else if(3280 < distance && distance <= 4830)
    {
        tracer.run(0.0211,0.0001,0.00074,80,edge);
        //tracer.run(0.097,0.051,0.0014,50,edge);
        //tracer.run(0.046,0.003,0.0013,68,edge);
    }
    /* 第二コーナー */
    else if(4830 < distance && distance <= 5400)
    {
        tracer.run(0.198,0.11,0.00163,45,edge);
    }
    /* 第二コーナー → シーン➀ */ //5450 6130
    if(5400 < distance && distance <= 6130)
    {
        tracer.run(0.097,0.051,0.0014,50,edge);
    }
    /* シーン➀ */ //6130 6350
    else if(6130 < distance && distance <= 6350)//220
    {
        if(firstEdge == -1){
            constanttracer.constant_run(41, 28);//39,28走らないから無理やり変える
        }else if(firstEdge == 1){
            constanttracer.constant_run(28, 32);
        }
    }
    /* シーン➁ */ //6350 8060
    else if(6350 < distance && distance <= 8070)//220-1720
    {
       tracer.run(0.2106,0.07,0.0023,40,edge);
    }
    /* シーン➂ */ //8060 8190
    else if(8070 < distance && distance <= 8170)//1720-1820
    {
        if(firstEdge == -1){
            constanttracer.constant_run(45, 37);
        }else if(firstEdge == 1){
            constanttracer.constant_run(37, 41);
        }
    }
    /* シーン➃ */ //8190 10650
    else if(8170 < distance && distance <= 10650)//1820-2480
    {
        tracer.run(0.33,0.2,0.0015,37,edge);
        //tracer.run(0.3,0.26,0.0015,37,edge);
    }
    /* シーン➄ */ //10650 10800
    else if(10650 < distance && distance <= 10800)//2480-
    {
        if(firstEdge == -1){
            constanttracer.constant_run(32, 43);
        }else if(firstEdge == 1){
            constanttracer.constant_run(38, 28);
        }
    }
    /* シーン➅ */ //10800 11540
    else if(10800 < distance && distance <= 11540)
    {
        tracer.run(0.2106,0.07,0.0023,40,edge);
    }
    /* シーン➆ */ //11540 11758
    else if(11540 < distance && distance <= 11708)
    {
        if(firstEdge == -1){
            constanttracer.constant_run(49, 30);
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