#include "EdgeExchangeClass.h"

EdgeExchangeClass::EdgeExchangeClass():
colorSensor(PORT_2){
}

int EdgeExchangeClass::edge_exchange(){
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
    //青線でエッジ切り替え条件分岐
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