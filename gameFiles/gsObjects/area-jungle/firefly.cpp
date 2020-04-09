#include "firefly.h"

Firefly::Firefly(double X, double Y, Arc* l, void (*upd)(double, Firefly*)) : Instance(X, Y, 1/32.0, 1/32.0){
    solid = false;
    maxRadius = l->getR();
    light = l;
    updatePos = upd;
}

void Firefly::draw(GLDraw* gld, GLShaders* gls){
    // The arc will draw around the radius, so let's just draw this as a point.
    gld->begin("POINTS");
    gld->color(1, 1, 1);
    gld->vertW(x+w/2, y+h/2);
    gld->end();
}

void Firefly::update(double deltaTime, bool* keyPressed, bool* keyHeld, Instance* player){
    updatePos(deltaTime, this);
    updateArc(deltaTime);
}

void Firefly::updateArc(double deltaTime){
    light->setPosition(x+dX*deltaTime, y+dY*deltaTime);
    light->setR(maxRadius*wide/maxWide);
}

void Firefly::defaultBehavior(double deltaTime, Firefly* me){}
