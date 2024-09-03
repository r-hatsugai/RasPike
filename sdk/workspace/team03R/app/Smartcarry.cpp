#include "Smartcarry.h"
#include <unistd.h>


#define GRID_NUM 3

typedef enum{
    TURN,//目標座標の方向へ向くまで旋回
    MOVE,//目標座標に到達するまで前進
    END  //構造体に格納される座標
}RUN_STATE;

struct GRID_XY{
    int gridX;
    int gridY;
};

Smartcarry::Smartcarry():
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

void Smartcarry::init() {
  init_f("smartcarry");
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

bool Smartcarry::smart_carry(float leftdistance, float rightdistance)
{
    bool flag = true;
    //-------------------------------------------
    //目標座標の設定
    //------------------------------------------
    static RUN_STATE state = TURN;
    struct GRID_XY target_grid[GRID_NUM] = {{1,0},
                                            {2,0},
                                            {2,-3},
                                            };//(y軸,x軸)

    //-------------------------------------------
    //目標座標までの距離、方位を格納
    //-------------------------------------------
    coordinate.Grid_setdistance(cur_gridX, cur_gridY, target_grid[grid_count].gridX,target_grid[grid_count].gridY);
    coordinate.Grid_setdirection(cur_gridX, cur_gridY, target_grid[grid_count].gridX,target_grid[grid_count].gridY);
    //現在地からの目標距離取得
    target_dis = coordinate.Grid_getdistance();
    //現在地からの目標方位取得
    target_dir = coordinate.Grid_getdirection();

    direction.Direction_r_update(leftdistance,rightdistance);
    //現在の距離取得
    cur_dis = distance.Distance_calculate();
    //現在の方位取得
    cur_dir = direction.Get_direction();  

    switch(state){
        case TURN:
            if(cur_dir < target_dir)
            {
                //右回転
                constant.pid_l_turn(55 , -55);
            }
            else if(cur_dir > target_dir)
            {
                //左回転
                constant.pid_r_turn(-55 , 55);//46
            }

            if((cur_dir > (target_dir-1.0)) && (cur_dir < (target_dir+1.0)))
            {
                gyrosensor.reset();
                sleep(500*1000);//4*1000
                flag = true;
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
                state = TURN;
                gyrosensor.reset();
                distance.Distance_reset();
                flag = true;
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
            flag = false;
            break;

        default:
            break;
    }
    return flag;
}

bool Smartcarry::back_run(float distance)
{
    bool flag = true;

    if(distance  > -100)
    {
        constant.constant_run(-50 , -50);
    }
    else if(distance < -100)
    {
        constant.constant_run(0 , 0);
        flag = false;
    }

    return flag;
}

bool Smartcarry::goal_run(float leftdistance, float rightdistance)
{
    bool flag = false;
    //-------------------------------------------
    //目標座標の設定
    //------------------------------------------
    static RUN_STATE state = TURN;
    struct GRID_XY target_grid[GRID_NUM] = {{0 , 1},
                                            {-1 , 1},
                                            {-3 , 1},
                                            };//(y軸,x軸)

    //-------------------------------------------
    //目標座標までの距離、方位を格納
    //-------------------------------------------
    coordinate.Grid_setdistance(cur_gridX, cur_gridY, target_grid[grid_count].gridX,target_grid[grid_count].gridY);
    coordinate.Grid_setdirection(cur_gridX, cur_gridY, target_grid[grid_count].gridX,target_grid[grid_count].gridY);
    //現在地からの目標距離取得
    target_dis = coordinate.Grid_getdistance();
    //現在地からの目標方位取得
    target_dir = coordinate.Grid_getdirection();

    direction.Direction_r_update(leftdistance,rightdistance);
    //現在の距離取得
    cur_dis = distance.Distance_calculate();
    //現在の方位取得
    cur_dir = direction.Get_direction();  

    switch(state){
        case TURN:
            if(cur_dir < target_dir)
            {
                //右回転
                constant.pid_l_turn(55 , -55);
            }
            else if(cur_dir > target_dir)
            {
                //左回転
                constant.pid_r_turn(-60 , 55);//46
            }

            if((cur_dir > (target_dir-1.0)) && (cur_dir < (target_dir+1.0)))
            {
                gyrosensor.reset();
                sleep(500*1000);//4*1000
                flag = false;
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
                state = TURN;
                gyrosensor.reset();
                distance.Distance_reset();
                flag = false;
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
            flag = false;
            break;

        default:
            break;
    }
    return flag;
}