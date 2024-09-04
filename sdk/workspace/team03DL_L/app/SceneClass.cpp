#include "SceneClass.h"

SceneClass::SceneClass():
    leftWheel(PORT_C), rightWheel(PORT_B),  gyrosensor(PORT_4), colorSensor(PORT_2){
        direction.Direction_init();
    }


bool SceneClass::scene_decide(float distance){
    //---------------------------------
    //エッジ判断
    //---------------------------------
    //edge=edgeexchange.edge_exchange();

    //firstEdge = -1:L ,firstEdge = 1:R
    firstEdge=edgeexchange.edge_past();
    
    //constanttracer.gyro_run(35, 35);

    flag = false;

    //---------------------------------
    //シーン判断2770
    //---------------------------------
    
    if(distance <= 2770)
    {
        //tracer.run(0.095,0,0.009,50,firstEdge);
        //tracer.run(0.095,0,0.009,50,firstEdge);
        //tracer.run(0.095,0,0.009,60,firstEdge);
        tracer.run(0.075,0.015,0.02,65,firstEdge);
        //tracer.run(0.07,0,0.016,70,firstEdge);
        //tracer.run(0.064,0,0.012,73,firstEdge);
        //tracer.run(0.09,0,0.035,80,firstEdge);
    }
    
    /* 第一コーナー */ //2630 3300 2580 3500
    else if(2770 < distance && distance <= 3280) //0.298,0.25,0.003,  0.26,,0.00238
    {
        tracer.run(0.217,0,0.014,45,firstEdge);
    }
    /* 第一コーナー → 第二コーナー */ //3500 4750 4800
    else if(3280 < distance && distance <= 4800)
    {
        //tracer.run(0.095,0,0.009,60,firstEdge);
        tracer.run(0.075,0.015,0.02,65,firstEdge);
    }
    /* 第二コーナー */
    else if(4800 < distance && distance <= 5590)
    {
        tracer.run(0.3,0,0.028,45,firstEdge);
    }
    /* 第二コーナー → シーン➀ */ //5400 6130 550
    else if(5590 < distance && distance <= 6130)
    {
        tracer.run(0.09,0,0.009,50,firstEdge);
    }
    /* シーン➀ */ //6130 6360 280
    else if(6130 < distance && distance <= 6320)
    {
        if(firstEdge == -1){
            constanttracer.constant_run(58, 40);
        }else if(firstEdge == 1){
            constanttracer.constant_run(28, 32);
        }
    }
    /* シーン➁ 前半 */ //6360 8070 1620
    else if(6320 < distance && distance <= 7470)
    {
        tracer.run(0.2,0,0.008,35,1);
       //tracer.run(0.187,0,0.012,40,edge);
    }
    /* シーン➁ 後半 */ //6360 8070 1620
    else if(7470 < distance && distance <= 8070)
    {
       tracer.run(0.25,0,0.017,45,1);//42
    }
    /* シーン➂ */ //8070 8180 170
    else if(8070 < distance && distance <= 8180)
    {
        if(firstEdge == -1){
            constanttracer.constant_run(42, 32);
        }else if(firstEdge == 1){
            constanttracer.constant_run(37, 41);
        }
    }
    /* シーン➃ 前半 */ //8180 10690 2480
    else if(8180 < distance && distance <= 8500)
    {
            tracer.run(0.37,0,0.022,37,-1);
            //tracer.run(0.3,0.26,0.0015,37,edge);        
            //tracer.run(0.27,0,0.022,0,edge);
    }
        /* シーン➃ 後半 */ //8180 10690 2480
    else if(8500 < distance && distance <= 10670)
    {
            tracer.run(0.37,0,0.022,45,-1);
            //tracer.run(0.3,0.26,0.0015,37,edge);        
            //tracer.run(0.27,0,0.022,0,edge);
    }

    /* シーン➄ */ //10690 10800 151
    else if(10670 < distance && distance <= 10821)
    {
        if(firstEdge == -1){
            constanttracer.constant_run(28, 42);
        }else if(firstEdge == 1){
            constanttracer.constant_run(38, 28);
        }
    }
    /* シーン➅ */ //10800 11580 730
    else if(10821 < distance && distance <= 11551)
    {
        tracer.run(0.24,0,0.015,45,1);
    }
    /* シーン➆ */ //11580 11730 174
    else if(11551 < distance && distance <= 11705)
    {
        if(firstEdge == -1){
            constanttracer.constant_run(54, 28);
        }else if(firstEdge == 1){
            constanttracer.constant_run(30, 33);
        }
    }
    /* ダブルループ出口 → デブリリムーバル入り口 */ //11730 12130 570
    else if(11705 < distance && distance <= 12657)
    {
        
        tracer.run(0.15,0,0.01,45,-1);
        
    }  
    else if(12657 < distance) //12130
    {
        edge=edgeexchange.edge_exchange();
        if(edge == 1){
            tracer.run(0.095,0,0.009,0,-1);
        }else{
            //leftWheel.reset();
            //rightWheel.reset();
            //gyrosensor.reset();
            //flag = true;
        }
    }        

    return flag;
}