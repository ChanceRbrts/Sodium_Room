#include "hubFirstFloor.h"

HubFirstFloor::HubFirstFloor() : Level(){
    filePath = "mainLevels/hubFirstFloor";
    newAlpha = 0.5;
    prevAlpha = 0.5;
    maxAnim = 1/15.0;
    anim = maxAnim;
}

void HubFirstFloor::updateLighting(double deltaTime){
    anim += deltaTime;
    // Taken from the lighter code, with some of the numbers skewed.
    if (anim >= maxAnim){
        GameState::setSaveD("fireplace_transparency", newAlpha);
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
        GameState::setSaveD("fireplace_transparency", nAlpha);
    }
}

std::vector<Instance *> HubFirstFloor::makeLevel(std::vector<Instance*> previous){
    previous.push_back(new Player(5, 13));
    previous.push_back(new Fireplace(11, 12));
    return previous;
}

std::vector<Arc *> HubFirstFloor::createArcs(){
    std::vector<Arc *> arcs;
    return arcs;
}

std::vector<CameraObject *> HubFirstFloor::createCameraObjects(){
    std::vector<CameraObject *> cam;
    return cam;
}

std::vector<ShaderBox *> HubFirstFloor::createShaderBoxes(GLUtil* glu){
    std::vector<ShaderBox *> shades;
    double wid = glu->draw->getWidth();
    darkRoom = new LongShaderbox(0, wid/64, 0, wid/32, w/32-wid/64, h/32, "", "hub/fireplace", glu);
    darkRoom->addUniform("fireR", 128);
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
    double alpha = GameState::getSaveD("fireplace_transparency");
    darkRoom->addUniform("backA", 0.6-0.1*alpha);
    darkRoom->addUniform("fireA", 0.7-0.2*alpha);
    darkRoom->addUniform("camX", darkRoom->getX());
    darkRoom->addUniform("camY", darkRoom->getY());
    /*darkRoom->addUniform("r", color);
    darkRoom->addUniform("g", color);
    darkRoom->addUniform("b", color);*/
}
