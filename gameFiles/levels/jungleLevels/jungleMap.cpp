#include "jungleMap.h"

JungleMap::JungleMap(int sID) : Map(sID){
    addLevel(new RainHallwayLevel(), 0, 0);
}
