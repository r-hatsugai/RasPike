//---------------------------------
//速度
//LAP 20.03 ダブルループ 60.03
//---------------------------------

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

    flag = true;

    //---------------------------------
    //シーン判断
    //---------------------------------
    //printf("distance%f\n", distance);
    
    //右斜めに傾け設置する
    if(distance <= 2770)
    {        
        //tracer.run(0.095,0,0.009,50,firstEdge);
        //tracer.run(0.095,0,0.009,60,firstEdge);
        //tracer.run(0.075,0.015,0.02,65,firstEdge);
        tracer.run(0.1,0,0.03,70,firstEdge);
        //tracer.run(0.064,0,0.012,73,firstEdge);
        //tracer.run(0.074,0,0.033,75,firstEdge);
        //tracer.run(0.088,0,0.0349,80,firstEdge);
    }    
    /* 第一コーナー */ //2630 3300 2580 3500
    else if(2770 < distance && distance <= 3340) //0.298,0.25,0.003,  0.26,,0.00238
    {
       /* 充電満タン時 */
        tracer.run(0.211,0,0.015,45,firstEdge);
        /* 充電微量時 */
        //tracer.run(0.19,0,0.016,45,firstEdge);
    }
    /* 第一コーナー → 第二コーナー */ //3500 4750 4800
    else if(3340 < distance && distance <= 4800)
    {
        //tracer.run(0.095,0,0.009,50,firstEdge);
        //tracer.run(0.046,0.003,0.0013,68,edge);
        //tracer.run(0.07,0,0.015,70,firstEdge);
        tracer.run(0.1,0,0.03,70,firstEdge);
        //tracer.run(0.07,0,0.02,80,firstEdge);
        //tracer.run(0.088,0,0.0348,80,firstEdge);
    }
    /* 第二コーナー */
    else if(4800 < distance && distance <= 5590)
    {
       /* 充電満タン時 */       
        tracer.run(0.24,0,0.015,45,firstEdge);
        /* 充電微量時 */
        //tracer.run(0.19,0,0.016,45,firstEdge);    
        //tracer.run(0.2,0,0.016,45,firstEdge);
    }
    /* 第二コーナー → シーン➀ */ //5400 6130 550
    else if(5590 < distance && distance <= 6130)
    {
        //tracer.run(0.09,0,0.009,50,firstEdge);
        tracer.run(0.1,0,0.03,50,firstEdge);
    }
    /* シーン➀ */ //6130 6360 280
    else if(6130 < distance && distance <= 6320)
    {
        constanttracer.constant_run(32, 36);
    }
    /* シーン➁ 前半 */ //6360 8070 1620
    else if(6320 < distance && distance <= 7470)
    {
        tracer.run(0.2,0,0.008,35,-1);
       //tracer.run(0.187,0,0.012,40,edge);//42
    }
    /* シーン➁ 後半 */ //6360 8070 1620
    else if(7470 < distance && distance <= 8070)
    {
        //0.187
       tracer.run(0.25,0,0.017,45,-1);//42
    }
    /* シーン➂ */ //8070 8180 170
    else if(8070 < distance && distance <= 8250)
    {
        /* 充電満タン時 */
        constanttracer.constant_run(29, 33);
        /* 充電微量時 */
        //constanttracer.constant_run(35, 30);
    }
    /* シーン➃ 前半 */ //8180 10690 2480
    else if(8250 < distance && distance <= 8800)
    {
        tracer.run(0.39,0,0.018,37,1);
        //tracer.run(0.37,0,0.022,37,1);
        //tracer.run(0.3,0.26,0.0015,37,edge);        
        //tracer.run(0.27,0,0.022,0,edge);
    }
    /* シーン➃ 後半 */ //8180 10690 2480
    else if(8800 < distance && distance <= 10780)
    {
        tracer.run(0.37,0,0.022,45,1);
    }
    /* シーン➄ */ //10690 10800 151
    else if(10780 < distance && distance <= 10871)
    {
        //constanttracer.constant_run(56, 28);//(56, 28)
        constanttracer.constant_run(30, 35);//(30, 39)
    }
    /* シーン➅ */ //10800 11580 730
    else if(10871 < distance && distance <= 11551)
    {
        tracer.run(0.19,0,0.015,36,-1);
    }
    /* シーン➆ */ //11580 11730 174
    else if(11551 < distance && distance <= 11705)
    {
        constanttracer.constant_run(30, 35);
    }
    /* ダブルループ出口 → デブリリムーバル入り口 */ //11730 12130 570
    else if(11705 < distance && distance <= 12560)
    {        
        tracer.run(0.15,0,0.01,45,1);
        //tracer.run(0.15,0,0.01,0,1);              
    }  
    else if(12560 < distance) //12130
    {
        //edge=edgeexchange.edge_exchange();
        flag = false;
        tracer.run(0.095,0,0.009,0,1);
        gyrosensor.reset();
        constanttracer.constant_init();
    }        

    return flag;
}