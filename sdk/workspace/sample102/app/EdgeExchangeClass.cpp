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

    //------------------------------
    //青線でエッジ切り替え条件分岐
    //------------------------------
    if(80 >= out.S && out.S >= 72 && 40 >= out.V && out.V >= 10){
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

    //printf("edge %d\n", edge);

    return edge;
}