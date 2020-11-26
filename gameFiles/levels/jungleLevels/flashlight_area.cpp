#include "flashlight_area.h"

FlashlightArea::FlashlightArea() : Level(){
    filePath = "jungleLevels/flashlight_area";
}

std::vector<Instance *> FlashlightArea::makeLevel(std::vector<Instance*> previous){
    return previous;
}
