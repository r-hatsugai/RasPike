#include "EdgeExchange.h"
#include <stdio.h>

//-------------------------------
//変数宣言
//-------------------------------
int count = 0;
int edge = -1;

int count2 = 0;
int count3 = 0;

int flg = 0;
int edgef = -1;

int EdgeExchange(HSV out, float distance){

    //------------------------------
    //青線でエッジ切り替え条件分岐
    //------------------------------
    if(33 <= out.S && 40 <= out.V){
        count += 1;
    }

    /*青63　　　　　　　　　青白43　　青白55　　　　　　　　　　青38,37*/
    if(64 >= out.S && out.S >= 41 && 55 >= out.V && out.V >= 36){
        count2 += 1;
    }
    /*80,71,28,10*/
    if(80 >= out.S && out.S >= 45 && 30 >= out.V && out.V >= 10){
        count3 += 1;
    }

    /*青線１ 30 90 5,12*/
    if(1 <= count3 && count3 <= 12){
        edge = 1;
    }
    
    /*青線２ 90 180 12,22*/
    
    if(12 < count3 && count3 <= 22){
        edge = -1;
    }
    

    /*青線３ 180 310 22,30*/
    if(22 < count3 && count3 <= 28){
        edge = 1;
    }

     /*青線４ 310 390 30,38*/
    if(28 < count3 && count3 <= 38){
        edge = -1;
    }

    //printf("edge %d\n", edge);
    //printf("count(増加) %d\n", count);

    printf("count(青白線) %d\n", count2);
    printf("count(黒青線) %d\n", count3);

    //printf("走行距離 %f\n", distance);

    // 青検知後の黒でエッジ切り替え
    if(80 >= out.S && out.S >= 72 && 50 >= out.V && out.V >= 10){
        flg = 1;
    }

    if( 10 >= out.V && flg == 1){
        if(edgef == -1){
            edgef = 1;
        }else if(edgef == 1){
            edgef = -1;
        }
        flg = 0;
    }

    printf("edgef %d\n", edgef);

    return edgef;
}