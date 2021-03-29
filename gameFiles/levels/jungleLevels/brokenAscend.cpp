#include "brokenAscend.h"

BrokenAscend::BrokenAscend() : Level() {
    filePath = "jungleLevels/broken_ascend";
    layer1 = new BasicLevel("jungleLevels/broken_ascend_layer1", 0, 0, 0.4, 0.4, 0.4);
    layer2 = new BasicLevel("jungleLevels/broken_ascend_layer2", 0, 0, 1, 0, 0);
    layer3 = new BasicLevel("jungleLevels/broken_ascend_layer3", 0, 0, 0, 1, 0);
    layer4 = new BasicLevel("jungleLevels/broken_ascend_layer4", 0, 0, 0, 0, 1);
}

std::vector<Instance *> BrokenAscend::makeLevel(std::vector<Instance*> previous){
    previous.push_back(new EnclosedLevel(2, 15, 20, 0, layer1));
    previous.push_back(new EnclosedLevel(2, 14, 20, 0, layer2));
    previous.push_back(new EnclosedLevel(2, 13, 20, 0, layer3));
    previous.push_back(new EnclosedLevel(2, 12, 20, 0, layer4));
    return previous;
}

void BrokenAscend::demakeEnd(){
    delete layer1;
    delete layer2;
    delete layer3;
    delete layer4;
    layer1 = nullptr;
    layer2 = nullptr;
    layer3 = nullptr;
    layer4 = nullptr;
}

std::vector<CameraObject *> BrokenAscend::createCameraObjects(){
    std::vector<CameraObject *> cams;
    cams.push_back(new OneWayCameraObject(0, 2, 10, 3));
    cams.push_back(new OneWayCameraObject(2, h/32, 6, 0));
    return cams;
}
