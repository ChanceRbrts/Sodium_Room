#include "hubBasement.h"

HubBasement::HubBasement(){
    darkRoom = nullptr;
    filePath = "mainLevels/hubBasement";
}

std::vector<Instance *> HubBasement::makeLevel(std::vector<Instance*> previous){
    return previous;
}

std::vector<CameraObject *> HubBasement::createCameraObjects(){
    std::vector<CameraObject *> cams;
    return cams;
}

std::vector<ShaderBox *> HubBasement::createShaderBoxes(GLUtil* glu){
    std::vector<ShaderBox *> shades;
    double wid = glu->draw->getWidth();
    darkRoom = new LongShaderbox(getXOff(), wid/64, getYOff(), wid/32, w/32-wid/64, h/32, "", "hub/fireplace", glu);
    darkRoom->addUniform("fireX", 384);
    darkRoom->addUniform("fireY", 416);
    darkRoom->addUniform("h", h);
    darkRoom->setReplaceWithArc(true);
    shades.push_back(darkRoom);
    return shades;
}

void HubBasement::updateLevel(double deltaTime, Instance* player){
    // The First Floor is always loaded in when this level is loaded in.
    double alpha = GameState::getSaveD("hubFire_transparency");
    double dark = GameState::getSaveD("hubFire_dark");
    darkRoom->addUniform("backA", 0.05+dark*(0.65-0.1*alpha));
    darkRoom->addUniform("fireA", pow(dark, 0.25)*(0.7-0.2*alpha));
    darkRoom->addUniform("fireR", pow(dark, 0.25)*128);
    darkRoom->addUniform("camX", darkRoom->getX());
    darkRoom->addUniform("camY", darkRoom->getY());
}
