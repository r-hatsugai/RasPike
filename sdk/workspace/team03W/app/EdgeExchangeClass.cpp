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

    printf("H:%f\n", out.H);
    printf("S:%f\n", out.S);
    printf("V:%f\n", out.V);

    //------------------------------
    //青線でエッジ切り替え条件分岐
    //if(89 >= out.S && out.S >= 60 && 30 >= out.V && out.V >= 12){
    //------------------------------
    if(85 >= out.S && out.S >= 70 && 35 >= out.V && out.V >= 20){
        flg = 1;
        printf("青色検知\n");
    }

    if(10 >= out.V && flg == 1){
        if(edge == -1){
            edge = 1;
        }else if(edge == 1){
            edge = -1;
        }
        flg = 0;
        printf("黒色検知\n");
    }

    printf("edge %d\n", edge);

    return edge;
}

int EdgeExchangeClass::edge_past(){
    return firstEdge;
}