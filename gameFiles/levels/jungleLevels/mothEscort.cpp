#include "mothEscort.h"

MothEscort::MothEscort(){
    filePath = "jungleLevels/moth_escort";
    time = 0;
    maxTime = 1.25;
}

std::vector<Instance *> MothEscort::makeLevel(std::vector<Instance*> previous){
    light = new LightBox(20, 11);
    previous.push_back(light);
    previous.push_back(new Button(16, 11, 2, "mothescort_lightbox", 2));
    previous.push_back(new MothBlocks(5, 1, "jungleLevels/mothblocks"));
    return previous;
}

void MothEscort::demakeLevel(){
    light = nullptr;
}

std::vector<CameraObject *> MothEscort::createCameraObjects(){
    std::vector<CameraObject *> camObjs;
    camObjs.push_back(new OneWayCameraObject(2, h/32, w/32-2, 0));
    camObjs.push_back(new OneWayCameraObject(w/32, 6, 2, 0, 0, 1, false));
    camObjs.push_back(new OneWayCameraObject(0, 2, h/32-4, 3));
    return camObjs;
}

std::vector<Arc *> MothEscort::createArcs(){
    std::vector<Arc *> arcs;
    arcs.push_back(new Arc(6.5, 2.5, 2, -M_PI, M_PI, 1.1, 1.1, 1.1, false));
    arcs.push_back(new Arc(5.5, 12.5, 2, -M_PI, M_PI, 1.3, 1.3, 1.3, false));
    arcs.push_back(light->getArc());
    return arcs;
}

void MothEscort::updateLevel(double deltaTime, Instance* player){
    bool lightPress = GameState::getSaveB("mothescort_lightbox");
    if (lightPress && time < maxTime){
        time += deltaTime;
        if (time > maxTime) time = maxTime;
    } else if (!lightPress && time > 0){
        time -= deltaTime;
        if (time < 0) time = 0;
    }
    light->y = getYOff()+352-288*time/maxTime;
}