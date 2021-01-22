#include "growFruit.h"

GrowFruit::GrowFruit() : Level(){
    filePath = "jungleLevels/growFruit";
}

std::vector<Instance *> GrowFruit::makeLevel(std::vector<Instance*> previous){
    return previous;
}

std::vector<CameraObject *> GrowFruit::createCameraObjects(){
    std::vector<CameraObject *> camObjs;
    return camObjs;
}
