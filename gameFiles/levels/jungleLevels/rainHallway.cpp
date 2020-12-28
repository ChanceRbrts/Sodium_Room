#include "rainHallway.h"

RainHallwayEnclosed::RainHallwayEnclosed() : Level(){
    filePath = "jungleLevels/rainhallway_enc";
    a1 = nullptr;
    a2 = nullptr;
    a3 = nullptr;
    anim = 0;
    maxAnim = 60;
    hasBackground = true;
    r = 0.25;
    g = 0.25;
    b = 0.25;
}

std::vector<Instance *> RainHallwayEnclosed::makeLevel(std::vector<Instance*> previous){
    previous.push_back(new Rain(21, 0, 8, 0));
    previous.push_back(new Grate(21, 5, 8));
    previous.push_back(new Rain(45, 0, 8, 0));
    previous.push_back(new Grate(45, 5, 8));
    previous.push_back(new Rain(69, 0, 8, 0));
    previous.push_back(new Grate(69, 5, 8));
    return previous;
}

void RainHallwayEnclosed::demakeLevel(){
    a1 = nullptr;
    a2 = nullptr;
    a3 = nullptr;
}

std::vector<Arc *> RainHallwayEnclosed::createArcs(){
    std::vector<Arc *> arcs;
    a1 = new Arc(25, 14, 15, -M_PI*5/8, -M_PI*3/8, 1, 0, 0, true);
    arcs.push_back(a1);
    // This spans in between 1/4PI and 1/3PI, so 7/48PI
    a2 = new Arc(49, 14, 15, -M_PI*41/96, -M_PI*55/96, 1, 0, 0, true);
    arcs.push_back(a2);
    a3 = new Arc(73, 14, 15, -M_PI*2/6, -M_PI*4/6, 1, 0, 0, true);
    arcs.push_back(a3);
    return arcs;
}

void RainHallwayEnclosed::updateLevel(double deltaTime, Instance* player){
    // The arcs will go back and forth on cyclic timers.
    anim = fmod(anim+deltaTime, maxAnim);
    // Arc 1 will have a 5 second timer.
    double a1Angle = -M_PI/2+M_PI/3*sin(2*M_PI*anim/5);
    a1->setAngle(a1Angle-M_PI*7/96, a1Angle+M_PI*7/96);
    // Arc 2 will have a 4 second timer.
    double a2Angle = -M_PI/2+M_PI/3*sin(M_PI*anim/2);
    a2->setAngle(a2Angle-M_PI/8, a2Angle+M_PI/8);
    // Arc 3 will have a 3 second timer.
    double a3Angle = -M_PI/2+M_PI/3*sin(2*M_PI*anim/3);
    a3->setAngle(a3Angle-M_PI/7, a3Angle+M_PI/7);
}

RainHallwayLevel::RainHallwayLevel() : Level(){
    filePath = "jungleLevels/rainhallway";
    enclosed = nullptr;
    a = nullptr;
    move = 0;
    maxMove = 1;
    floorOne = nullptr;
    floorTwo = nullptr;
    pastPoint = false;
}

std::vector<Instance *> RainHallwayLevel::makeLevel(std::vector<Instance*> previous){
    previous.push_back(new Player(1, 4));
    previous.push_back(new Rain(14, 0, 8, 29, 1));
    previous.push_back(new Grate(14, 5, 8));
    enclosed = new RainHallwayEnclosed();
    previous.push_back(new EnclosedLevel(10, 0, 0, 15, enclosed));
    previous.push_back(new Button(5, 13, 0, "rainhall_open", 2));
    return previous;
}

std::vector<Arc *> RainHallwayLevel::createArcs(){
    std::vector<Arc *> arcs;
    a = new Arc(12, 8, 8, -M_PI/8, M_PI/8, 0.25, 0.25, 0.25, true);
    arcs.push_back(a);
    return arcs;
}

std::vector<CameraObject *> RainHallwayLevel::createCameraObjects(){
    std::vector<CameraObject *> camObjs;
    floorOne = new OneWayCameraObject(1, 15, 28, 0);
    floorTwo = new OneWayCameraObject(1, 15, 28, -128, 0, 0, false);
    pastPoint = false;
    camObjs.push_back(floorOne);
    camObjs.push_back(new OneWayCameraObject(10.01, 1, 13, 0, -64, 3, true));
    camObjs.push_back(new OneWayCameraObject(30, 0, 15, 1));
    return camObjs;
}

void RainHallwayLevel::updateLevel(double deltaTime, Instance* player){
    if (a == nullptr) return;
    if (GameState::getSaveB("rainhall_open") && move < maxMove){
        move += deltaTime;
        if (move > maxMove) move = maxMove;
    } else if (!GameState::getSaveB("rainhall_open") && move > 0){
        move -= deltaTime;
        if (move < 0) move = 0;
    }
    double baseDeg = -M_PI*move/maxMove;
    a->setAngle(baseDeg-M_PI/8, baseDeg+M_PI/8);
    if (player->x > getXOff()+w-18*32) GameState::setSaveI("rainhall_open", 0);
    // Swap out the floor camera object if the player goes within the right edge of the level.
    bool prevPastPoint = pastPoint;
    pastPoint = player->x > getXOff()+w-640;
    if (prevPastPoint != pastPoint){
        if (pastPoint){
            camObjs[0] = floorTwo;
            floorTwo->setPosValues(floorOne);
        } else {
            camObjs[0] = floorOne;
            floorOne->setPosValues(floorTwo);
        }
    }
}

void RainHallwayLevel::demakeLevel(){
    a = nullptr;
    // Delete the interchangeable camera objects.
    if (pastPoint) delete floorOne; 
    else delete floorTwo;
    floorOne = nullptr;
    floorTwo = nullptr;
}
