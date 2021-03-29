#include "flashlight_exit.h"

FlashlightExit::FlashlightExit() : Level(){
    filePath = "jungleLevels/flashlightexit";
    enclosed = nullptr;
}

std::vector<Instance *> FlashlightExit::makeLevel(std::vector<Instance*> previous){
    enclosed = new BasicLevel("jungleLevels/flashlightexit_void", 0, 0, 0.4, 0.4, 0.4);
    previous.push_back(new EnclosedLevel(5, 5, 0, 28, enclosed));
    previous.push_back(new FlashlightCharger(17, 33, 0));
    return previous;
}

void FlashlightExit::demakeEnd(){
    delete enclosed;
}

std::vector<CameraObject *> FlashlightExit::createCameraObjects(){
    std::vector<CameraObject *> camObjs;
    camObjs.push_back(new OneWayCameraObject(1, 15, w/32-8, 0));
    camObjs.push_back(new OneWayCameraObject(0, 17, 5, 3));
    camObjs.push_back(new OneWayCameraObject(10, 35, 15, 0));
    return camObjs;
}
