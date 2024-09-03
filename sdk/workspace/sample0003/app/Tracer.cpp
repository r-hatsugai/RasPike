#include "Tracer.h" // <1>

//---------------------------------
//コンストラクタでポート設定
//---------------------------------
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

//---------------------------------
//走行関数
//---------------------------------
void Tracer::run(float KP, float KI ,float KD, int BASE_SPEED ,int edge) {
  //------------------------------
  //変数に値を格納
  //------------------------------
  LEFT_EDGE=-1;
  RIGHT_EDGE=1;

  //------------------------------
  //カラーセンサからRGB値を取得
  //------------------------------
  colorSensor.getRawColor(rgb_val);

  //------------------------------
  //pid計算
  //------------------------------
  pid_val=pid.pid_calculate(rgb_val,KP,KI,KD);

  //------------------------------
  //HSV計算
  //------------------------------
  out=hsv.hsv_calculate(rgb_val);

  //------------------------------
  //モータ回転数計算
  //------------------------------
  left_motor_power  = (S32)(BASE_SPEED + (pid_val * edge)); // int
  right_motor_power = (S32)(BASE_SPEED - (pid_val * edge));//steering_amount

  //------------------------------
  //モータに値格納
  //------------------------------
  leftWheel.setPWM(left_motor_power);
  rightWheel.setPWM(right_motor_power);
  
}
