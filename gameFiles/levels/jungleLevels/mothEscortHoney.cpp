#include "mothEscortHoney.h"

MothEscortHoney:: MothEscortHoney() : Level(){
    filePath = "jungleLevels/moth_escort_honey";
    lightOffTime = 0;
    maxLightOffTime = 5;
}

std::vector<Instance *> MothEscortHoney::makeLevel(std::vector<Instance*> previous){
    previous.push_back(new HoneyPlatform(15, 21.5, 3, 0, 0.5, 1, false));
    previous.push_back(new HoneyPlatform(31, 21.5, 3, false));
    previous.push_back(new MothBlocks(2, 13, "jungleLevels/mothblocks_rightstair"));
    previous.push_back(new Key(40, 15, "flashlight_piece_4"));
    return previous;
}

void MothEscortHoney::demakeLevel(){
    light = nullptr;
}

std::vector<CameraObject *> MothEscortHoney::createCameraObjects(){
    std::vector<CameraObject *> camObjs;
    camObjs.push_back(new OneWayCameraObject(0, 10, h/32-12, 3));
    camObjs.push_back(new OneWayCameraObject(w/32, 10, h/32-12, 1));
    return camObjs;
}

std::vector<Arc *> MothEscortHoney::createArcs(){
    std::vector<Arc *> arcs;
    arcs.push_back(new Arc(23.5, 25, 9, -M_PI/8, 0, 0, 0.5, 1, true));
    arcs.push_back(new Arc(3.5, 17.5, 2, -M_PI, M_PI, 1.1, 1.1, 1.1, false));
    arcs.push_back(new Arc(17.5, 23.5, 2, -M_PI, M_PI, 1.1, 1.1, 1.1, false));
    arcs.push_back(new Arc(37.5, 17.5, 2, -M_PI, M_PI, 1.3, 1.3, 1.3, false));
    arcs.push_back(new Arc(20, 5.5, 3, -M_PI*5/8, -M_PI*3/8, 0, 1, 0, true));
    return arcs;
}

void MothEscortHoney::updateLevel(double deltaTime, Instance* player){
    
}
