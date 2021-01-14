#include "flashlight_area.h"

FlashlightArea::FlashlightArea() : Level(){
    filePath = "jungleLevels/flashlight_area";
}

std::vector<Instance *> FlashlightArea::makeLevel(std::vector<Instance*> previous){
    previous.push_back(new FlashlightPodium(9, 13));
    return previous;
}

std::vector<CameraObject *> FlashlightArea::createCameraObjects(){
    std::vector<CameraObject *> camObjs;
    camObjs.push_back(new OneWayCameraObject(1, 15, w/32-2, 0));
    camObjs.push_back(new OneWayCameraObject(0, 3, h/32-6, 3));
    camObjs.push_back(new OneWayCameraObject(w/32, 3, h/32-6, 1));
    return camObjs;
}

FlashlightUpperArea::FlashlightUpperArea() : Level(){
    filePath = "jungleLevels/flashlight_upperarea";
}

std::vector<Instance *> FlashlightUpperArea::makeLevel(std::vector<Instance*> previous){
    previous.push_back(new Rain(4, 1, 4, 24, 2));
    return previous;
}

std::vector<CameraObject *> FlashlightUpperArea::createCameraObjects(){
    std::vector<CameraObject *> camObjs;
    camObjs.push_back(new OneWayCameraObject(1, 15, w/32-2, 0, 0, 0, true));
    return camObjs;
}

FlashlightLowerArea::FlashlightLowerArea() : Level(){
    filePath = "jungleLevels/flashlight_lowerarea";
}

std::vector<Instance *> FlashlightLowerArea::makeLevel(std::vector<Instance*> previous){
    previous.push_back(new Rain(12, 8, 4, 12, 0));
    previous.push_back(new Grate(12, 10, 4));
    return previous;
}

std::vector<CameraObject *> FlashlightLowerArea::createCameraObjects(){
    std::vector<CameraObject *> camObjs;
    camObjs.push_back(new OneWayCameraObject(w/32, 3, 9, 1));
    camObjs.push_back(new OneWayCameraObject(14, 12, 4, 0));
    return camObjs;
}
