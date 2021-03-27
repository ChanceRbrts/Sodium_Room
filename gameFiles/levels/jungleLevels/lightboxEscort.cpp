#include "lightboxEscort.h"

LightBoxEscort::LightBoxEscort() : Level(){
    filePath = "jungleLevels/lightbox_escort";
    en1 = new BasicLevel("jungleLevels/lightbox_escort_interior", 0, 0, 0.4, 0.4, 0.4);
    en2 = new BasicLevel("jungleLevels/lightbox_escort_interior", 0, 0, 1, 0, 0);
    en3 = new BasicLevel("jungleLevels/lightbox_escort_interior", 0, 0, 0, 1, 0);
    en4 = new BasicLevel("jungleLevels/lightbox_escort_interior", 0, 0, 0, 0, 1);
}

std::vector<Instance *> LightBoxEscort::makeLevel(std::vector<Instance*> previous){
    previous.push_back(new Rain(1, 1, 3, 33, 2));
    previous.push_back(new FlashlightCharger(5, 13, AREA_JUNG));
    previous.push_back(new FlashlightCharger(26, 5, AREA_JUNG));
    previous.push_back(new FlashlightCharger(26, 13, AREA_JUNG));
    previous.push_back(new EnclosedLevel(16, 3, 0, 11, en1));
    previous.push_back(new EnclosedLevel(24, 3, 0, 11, en2));
    previous.push_back(new EnclosedLevel(32, 3, 0, 11, en3));
    previous.push_back(new EnclosedLevel(40, 3, 0, 11, en4));
    return previous;
}

std::vector<CameraObject *> LightBoxEscort::createCameraObjects(){
    std::vector<CameraObject *> cams;
    return cams;
}

std::vector<Arc *> LightBoxEscort::createArcs(){
    std::vector<Arc *> arcs;
    return arcs;
}
