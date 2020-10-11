#include "instancelev.h"

InstanceLev::InstanceLev(double X, double Y, double W, double H) : Instance(X, Y, W, H){
    messWithLevel = false;
}

bool InstanceLev::messWithLevels(LevelList* levs, Level* lev, Map* map, Instance* player){ return false; }

bool InstanceLev::removeMessFromWorld(LevelList* levs, Level* lev, Instance* player){ return false; }
