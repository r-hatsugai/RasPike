#include "Debris.h"
#include <unistd.h>


#define GRID_NUM 4

typedef enum{
    TURN,//目標座標の方向へ向くまで旋回
    MOVE,//目標座標に到達するまで前進
    // EX,//デブリ除去
    END  //構造体に格納される座標
}RUN_STATE;

struct GRID_XY{
    int gridX;
    int gridY;
};

Debris::Debris():
    leftWheel(PORT_C), rightWheel(PORT_B), gyrosensor(PORT_4)
    {
        cur_gridX = 0;//現在位置座標のX値
        cur_gridY = 0;//現在位置座標のY値
        target_dir = 0.0;//現在位置座標から目標座標までの方位
        target_dis = 0.0;//現在位置座標から目標座標までの距離
        cur_dir = 0.0;//方位計の現在値
        cur_dis = 0.0;//距離計の現在値
        grid_count= 0;//目標座標構造体への参照カウンタ
        distance.Distance_reset();
        direction.Direction_init();

    }

void Debris::init() {
  init_f("Debris");
}

void Debris::debris_removal(float leftdistance, float rightdistance)
{
    //-------------------------------------------
    //目標座標の設定
    //-------------------------------------------
    static RUN_STATE state = TURN;
    struct GRID_XY target_grid[GRID_NUM] = {{1,0},
                                            {2,0},
                                            {3,0},
                                            {2,0},
                                            };//(y軸,x軸)

                                            /*
                                            パターン１
                                            {0,2},
                                            {1,1},
                                            {2,2},
                                            {3,0},
                                            };

                                            パターン２
                                            {0,0},
                                            {0,3},
                                            {1,2},
                                            {2,1},
                                            };

                                            パターン３(1,1への９０度旋回ができない)
                                            {1,0},
                                            {1,1},
                                            {0,3},
                                            {2,2},
                                            };

                                            パターン４
                                            {0,0},
                                            {0,3},
                                            {1,1},
                                            {3,2},
                                            };

                                            パターン５
                                            {0,1},
                                            {1,2},
                                            {2,0},
                                            {3,0},
                                            };
                                            */
/*
3,0  3,1  3,2  3,3  3,4(スマートキャリーボトル)  3,6(ゴール)
2,0
1,0
0,0                       0,5(置く場所)
dd*/
    //-------------------------------------------
    //目標座標までの距離、方位を格納
    //-------------------------------------------
    coordinate.Grid_setdistance(cur_gridX, cur_gridY, target_grid[grid_count].gridX,target_grid[grid_count].gridY);
    coordinate.Grid_setdirection(cur_gridX, cur_gridY, target_grid[grid_count].gridX,target_grid[grid_count].gridY);
    //現在地からの目標距離取得
    target_dis = coordinate.Grid_getdistance();
    //現在地からの目標方位取得
    target_dir = coordinate.Grid_getdirection();

    direction.Direction_update(leftdistance,rightdistance);
    //現在の距離取得
    cur_dis = distance.Distance_calculate();
    //現在の方位取得
    cur_dir = direction.Get_direction();  

    switch(state){
        case TURN:
            if(cur_dir < target_dir)
            {
                //右回転
                constant.pid_l_turn(50 , -50);
            }
            else if(cur_dir > target_dir)
            {
                //左回転
                constant.pid_r_turn(-50 , 50);//46
            }

            if((cur_dir > (target_dir-1.0)) && (cur_dir < (target_dir+1.0)))
            {
                gyrosensor.reset();

                printf("\nリセットcur_dir:%f\n", cur_dir);
                printf("リセットtarget_ex:%f\n", target_dir);

                sleep(500*1000);//4*1000
                state = MOVE;
            }
            break;

        case MOVE:
            constant.gyro_run(50, 50);
            if((cur_dis > target_dis) && (grid_count < (GRID_NUM-1)))
            {
                cur_gridX = target_grid[grid_count].gridX;
                cur_gridY = target_grid[grid_count].gridY;

                distance.Distance_reset();
                direction.Direction_setdirection(target_dir);

                grid_count++;
                coordinate.Grid_setdistance(cur_gridX, cur_gridY, target_grid[grid_count].gridX, target_grid[grid_count].gridY);
                coordinate.Grid_setdirection(cur_gridX, cur_gridY, target_grid[grid_count].gridX, target_grid[grid_count].gridY);
                target_dis = coordinate.Grid_getdistance();
                target_dir = coordinate.Grid_getdirection();
                printf("ムーブ次の方位:%f\n", target_dir);
                printf("ムーブ次の現在方位:%f\n", cur_dir);
                                
                //state = EX;
                state = TURN;
                gyrosensor.reset();
                distance.Distance_reset();
                break;
            }
            else if((cur_dis > target_dis) && (grid_count >= (GRID_NUM-1)))
            {
                state = END;
            }
            break;

        // case EX:

        //     target_ex = distance.Distance_calculate();
            
        //     if(target_ex < 15)
        //     {
        //         constant.gyro_run(40 , 50);//46

        //     }else if(target_ex >= 15 && target_ex <= 30)
        //     {
        //         constant.gyro_run(-50 , -40);//46
        //     }

        //     sleep(500*1000);//4*1000
        //     state = TURN;
        //     gyrosensor.reset();
        //     break;

        case END:

            constant.constant_run(true , true);
            distance.Distance_reset();
            direction.Direction_init();
            break;

        default:
            break;
    }
    
}