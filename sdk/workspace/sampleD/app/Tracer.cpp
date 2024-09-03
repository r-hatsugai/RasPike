#include "Tracer.h" // <1>
 
//---------------------------------
//コンストラクタでポート設定
//---------------------------------
Tracer::Tracer():
  leftWheel(PORT_C), rightWheel(PORT_B), sonarSensor(PORT_3) { // <2>
}
 
void Tracer::init() {
  init_f("Tracer");
}
 
void Tracer::terminate() {
  msg_f("Stopped.", 1);
  leftWheel.stop();  // <1>
  rightWheel.stop();
}
 
//---------------------------------
//走行関数
//---------------------------------
void Tracer::run(float KP, float KI ,float KD, int BASE_SPEED ,int edge) {
 
  //------------------------------
  //pid計算
  //------------------------------
  pid_val=pid.pid_calculate(KP,KI,KD);
 
  //------------------------------
  //モータ回転数計算
  //------------------------------
  left_motor_power  = (int)(BASE_SPEED + (pid_val * edge)); // int
  right_motor_power = (int)(BASE_SPEED - (pid_val * edge));//steering_amount
 
  //------------------------------
  //モータに値格納
  //------------------------------
  leftWheel.setPWM(left_motor_power);
  rightWheel.setPWM(right_motor_power);
 
}