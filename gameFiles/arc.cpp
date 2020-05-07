#include "arc.h"

Arc::Arc(double X, double Y, double R, double D1, double D2, double RC, double GC, double BC, bool mono){
    x = X*32;
    y = Y*32;
    r = R*32;
    maxR = r;
    d1 = D1;
    d2 = D2;
    connected = true;
    shade = nullptr;
    rCol = RC;
    gCol = GC;
    bCol = BC;
    monocolor = mono;
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
    d1 = fmod(D1+3*M_PI, M_PI*2)-M_PI;
    d2 = fmod(D2+3*M_PI, M_PI*2)-M_PI;
}

void Arc::draw(GLUtil* glu){
    // printf("%f, %f, %f!\n", x, y, r);
    if (shade == nullptr){
        shade = new ShaderBox(0, 0, maxR*1.1/16, maxR*1.1/16, "", "arc", glu);
    }
    shade->addUniform("x", x);
    shade->addUniform("y", y);
    shade->addUniform("rad", r);
    shade->addUniform("d1", d1);
    shade->addUniform("d2", d2);
    shade->addUniform("r", rCol);
    shade->addUniform("g", gCol);
    shade->addUniform("b", bCol);
    shade->addUniform("xScale", 1);
    shade->addUniform("yScale", 1);
    shade->addUniform("camX", glu->draw->camX);
    shade->addUniform("camY", glu->draw->camY);
    shade->addUniform("unitX", 2/glu->draw->getWidth());
    shade->addUniform("unitY", -2/glu->draw->getHeight());
    shade->addUniform("mono", monocolor);
    shade->moveShaderBox(x-maxR*1.1, y-maxR*1.1);
}

void Arc::setColor(double R, double G, double B){
    rCol = (R <= 1 && R >= 0) ? R : rCol;
    gCol = (G <= 1 && G >= 0) ? G : gCol;
    bCol = (B <= 1 && B >= 0) ? B : bCol;
}

ArcInfo Arc::getInfo(int id){
    return (ArcInfo){id, rCol, gCol, bCol, monocolor};
}
