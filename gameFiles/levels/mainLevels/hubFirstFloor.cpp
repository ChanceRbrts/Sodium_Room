#include "hubFirstFloor.h"

HubFirstFloor::HubFirstFloor() : Level(){
    filePath = "mainLevels/hubFirstFloor";
    newAlpha = 0.5;
    prevAlpha = 0.5;
    maxAnim = 1/15.0;
    darkRoom = nullptr;
    dark = GameState::getSaveB("hubFire") ? 1 : 0;
    anim = maxAnim;
}

void HubFirstFloor::updateLighting(double deltaTime){
    // Change the darkness first if necessary.
    bool dk = GameState::getSaveB("hubFire");
    if (dk && dark < 1){
        dark += deltaTime;
        if (dark > 1) dark = 1;
    } else if (!dk && dark > 0){
        dark -= deltaTime;
        if (dark < 0) dark = 0;
    }
    if (dark == 0) return;
    anim += deltaTime;
    // Taken from the lighter code, with some of the numbers skewed.
    if (anim >= maxAnim){
        GameState::setSaveD("hubFire_transparency", newAlpha);
        prevAlpha = newAlpha;
        double alphaPart = rand()*1.0/RAND_MAX;
        newAlpha = pow(alphaPart, 0.25);
        anim = 0;
    } else {
        // Let's do a sinusoildal regression; it should look natural?
        double avg = (prevAlpha+newAlpha)/2;
        double sinSize = (newAlpha-prevAlpha)/2;
        // This goes from prevAlpha to newAlpha; sin goes from 1 to -1.
        double nAlpha = avg-sinSize*sin(M_PI*anim/maxAnim);
        GameState::setSaveD("hubFire_transparency", nAlpha);
    }
}

std::vector<Instance *> HubFirstFloor::makeLevel(std::vector<Instance*> previous){
    previous.push_back(new Player(5, 13));
    previous.push_back(new Fireplace(11, 12, "hubFire"));
    return previous;
}

std::vector<CameraObject *> HubFirstFloor::createCameraObjects(){
    std::vector<CameraObject *> cam;
    cam.push_back(new OneWayCameraObject(0, h/32, w/32, 0));
    return cam;
}

std::vector<ShaderBox *> HubFirstFloor::createShaderBoxes(GLUtil* glu){
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

void HubFirstFloor::updateLevel(double deltaTime, Instance* player){
    // GameState::setSaveD("fireplace_transparency", 0.5);
    updateLighting(deltaTime);
    GameState::setSaveD("hubFire_dark", dark);
    double alpha = GameState::getSaveD("hubFire_transparency");
    darkRoom->addUniform("backA", 0.05+dark*(0.65-0.1*alpha));
    darkRoom->addUniform("fireA", pow(dark, 0.25)*(0.7-0.2*alpha));
    darkRoom->addUniform("fireR", pow(dark, 0.25)*128);
    darkRoom->addUniform("camX", darkRoom->getX());
    darkRoom->addUniform("camY", darkRoom->getY());
}
