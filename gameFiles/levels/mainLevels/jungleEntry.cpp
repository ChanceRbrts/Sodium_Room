#include "jungleEntry.h"

JungleEntry::JungleEntry() : Level() {
    filePath = "mainLevels/jungleEntry";
}

std::vector<Instance *> JungleEntry::makeLevel(std::vector<Instance*> previous){
    previous.push_back(new Grate(1, 14, 10));
    return previous;
}

std::vector<CameraObject *> JungleEntry::createCameraObjects(){
    std::vector<CameraObject *> cams;
    cams.push_back(new OneWayCameraObject(1, 14, 59, 0));
    return cams;
}
