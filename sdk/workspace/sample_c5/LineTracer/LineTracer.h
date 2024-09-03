#ifndef LINETRACER_H
#define LINETRACER_H
 
/* 下記の項目は各ロボットに合わせて変えること */
 
/* カラーセンサの輝度設定 */
#define WHITE_BRIGHTNESS  (180)
#define BLACK_BRIGHTNESS  (10)
 
/* ステアリング操舵量の係数 */
#define STEERING_COEF     (0.2F)
 
/* 走行基準スピード */
#define BASE_SPEED        (60)
 
/* ライントレースエッジ切り替え */
#define LEFT_EDGE         (-1) 
#define RIGHT_EDGE        (1)
 
#endif
