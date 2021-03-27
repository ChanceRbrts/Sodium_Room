#include "jungleMap.h"

JungleMap::JungleMap(int sID) : Map(sID){
    addLevel(new RainHallwayLevel(), 0, 0);
    addLevel(new FlashlightExit(), -7, 15);
    addLevel(new FlashlightArea(), -27, 15);
    addLevel(new FlashlightUpperArea(), -30, 0);
    addLevel(new FlashlightLowerArea(), -27, 30);
    addLevel(new MothEscort(), -60, 30);
    addLevel(new GrowFruit(), 25, 15);
    addLevel(new MothEscortHoney(), -33, 45);
    addLevel(new BasicLevel("jungleLevels/underpass", 0, 0), 25, 34);
    addLevel(new MothEscort2(), 93, 39);
    addLevel(new BrokenAscend(), 64, 13);
    addLevel(new TreeRoom(), 30, 0);
    addLevel(new LightBoxEscort(), 85, 0);
}
