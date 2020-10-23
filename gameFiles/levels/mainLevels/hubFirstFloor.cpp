#include "hubFirstFloor.h"

HubFirstFloor::HubFirstFloor(){
    
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
    return shades;
}
