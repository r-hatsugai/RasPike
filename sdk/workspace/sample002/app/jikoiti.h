#ifndef JIKOITI_H
#define JIKOITI_H

#include "GyroSensor.h"

using namespace ev3api;// <4>

class jikoiti{
public:
    jikoiti();
    GyroSensor gyroSensor;
};
#endif