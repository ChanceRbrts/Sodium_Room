#include "instanceCreator.h"

InstCreate::InstCreate() : Instance(0, 0, 1, 1){}

void InstCreate::draw(GLDraw* gld, GLShaders* gls){}

void InstCreate::addInstance(Instance* i){
    toAdd.push_back(i);
}
