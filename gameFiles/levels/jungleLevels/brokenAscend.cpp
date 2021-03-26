#include "brokenAscend.h"

BrokenAscend::BrokenAscend() : Level() {
    filePath = "jungleLevels/broken_ascend";
}

std::vector<Instance *> BrokenAscend::makeLevel(std::vector<Instance*> previous){
    /// TODO: Add the enclosed levels here.
    return previous;
}

std::vector<CameraObject *> BrokenAscend::createCameraObjects(){
    std::vector<CameraObject *> cams;
    cams.push_back(new OneWayCameraObject(0, 2, 10, 3));
    cams.push_back(new OneWayCameraObject(2, h/32, 6, 0));
    return cams;
}
