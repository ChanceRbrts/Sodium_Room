#include "growFruit.h"

GrowFruit::GrowFruit() : Level(){
    filePath = "jungleLevels/growFruit";
}

std::vector<Instance *> GrowFruit::makeLevel(std::vector<Instance*> previous){
    previous.push_back(new Soil(5, 18, 4));
    previous.push_back(new FakeSolids(24, 0, "jungleLevels/growFruit_hidden", true));
    previous.push_back(new BouncingFruit(24, 16, false));
    // previous.push_back(new HoneyPlatform(10, 18, 4, true));
    return previous;
}

std::vector<CameraObject *> GrowFruit::createCameraObjects(){
    std::vector<CameraObject *> camObjs;
    camObjs.push_back(new OneWayCameraObject(4, 0, w/32-13, 2));
    camObjs.push_back(new OneWayCameraObject(1, h/32, w/32-8, 0));
    camObjs.push_back(new OneWayCameraObject(10, 1, w/32-17, 0, 0, 0, true));
    return camObjs;
}
