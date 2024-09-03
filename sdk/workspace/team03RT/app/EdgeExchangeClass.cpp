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
    printf("hsv.H%f\n",out.H);
    printf("hsv.S%f\n",out.S);
    printf("hsv.V%f\n",out.V);


    //------------------------------
    //青線でエッジ切り替え条件分岐
    //------------------------------
    if(83 >= out.S && out.S >= 72 && 40 >= out.V && out.V >= 15){
        flg = 1;
        printf("青色検知\n");
    }

    if(14 >= out.V && flg == 1){
        printf("黒色色検知\n");
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

int EdgeExchangeClass::edge_past(){
    return firstEdge;
}