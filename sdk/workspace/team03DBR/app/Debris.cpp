#include "Debris.h"
#include <unistd.h>

Debris::Debris():
    leftWheel(PORT_C), rightWheel(PORT_B), gyrosensor(PORT_4)
    {}

void Debris::init() {
  init_f("Debris");
}

//----------------------------------------
//４マス分直進する関数
//----------------------------------------
bool Debris::debris_removal(float d_distance,float leftdistance, float rightdistance)
{
    flag = true;
    //---------------------------------------------
    //フラグ返す
    //---------------------------------------------
    //printf("\nRem:distance%f\n",d_distance);
    //printf("Rem:Direction:%f\n",Direction);
    //printf("\n方位:%f\n",Direction);
    printf("直進と90度回転\n");
    //---------------------------------------------
    //直進
    //---------------------------------------------

    if(d_distance < 100.0)//〇の固定値
    {
        //constant.gyro_run(50 , 50);
        //constant.constant_run(50, 50);
        tracer.run(0.001, 0, 0.016, 50, 1);
    }
    if(100.0 <= d_distance && d_distance < 322.0)//Pid
    {
        tracer.run(0.2, 0, 0.016, 50, 1);
        //gyrosensor.reset();
    }
    else if(322.0 <= d_distance && d_distance < 436.0)//〇の固定値
    {
        //constant.gyro_run(0 , 0);
        constant.constant_run(50, 50);
        //tracer.run(0.001, 0, 0.016, 50, 1);
    }
    //----------------------------------------------
    else if(436.0 <= d_distance && d_distance < 653.0)//Pid
    {
        tracer.run(0.2, 0, 0.016, 50, 1);
        //gyrosensor.reset();
    }
    else if(653.0 <= d_distance && d_distance < 785.0)//〇の固定値
    {
        //gyrosensor.reset();
        //constant.gyro_run(50 , 50);
        constant.constant_run(50, 50);
        //tracer.run(0.001, 0, 0.016, 50, 1);
    }
    //----------------------------------------------
    else if(785.0 <= d_distance && d_distance < 1010.0)//Pid
    {
        tracer.run(0.2, 0, 0.016, 50, 1);
        //gyrosensor.reset();
    }
    else if(1010.0 <= d_distance && d_distance < 1100.0)//〇の固定値
    {
        //gyrosensor.reset();
        //constant.gyro_run(50 , 50);
        constant.constant_run(50, 50);
        //tracer.run(0.001, 0, 0.016, 50, 1);
    }
    else if(d_distance >= 1100.0)
    {
        constant.gyro_run(0 , 0);
        //-------------------------------------------------------
        //左回転の方位取得
        //-------------------------------------------------------
        direction.Direction_l_update(leftdistance, rightdistance);
        Direction = direction.Get_direction();
        //-------------------------------------------------------
        //旋回
        //-------------------------------------------------------
        constant.pid_r_turn(-60 , 60);

        //-------------------------------------------------------
        //方位が一定を超えたら停止
        //-------------------------------------------------------
        if(Direction > 90.0)
        {
            constant.gyro_run(0 , 0);   
            flag = false;      
        }
    }
    
    return flag;
}

//----------------------------------------
//４マス分直進する関数（L字後半）
//----------------------------------------
bool Debris::debris_removal2(float d_distance, float leftdistance, float rightdistance)
{
    //---------------------------------------------
    //フラグ返す
    //--------------------------------------------
    printf("直進\n");
    //---------------------------------------------
    //直進
    //---------------------------------------------
    if(d_distance < 20.0)//〇の固定値
    {
        //gyrosensor.reset();
        //constant.gyro_run(50 , 50);
        //constant.constant_run(50, 50);
        tracer.run(0.001, 0, 0.016, 50, -1);
    }
    else if(20.0 <= d_distance && d_distance < 230.0)//pid
    {
        tracer.run(0.2, 0, 0.016, 50, -1);
    }
    //----------------------------------------------
    else if(230.0 <= d_distance && d_distance < 380.0)//〇の固定値
    {
        //gyrosensor.reset();
        //constant.gyro_run(50 , 50);
        //constant.constant_run(50, 50);
        tracer.run(0.001, 0, 0.016, 50, -1);
    }
    else if(380.0 <= d_distance && d_distance < 590.0)//pid 
    {
        tracer.run(0.2, 0, 0.016, 50, -1);
    }
    //----------------------------------------------
    else if(590.0 <= d_distance && d_distance < 735.0)//〇の固定値
    {
        //gyrosensor.reset();
        //constant.gyro_run(50 , 50);
        //constant.constant_run(50, 50);
        tracer.run(0.001, 0, 0.016, 40, -1);
    }
    else if(735.0 <= d_distance && d_distance < 950.0)//pid
    {
        tracer.run(0.2, 0, 0.016, 50, -1);
    }
    //----------------------------------------------
    else if(950.0 <= d_distance && d_distance < 1050.0)//〇の固定値
    {
        //gyrosensor.reset();
        //constant.gyro_run(50 , 50);
        //constant.constant_run(50, 50);
        tracer.run(0.001, 0, 0.016, 40, -1);
    }
    else if(d_distance >= 1050.0)
    {    
       constant.constant_run(0 , 0);
          
        flag = false;      
    }
    
    return flag;
}

//----------------------------------------
//1マス分直進する関数
//----------------------------------------
bool Debris::debris_short(float d_distance, float leftdistance, float rightdistance)
{
    printf("1マス直進と90度回転\n");

    if(d_distance < 20.0)//〇の固定値
    {
        //gyrosensor.reset();
        //constant.gyro_run(50 , 50);
        //constant.constant_run(50, 50);
        tracer.run(0.001, 0, 0.016, 50, -1);
    }
    else if(20.0 <= d_distance && d_distance < 200.0)//pid
    {
        tracer.run(0.2, 0, 0.016, 50, -1);
    }
    //----------------------------------------------
    else if(200.0 <= d_distance && d_distance < 375.0)//〇の固定値
    {
        //gyrosensor.reset();
        //constant.gyro_run(50 , 50);
        //constant.constant_run(50, 50);
        tracer.run(0.001, 0, 0.016, 50, -1);
    }
    else if(375.0 <= d_distance)
    {
        constant.constant_run(0 , 0);
        //-------------------------------------------------------
        //左回転の方位取得
        //-------------------------------------------------------
        direction.Direction_l_update(leftdistance, rightdistance);
        s_Direction = direction.Get_direction();
        //-------------------------------------------------------
        //旋回
        //-------------------------------------------------------
        constant.pid_r_turn(-65 , 65);
        //printf("\n方位:%f\n",s_Direction);

        //-------------------------------------------------------
        //方位が一定を超えたら停止
        //-------------------------------------------------------
        if(s_Direction > 90.0)
        {
            //tracer.run(0.2, 0, 0.016, 0, -1);
            constant.gyro_run(0 , 0);   
            //direction.Direction_init();
            run_flag = false;      
        }
    }
    return run_flag;
}

void Debris::debris_action(float d_distance, float leftdistance, float rightdistance)
{
    //d_flag2 = debris_removal2(d_distance, leftdistance, rightdistance);
    if(b_flag)
    {
        if(a_flag)
        {
            //一回目
            a_flag = debris_removal(d_distance, leftdistance, rightdistance);
        }
        else
        {
            b_flag = false;
            distance.Distance_reset();
            gyrosensor.reset();
        }
    }
    else
    {
        distance2 = distance.Distance_calculate();
        leftdistance2 = distance.Get_distance_left();
        rightdistance2 = distance.Get_distance_right();

        //二回目
        c_flag = debris_removal2(distance2, leftdistance2, rightdistance2);
    }
    
}