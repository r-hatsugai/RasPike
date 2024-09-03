#include "Tracer.h" // <1>



Tracer::Tracer():
  leftWheel(PORT_C), rightWheel(PORT_B), colorSensor(PORT_2), sonarSensor(PORT_3) { // <2>
}

void Tracer::init() {
  init_f("Tracer");
}

void Tracer::terminate() {
  msg_f("Stopped.", 1);
  leftWheel.stop();  // <1>
  rightWheel.stop();
}

void Tracer::run() {
  //--------------------
  //変数宣言
  //-------------------
  DELTA_T=0.004;
  KP=0.066; //0.0659
  KI=0.003; //0.001
  KD=0.0012; //0.0015
  PID_MAX=40;
  PID_MIN=-40;
  
  //---------------------
  //
  //---------------------
  rgb_raw_t rgb_val;

  //---------------------
  //手をかざしてスタートする機能
  //---------------------
  /*while(1){
    distance=sonarSensor.getDistance();
    if(distance==10){
      break;
    }
  }*/

  //---------------------
  //
  //---------------------
  target_brightness=85;

  //---------------------
  //
  //---------------------
  colorSensor.getRawColor(rgb_val);

  //---------------------
  //
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
  pid = p + i + d;
  if(pid>PID_MAX){
      pid=PID_MAX;
  }else if(pid<PID_MIN){
      pid=PID_MIN;
  }

  printf("pid %f\n", pid);

  left_motor_power  = (S32)(BASE_SPEED + (pid * LEFT_EDGE)); // int
  right_motor_power = (S32)(BASE_SPEED - (pid * LEFT_EDGE));//steering_amount


  leftWheel.setPWM(left_motor_power);
  rightWheel.setPWM(right_motor_power);
  
}
