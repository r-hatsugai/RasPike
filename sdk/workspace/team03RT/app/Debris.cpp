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

    //---------------------------------------------
    //直進
    //---------------------------------------------
    if(d_distance < 228.0)//〇の固定値
    {
        tracer.run(0.2, 0, 0.016, 50, 1);
    }
    else if(228.0 <= d_distance && d_distance < 374.0)//pid
    {
        gyrosensor.reset();
        constant.gyro_run(50 , 50);
    }
    //----------------------------------------------
    else if(374.0 <= d_distance && d_distance < 573.0)//〇の固定値
    {
        tracer.run(0.2, 0, 0.016, 50, 1);
    }
    else if(573.0 <= d_distance && d_distance < 717.0)//pid
    {
        //gyrosensor.reset();
        constant.gyro_run(50 , 50);
    }
    //----------------------------------------------
    else if(717.0 <= d_distance && d_distance < 923.0)//〇の固定値
    {
        tracer.run(0.2, 0, 0.016, 50, 1);
    }
    else if(923.0 <= d_distance && d_distance < 990.0)//pid
    {
        //gyrosensor.reset();
        constant.gyro_run(50 , 50);
    }
    else if(d_distance >= 990.0)
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

bool Debris::debris_removal2(float d_distance, float leftdistance, float rightdistance)
{
    //---------------------------------------------
    //フラグ返す
    //---------------------------------------------
    //printf("\ndebris_removal2:distance%f\n",d_distance);
    //printf("Rem2:Direction:%f\n",Direction);

    //gyrosensor.reset();

    //---------------------------------------------
    //直進
    //---------------------------------------------
    if(d_distance < 20.0)//〇の固定値
    {
        //tracer.run(0.25, 0, 0.016, 40, 1);
        gyrosensor.reset();
        constant.gyro_run(50 , 50);
    }
    else if(20.0 <= d_distance && d_distance < 230.0)//pid
    {
        tracer.run(0.2, 0, 0.016, 50, -1);
    }
    //----------------------------------------------
    else if(230.0 <= d_distance && d_distance < 375.0)//〇の固定値
    {
        gyrosensor.reset();
        constant.gyro_run(50 , 50);
        
    }
    else if(375.0 <= d_distance && d_distance < 595.0)//pid 距離の見直し
    {
        tracer.run(0.2, 0, 0.016, 50, -1);
    }
    //----------------------------------------------
    else if(595.0 <= d_distance && d_distance < 735.0)//〇の固定値
    {
        gyrosensor.reset();
        constant.gyro_run(50 , 50);
    }
    else if(735.0 <= d_distance && d_distance < 950.0)//pid
    {
        tracer.run(0.2, 0, 0.016, 50, -1);
    }
    //----------------------------------------------
    else if(950.0 <= d_distance && d_distance < 1050.0)//〇の固定値
    {
        gyrosensor.reset();
        constant.gyro_run(50 , 50);
    }
    else if(d_distance >= 1050.0)
    {
        constant.gyro_run(0 , 0);
        
        constant.constant_run(0 , 0);
          
        flag = true;      
        
    }
    
    return flag;
}

//----------------------------------------
//1マス分直進する関数
//----------------------------------------
bool Debris::debris_short(float d_distance, float leftdistance, float rightdistance)
{
    
    //printf("\ndebris_short:distance%f\n",d_distance);
    //printf("s_Direction:%f\n",s_Direction);

    if(d_distance < 50.0)
    {
        constant.constant_run(50 , 50);
        //tracer.run(0.2, 0, 0.016, 50, 1);
    }
    else if(50.0 <= d_distance && d_distance < 335.0)
    {
        tracer.run(0.2, 0, 0.016, 0, 1);
    }
    //----------------------------------------------
    else if(335.0 <= d_distance && d_distance < 425.0)
    {
        //constant.constant_run(50 , 50);
    }
    else if(425.0 <= d_distance)
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
        constant.constant_run(-60 , 60);

        //-------------------------------------------------------
        //方位が一定を超えたら停止
        //-------------------------------------------------------
        if(s_Direction > 88.0)
        {
            constant.gyro_run(0 , 0);   
            direction.Direction_init();
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
        printf("\ndebris_action:distance2:%f\n",distance2);

        d_flag2 = debris_removal2(distance2, leftdistance2, rightdistance2);

    }
}