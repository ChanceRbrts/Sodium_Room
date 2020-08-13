#include "arc.h"

Arc::Arc(double X, double Y, double R, double D1, double D2, double RC, double GC, double BC, bool mono){
    x = X*32;
    y = Y*32;
    r = R*32;
    maxR = r;
    d1 = D1;
    d2 = D2;
    connected = true;
    rCol = RC;
    gCol = GC;
    bCol = BC;
    alpha = 1;
    monocolor = mono;
    defBehavior = false;
}

Arc::~Arc(){
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

void Arc::draw(GLUtil* glu, ShaderBox* mainTex, DualSBox drawTo, int fromTex, int fromAlpha){
    // printf("%f, %f, %f!\n", x, y, r);
    /*
    if (shade == nullptr){
        shade = new ShaderBox(0, 0, maxR*1.1/16, maxR*1.1/16, "", "arc", glu);
    }
    */
    // Set the uniform values.
    mainTex->addUniform("x", x);
    mainTex->addUniform("y", y);
    mainTex->addUniform("rad", r);
    mainTex->addUniform("d1", d1);
    mainTex->addUniform("d2", d2);
    mainTex->addUniform("r", rCol);
    mainTex->addUniform("g", gCol);
    mainTex->addUniform("b", bCol);
    mainTex->addUniform("a", alpha);
    mainTex->addUniform("xScale", 1);
    mainTex->addUniform("yScale", 1);
    mainTex->addUniform("camX", glu->draw->camX);
    mainTex->addUniform("camY", glu->draw->camY);
    mainTex->addUniform("unitX", 2/glu->draw->getWidth());
    mainTex->addUniform("unitY", -2/glu->draw->getHeight());
    mainTex->addUniform("mono", monocolor);
    mainTex->addUniformI("prevTex", 1);
    mainTex->addUniformI("prevAlpha", 2);
    mainTex->addUniform("alphaTex", false);
    // Actually draw the arc onto the drawTo shaderbox.
    glu->draw->color(1, 1, 1, 1);
    drawTo.first->drawOnBox();
    glu->draw->enableTextures();
    glu->draw->bindTexture(fromTex, 1);
    glu->draw->bindTexture(fromAlpha, 2);
    mainTex->draw();
    drawTo.first->drawOutBox();
    mainTex->addUniform("alphaTex", true);
    drawTo.second->drawOnBox();
    glu->draw->enableTextures();
    glu->draw->bindTexture(fromTex, 1);
    glu->draw->bindTexture(fromAlpha, 2);
    mainTex->draw();
    drawTo.second->drawOutBox();
    // shade->moveShaderBox(x-maxR*1.1, y-maxR*1.1);
}

void Arc::setColor(double R, double G, double B){
    rCol = R >= 0 ? R : rCol;
    gCol = G >= 0 ? G : gCol;
    bCol = B >= 0 ? B : bCol;
}

void Arc::setAlpha(double A){
    alpha = A > 1 ? 1 : (A < 0 ? 0 : A);
}

void Arc::makeDefault(){
    defBehavior = true;
}

ArcInfo Arc::getInfo(int id){
    return (ArcInfo){id, rCol, gCol, bCol, monocolor, defBehavior};
}
