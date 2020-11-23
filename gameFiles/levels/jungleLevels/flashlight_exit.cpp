#include "flashlight_exit.h"

FlashlightExit::FlashlightExit(){
    filePath = "jungleLevels/flashlightexit";
    enclosed = new BasicLevel("jungleLevels/flashlightexit_void", 0, 0);
}

std::vector<Instance *> FlashlightExit::makeLevel(std::vector<Instance*> previous){
    previous.push_back(new EnclosedLevel(5, 5, 0, 28, enclosed));
    return previous;
}
