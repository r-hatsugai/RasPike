#include "Debris.h"
#include <unistd.h>


#define GRID_NUM 5

typedef enum{
    TURN,//目標座標の方向へ向くまで旋回
    MOVE,//目標座標に到達するまで前進
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
        target_dir = 0.0;//現在位置座標から目標座標までの距離
        target_dis = 0.0;//現在位置座標から目標座標までの方位
        cur_dir = 0.0;//方位計の現在値
        cur_dis = 0.0;//距離計の現在値
        grid_count= 0;//目標座標構造体への参照カウンタ
        distance.Distance_reset();
        direction.Direction_init();

    }

void Debris::init() {
  init_f("Debris");
}

bool Debris::debris_removal(float leftdistance, float rightdistance)
{
    //-------------------------------------------
    //目標座標の設定
    //-------------------------------------------
    static RUN_STATE state = TURN;
    struct GRID_XY target_grid[GRID_NUM] = {{2,2},
                                            {3,1},
                                            {4,2},
                                            {5,0},
                                            {5,3},
                                            };//(y軸,x軸)
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
    target_dis = coordinate.Grid_getdistance();
    target_dir = coordinate.Grid_getdirection();

    direction.Direction_update(leftdistance,rightdistance);
    cur_dis = distance.Distance_calculate();

    cur_dir = direction.Get_direction();  

    flag = false;
    

    switch(state){
        case TURN:
            if(cur_dir < target_dir)
            {
                constant.pid_l_turn(60 , -60);
            }
            else if(cur_dir > target_dir)
            {
                constant.pid_r_turn(-60 , 60);//46
            }

            if((cur_dir > (target_dir-1.0)) && (cur_dir < (target_dir+1.0)))
            {;
                gyrosensor.reset();
                sleep(500*1000);//4*1000
                state = MOVE;
            }
            break;

        case MOVE:
            constant.gyro_run(70,70);

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

                state = TURN;
                gyrosensor.reset();
                break;
            }
            else if((cur_dis > target_dis) && (grid_count >= (GRID_NUM-1)))
            {
                state = END;
            }
            break;

        case END:

            constant.constant_run(true , true);
            distance.Distance_reset();
            direction.Direction_init();
            flag = true;
            break;

        default:
            break;
    }
    return flag;
    
}