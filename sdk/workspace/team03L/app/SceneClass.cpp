#include "SceneClass.h"

SceneClass::SceneClass():
    colorSensor(PORT_2){
        direction.Direction_init();
    }


void SceneClass::scene_decide(float distance){
    //---------------------------------
    //エッジ判断
    //---------------------------------
    edge=edgeexchange.edge_exchange();

    //firstEdge = -1:L ,firstEdge = 1:R
    firstEdge=edgeexchange.edge_past();
    
    constanttracer.gyro_run(35, 35);

    //---------------------------------
    //シーン判断
    //---------------------------------
    
    /* スタート → 第一コーナー */
    /* 第二コーナー → シーン➀ */ //5450 6130
    
    //  if(distance <= 5500)
    //  {
    //      tracer.run(0.097,0.051,0.0014,60,edge);
    //  }
    //  /* シーン➀ */ //6130 6350
    //  else if(5500 < distance && distance <= 7700)
    //  {
    //      constanttracer.constant_run(41, 28);//39,28走らないから無理やり変える
    //  }
    //  /* シーン➁ */ //6350 8060
    //  else if(7700 < distance && distance <= 2450)
    //  {
    //      tracer.run(0.2106,0.07,0.0023,40,edge);
    //  }
    //  /* シーン➂ */ //8060 8190
    //  else if(2450 < distance && distance <= 2600)
    //  {
    //      //left,right39,37
    //      tracer.run(0.3,0.24,0.0015,0,edge);
    //      //constanttracer.constant_run(38, 35);
    //  }
    //  /* シーン➃ */ //8190 10650
    //  else if(2600 < distance && distance <= 4940)
    //  {
    //      tracer.run(0.3,0.24,0.0015,0,edge);
    //      //tracer.run(0.3,0.26,0.0015,37,edge);
    //  }
    //  /* シーン➄ */ //10650 10800
    //  else if(4940 < distance && distance <= 5090)
    //  {
    //      constanttracer.constant_run(28, 43);
    //  }
    //  /* シーン➅ */ //10800 11540
    //  else if(5090 < distance && distance <= 5830)
    //  {
    //      tracer.run(0.2106,0.07,0.0023,40,edge);
    //  }
    //  /* シーン➆ */ //11540 11758
    //  else if(5830 < distance && distance <= 6048)
    //  {
    //      constanttracer.constant_run(37, 30);
    //  }
    //  /* ダブルループ出口 → デブリリムーバル入り口 */
    //  else if(6048 < distance && distance <= 6420)
    //  {
    //      tracer.run(0.097,0.051,0.0014,50,edge);
    //  }  

     
}