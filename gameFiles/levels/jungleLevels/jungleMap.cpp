#include "jungleMap.h"

JungleMap::JungleMap(int sID) : Map(sID){
    addLevel(new RainHallwayLevel(), 0, 0);
    addLevel(new FlashlightExit(), -7, 15);
    // addLevel(new FlashlightArea(), -27, 15);
}
