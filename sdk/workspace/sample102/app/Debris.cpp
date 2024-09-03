#include "Debris.h"


#define GRID_NUM 2

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
    }

void Debris::init() {
  init_f("Debris");
}

void Debris::debris_removal(float leftdistance, float rightdistance)
{
    //-------------------------------------------
    //時間を取得
    //-------------------------------------------
    /*nt = clock.now();
    seconds = (nt / 100000) % 1000;

    printf("現在時刻 %d\n", seconds);
    if(seconds <= 13)
    {
       constant.constant_run(-50 , -50);
    } 

    else
    {*/

    //-------------------------------------------
    //目標座標の設定
    //-------------------------------------------
    static RUN_STATE state = TURN;
    struct GRID_XY target_grid[GRID_NUM] = {
                                            {0,-1},
                                            {-3,-1},
                                            };//(y軸:gridX,x軸:gridY)

    //-------------------------------------------
    //距離、方位の初期化
    //-------------------------------------------
    // distance.Distance_reset();
    // direction.Direction_init();

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
    
        switch(state){
            case TURN:
                if(cur_dir < target_dir)
                {
                    constant.constant_run(55 , -50);
                }
                else if(cur_dir > target_dir)
                {
                    constant.constant_run(-67 , 25);
                }

                if((cur_dir > (target_dir-1.0)) && (cur_dir < (target_dir+1.0)))
                {
                    gyrosensor.reset();
                    state = MOVE;
                }
                break;

            case MOVE:
            //printf("grid_count: %d\n", grid_count);
            //printf("target_grid[grid_count]: (%d, %d)\n", target_grid[grid_count].gridX, target_grid[grid_count].gridY);

            /*if(target_grid[grid_count].gridX == 1 && target_grid[grid_count].gridY == 0)
            {
                printf("目標座標:(%d,%d)\n",target_grid[grid_count].gridX,target_grid[grid_count].gridY);
                constant.constant_run(-47 , -50); // 後進
            }
            else
            {*/
                constant.constant_run(56 , 50); // 前進
            //}
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
                break;

            default:
                break;
        }
    //}
}