#include "DebrisScene.h"

DebrisScene::DebrisScene():
    colorSensor(PORT_2){
    }

//デブリ用の新たな関数（app.cppに呼ばれる）
//Debris.hにデブリ攻略に必要な関数を呼ぶ
void DebrisScene::scene_debris(float distance,float leftdistance,float rightdistance ){
    debris.run(0.097,0.051,0.0014,30,edge);
    printf("デブリ攻略シーン関数\n");
}
