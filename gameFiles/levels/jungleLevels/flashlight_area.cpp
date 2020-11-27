#include "flashlight_area.h"

FlashlightArea::FlashlightArea() : Level(){
    filePath = "jungleLevels/flashlight_area";
}

std::vector<Instance *> FlashlightArea::makeLevel(std::vector<Instance*> previous){
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
