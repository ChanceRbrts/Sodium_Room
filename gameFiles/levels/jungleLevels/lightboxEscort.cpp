#include "lightboxEscort.h"

LightBoxEscort::LightBoxEscort() : Level(){
    filePath = "jungleLevels/lightbox_escort";
    en1 = new BasicLevel("jungleLevels/lightbox_escort_interior", 0, 0, 0.4, 0.4, 0.4);
    en2 = new BasicLevel("jungleLevels/lightbox_escort_interior", 0, 0, 1, 0, 0);
    en3 = new BasicLevel("jungleLevels/lightbox_escort_interior", 0, 0, 0, 1, 0);
    en4 = new BasicLevel("jungleLevels/lightbox_escort_interior", 0, 0, 0, 0, 1);
    lightLower = nullptr;
    lightMiddle = nullptr;
    lightUpper = nullptr;
}

std::vector<Instance *> LightBoxEscort::makeLevel(std::vector<Instance*> previous){
    lightLower = new LightBox(10, 11.5, 2);
    lightMiddle = new LightBox(10, 7.5, 2);
    lightUpper = new LightBox(10, 3.5, 2);
    previous.push_back(lightLower);
    previous.push_back(lightMiddle);
    previous.push_back(lightUpper);
    previous.push_back(new MothBlocks(11, 2, "jungleLevels/mothblocks_rightstair"));
    previous.push_back(new Rain(1, 1, 3, 33, 2));
    previous.push_back(new FlashlightCharger(4, 13, AREA_JUNG));
    // previous.push_back(new FlashlightCharger(26, 5, AREA_JUNG));
    // previous.push_back(new FlashlightCharger(26, 13, AREA_JUNG));
    previous.push_back(new EnclosedLevel(16, 3, 0, 11, en1));
    previous.push_back(new EnclosedLevel(24, 3, 0, 11, en2));
    previous.push_back(new EnclosedLevel(32, 3, 0, 11, en3));
    previous.push_back(new EnclosedLevel(40, 3, 0, 11, en4));
    return previous;
}

void LightBoxEscort::demakeLevel(){
    lightLower = nullptr;
    lightMiddle = nullptr;
    lightUpper = nullptr;
}

std::vector<CameraObject *> LightBoxEscort::createCameraObjects(){
    std::vector<CameraObject *> cams;
    return cams;
}

std::vector<Arc *> LightBoxEscort::createArcs(){
    std::vector<Arc *> arcs;
    arcs.push_back(lightLower->getArc());
    arcs.push_back(lightMiddle->getArc());
    arcs.push_back(lightUpper->getArc());
    // y= 4.5, 8.5, 12.5
    // Start and End Points
    arcs.push_back(new Arc(11.5, 2.5, 2, -M_PI, M_PI, 1.1, 1.1, 1.1, false));
    arcs.push_back(new Arc(53.5, 12.5, 2, -M_PI, M_PI, 1.3, 1.3, 1.3, false));
    // Obstacles (To Be Replaced with Objects?)
    arcs.push_back(new Arc(20.5, 4.5, 2, -M_PI, M_PI, 1.3, 1.3, 1.3, false));
    arcs.push_back(new Arc(20.5, 8.5, 2, -M_PI, M_PI, 1.3, 1.3, 1.3, false));
    arcs.push_back(new Arc(28.5, 12.5, 2, -M_PI, M_PI, 1.3, 1.3, 1.3, false));
    arcs.push_back(new Arc(28.5, 8.5, 2, -M_PI, M_PI, 1.3, 1.3, 1.3, false));
    arcs.push_back(new Arc(36.5, 4.5, 2, -M_PI, M_PI, 1.3, 1.3, 1.3, false));
    arcs.push_back(new Arc(36.5, 12.5, 2, -M_PI, M_PI, 1.3, 1.3, 1.3, false));
    arcs.push_back(new Arc(44.5, 4.5, 2, -M_PI, M_PI, 1.3, 1.3, 1.3, false));
    arcs.push_back(new Arc(44.5, 8.5, 2, -M_PI, M_PI, 1.3, 1.3, 1.3, false));
    return arcs;
}

void LightBoxEscort::updateLevel(double deltaTime, Instance* player){
    // Lightboxes move with the player within the range of x=13-x=46, w=60.
    // The lightbox position must center with the player if possible.
    double lightBoxX = (player->x+player->w/2)-lightLower->w/2;
    double mapX = getXOff();
    if (lightBoxX < mapX+13*32) lightBoxX = mapX+13*32;
    else if (lightBoxX > mapX+w-14*32) lightBoxX = mapX+w-14*32;
    lightLower->dX = (lightBoxX-lightLower->x)/deltaTime;
    lightMiddle->dX = (lightBoxX-lightMiddle->x)/deltaTime;
    lightUpper->dX = (lightBoxX-lightUpper->x)/deltaTime;
}
