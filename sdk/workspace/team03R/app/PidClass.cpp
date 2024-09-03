#include "PidClass.h"

PidClass::PidClass():
 colorSensor(PORT_2){
}

int PidClass::pid_calculate(float KP, float KI ,float KD){

    colorSensor.getRawColor(rgb_val);

    //--------------------
    //変数宣言
    //-------------------
    DELTA_T=0.004;
    PID_MAX=40;
    PID_MIN=-40;

    //---------------------
    //目標輝度設定
    //---------------------
    target_brightness=85;

    //---------------------
    //目標輝度の差
    //---------------------
    diff_brightness=(float32_t)(target_brightness - rgb_val.g);

    //-------------------------------------------------------------------------
    //センサーの値　ー　目標値
    //-------------------------------------------------------------------------
    diff[0] = diff[1];
    diff[1] = diff_brightness;
    integral += (diff[1] + diff[0]) / 2.0 * DELTA_T;

    //-------------------------------------------------------------------------
    //PID制御
    //-------------------------------------------------------------------------
    p = KP * diff[1]; /* P:目標値と現在地との差(偏差)に比例した操作量を調整する制御 */ 
    i = KI * integral; /* I:偏差を時間的に蓄積し、蓄積した量がある大きさになった所で、操作量を増やして偏差をなくすように動作させ、比例動作に積分動作を加えた制御 */
    d = KD * (diff[1] - diff[0]) / DELTA_T; /* D:今回に偏差と前回の偏差を比較し、偏差の大小によって機敏に反応するようにする制御 */
    Pid = p + i + d;
    if(Pid>PID_MAX){
        Pid=PID_MAX;
    }else if(Pid<PID_MIN){
        Pid=PID_MIN;
    }
    
    return Pid;
}

