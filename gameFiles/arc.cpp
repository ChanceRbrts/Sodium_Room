#include "arc.h"

Arc::Arc(double X, double Y, double R, double D1, double D2){
    x = X;
    y = Y;
    r = R;
    maxR = r;
    d1 = D1;
    d2 = D2;
    connected = true;
}

Arc::~Arc(){
    if (shade != nullptr){
        if (connected) delete shade;
        else shade->removeMe();
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
        shade = new ShaderBox(0, 0, maxR*2, maxR*2, "", "arc", glu);
    }
    shade->addUniform("x", x);
    shade->addUniform("y", y);
    shade->addUniform("rad", r);
    shade->addUniform("d1", d1);
    shade->addUniform("d2", d2);
    shade->addUniform("r", rCol);
    shade->addUniform("g", gCol);
    shade->addUniform("b", bCol);
    shade->addUniform("camX", glu->draw->camX);
    shade->addUniform("camY", glu->draw->camY);
    shade->addUniform("unitX", 2/glu->draw->getWidth());
    shade->addUniform("unitY", -2/glu->draw->getHeight());
    shade->moveShaderBox(x-maxR, y-maxR);
}

ArcInfo Arc::getInfo(int id){
    return (ArcInfo){id, rCol, gCol, bCol};
}
