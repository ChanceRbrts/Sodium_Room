#include "mothEscort.h"

MothEscort::MothEscort(){
    filePath = "jungleLevels/moth_escort";
}

std::vector<Instance *> MothEscort::makeLevel(std::vector<Instance*> previous){
    return previous;
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
    arcs.push_back(new Arc(7, 2, 2, -M_PI, M_PI, 1.1, 1.1, 1.1, false));
    arcs.push_back(new Arc(5, 13, 2, -M_PI, M_PI, 1.3, 1.3, 1.3, false));
    return arcs;
}