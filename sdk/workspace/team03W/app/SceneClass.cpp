#include "SceneClass.h"

SceneClass::SceneClass():
    leftWheel(PORT_C), rightWheel(PORT_B),  gyrosensor(PORT_4), colorSensor(PORT_2){
        direction.Direction_init();
    }


bool SceneClass::scene_decide(float distance){
    //---------------------------------
    //エッジ判断
    //---------------------------------
    edge=edgeexchange.edge_exchange();

    //firstEdge = -1:L ,firstEdge = 1:R
    firstEdge=edgeexchange.edge_past();
    
    //constanttracer.gyro_run(35, 35);

    flag = false;

    //---------------------------------
    //シーン判断2770
    //---------------------------------
    
    if(distance <= 2770)
    {
        tracer.run(0.095,0,0.009,50,edge);
        //tracer.run(0.19,0,0.009,45,edge);
        //tracer.run(0.0162,0.0001,0.00074,85,edge);
        //tracer.run(0.0214,0.0001,0.0006,80,edge);
        //tracer.run(0.196,0,0.00181,55,edge);
        //tracer.run(0.198,0.11,0.00163,50,edge);
        //tracer.run(0.036,0.0001,0.0008,75,edge);
        //tracer.run(0.097,0.04,0.0012,60,edge);
    }
    
    /* 第一コーナー */ //2630 3300 2580 3500
    else if(2770 < distance && distance <= 3280) //0.298,0.25,0.003,  0.26,,0.00238
    {
        tracer.run(0.217,0,0.014,45,edge);
    }
    /* 第一コーナー → 第二コーナー */ //3500 4750 4800
    else if(3280 < distance && distance <= 4800)
    {
        //tracer.run(0.0217,0.0001,0.00066,0,edge);
        tracer.run(0.095,0,0.009,50,edge);
        //tracer.run(0.046,0.003,0.0013,68,edge);
    }
    /* 第二コーナー */
    else if(4800 < distance && distance <= 5590)
    {
        tracer.run(0.3,0,0.028,45,edge);
    }
    /* 第二コーナー → シーン➀ */ //5400 6130 550
    else if(5590 < distance && distance <= 6130)
    {
        tracer.run(0.09,0,0.009,50,edge);
    }
    /* シーン➀ */ //6130 6360 280
    else if(6130 < distance && distance <= 6380)
    {
        //gyrosensor.reset();
        if(firstEdge == -1){
            constanttracer.constant_run(45, 30);//gyro_run(42, 30)
        }else if(firstEdge == 1){
            constanttracer.constant_run(28, 32);//gyro_run(28, 32)
        }
    }
    /* シーン➁ */ //6360 8070 1620
    else if(6280 < distance && distance <= 7770)
    {
        if(edge == 1){
            tracer.run(0.182,0,0.01,40,edge);
        }else{
            //思ってないエッジ切り替え
            tracer.run(0.187,0,0.012,0,edge);
        }
        //0.187
       //tracer.run(0.187,0,0.012,40,edge);//42
    }
        /* シーン➁ */ //6360 8070 1620
    else if(7770 < distance && distance <= 8070)
    {
        //0.187
       tracer.run(0.25,0,0.017,42,edge);//42
    }
    /* シーン➂ */ //8070 8180 170
    else if(8070 < distance && distance <= 8200)
    {
        gyrosensor.reset();
        if(firstEdge == -1){
            constanttracer.constant_run(50, 36);//42,30
        }else if(firstEdge == 1){
            constanttracer.constant_run(37, 41);//37,41
        }
    }
    /* シーン➃ */ //8180 10690 2480
    else if(8200 < distance && distance <= 10670)
    {
        if(edge == -1){
            tracer.run(0.27,0,0.024,40,edge);
            //tracer.run(0.3,0.26,0.0015,37,edge);
        }else{
            //思ってないエッジ切り替え
            tracer.run(0.27,0,0.022,0,edge);
        }
    }
    /* シーン➄ */ //10690 10800 151
    else if(10670 < distance && distance <= 10821)
    {
        gyrosensor.reset();
        if(firstEdge == -1){
            constanttracer.constant_run(28, 42);//gyro_run(28, 42)
        }else if(firstEdge == 1){
            constanttracer.constant_run(38, 28);//gyro_run(38, 28)
        }
    }
    /* シーン➅ */ //10800 11580 730
    else if(10821 < distance && distance <= 11551)
    {
        if(edge == 1){
            tracer.run(0.24,0,0.015,45,edge);
        }else{
            //思ってないエッジ切り替え
            tracer.run(0.24,0,0.015,0,edge);
        }
    }
    /* シーン➆ */ //11580 11730 174
    else if(11551 < distance && distance <= 11685)
    {
        gyrosensor.reset();
        if(firstEdge == -1){
            constanttracer.constant_run(47, 28);//45,30
        }else if(firstEdge == 1){
            constanttracer.constant_run(30, 33);
        }
    }
    /* ダブルループ出口 → デブリリムーバル入り口 */ //11730 12130 570
    else if(11685 < distance && distance <= 12255)
    {
        if(edge == -1){
            tracer.run(0.095,0,0.009,50,edge);
        }else{
            //思ってないエッジ切り替え
            tracer.run(0.095,0,0.009,0,edge);
        }
    }  
    else if(122555 < distance) //12130
    {
        leftWheel.reset();
        rightWheel.reset();
        gyrosensor.reset();
        flag = true;
    }        

    return flag;
}