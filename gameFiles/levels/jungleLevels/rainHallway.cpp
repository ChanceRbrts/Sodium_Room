#include "rainHallway.h"

RainHallwayLevel::RainHallwayLevel() : Level(){
    filePath = "jungleLevels/rainhallway";
    a1 = nullptr;
    a2 = nullptr;
    a3 = nullptr;
    anim = 0;
    maxAnim = 60;
}

std::vector<Instance *> RainHallwayLevel::makeLevel(std::vector<Instance*> previous){
    previous.push_back(new Player(1, 4));
    previous.push_back(new Rain(12, 0, 8, 0));
    previous.push_back(new Grate(12, 5, 8));
    previous.push_back(new Rain(36, 0, 8, 0));
    previous.push_back(new Grate(36, 5, 8));
    previous.push_back(new Rain(60, 0, 8, 0));
    previous.push_back(new Grate(60, 5, 8));
    previous.push_back(new Rain(85, 0, 8, 1));
    previous.push_back(new Grate(85, 5, 8));
    return previous;
}

std::vector<Arc *> RainHallwayLevel::createArcs(){
    std::vector<Arc *> arcs;
    a1 = new Arc(16, 14, 15, -M_PI*5/8, -M_PI*3/8, 1, 0, 0, true);
    arcs.push_back(a1);
    // This spans in between 1/4PI and 1/3PI, so 7/48PI
    a2 = new Arc(40, 14, 15, -M_PI*41/96, -M_PI*55/96, 1, 0, 0, true);
    arcs.push_back(a2);
    a3 = new Arc(64, 14, 15, -M_PI*2/6, -M_PI*4/6, 1, 0, 0, true);
    arcs.push_back(a3);
    return arcs;
}

void RainHallwayLevel::updateLevel(double deltaTime, Instance* player){
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
