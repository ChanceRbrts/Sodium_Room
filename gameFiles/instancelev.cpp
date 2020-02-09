#include "instancelev.h"

InstanceLev::InstanceLev(double X, double Y, double W, double H) : Instance(X, Y, W, H){
    messWithLevel = false;
}

void InstanceLev::messWithLevels(LevelList* levs, Instance* player){}
