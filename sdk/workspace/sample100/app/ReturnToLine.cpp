#include "ReturnToLine.h"

ReturnToLineClass::ReturnToLineClass():
colorSensor(PORT_2){
}

int ReturnToLineClass::return_to_line(){
    //------------------------------
    //カラーセンサからRGB値を取得
    //------------------------------
    colorSensor.getRawColor(rgb_val);
    //---------------------------------
    //HSV値取得
    //---------------------------------
    out=hsv.hsv_calculate(rgb_val);

    printf("E out.H %f\n", out.H);
    printf("E out.S %f\n", out.S);
    printf("E out.V %f\n", out.V);

    //------------------------------
    //赤紫色でフラグを立てる(距離をリセットする為)
    //------------------------------
    if(80 >= out.S && out.S >= 65 && 50 >= out.V && out.V >= 10){
        flg = 1;
    }

    if( 10 >= out.V && flg == 1){
        if(edge == -1){
            edge = 1;
        }else if(edge == 1){
            edge = -1;
        }
        flg = 0;
    }

    printf("edge %d\n", edge);
    return edge;
}