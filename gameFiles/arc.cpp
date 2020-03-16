#include "arc.h"

Arc::Arc(double X, double Y, double R, double D1, double D2){
    x = X;
    y = Y;
    r = R;
    maxR = r;
    d1 = D1;
    d2 = D2;
}

Arc::~Arc(){
    if (shade != nullptr){
        delete shade;
    }
}

void Arc::setPosition(double X, double Y){
    x = X;
    y = Y;
}

void Arc::setR(double R){
    r = (R > maxR) ? maxR : R;
}

void Arc::setAngle(double D1, double D2){
    d1 = D1;
    d2 = D2;
}

void Arc::draw(GLUtil* glu){
    if (shade == nullptr){
        shade = new ShaderBox(0, 0, maxR, maxR, "", "", glu);
    }
    shade->addUniform("x", x);
    shade->addUniform("y", y);
    shade->addUniform("r", r);
    shade->addUniform("d1", d1);
    shade->addUniform("d2", d2);
}
