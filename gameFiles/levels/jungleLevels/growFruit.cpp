#include "growFruit.h"

GrowFruit::GrowFruit() : Level(){
    filePath = "jungleLevels/growFruit";
}

std::vector<Instance *> GrowFruit::makeLevel(std::vector<Instance*> previous){
    previous.push_back(new Soil(5, 18, 4));
    previous.push_back(new FakeSolids(26, 0, "jungleLevels/growFruit_hidden", true));
    previous.push_back(new BouncingFruit(26, 16, false));
    return previous;
}

std::vector<CameraObject *> GrowFruit::createCameraObjects(){
    std::vector<CameraObject *> camObjs;
    camObjs.push_back(new OneWayCameraObject(1, h/32, w/32-2, 0));
    return camObjs;
}
