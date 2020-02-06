#include "fakeSolid.h"
#include <math.h>

FakeSolid::FakeSolid(float X, float Y) : Instance(X, Y, 1, 1){
    immovable = true;
    solid = true;
    swap = false;
    loadedShader = false;
    name = "FakeSolid";
    for (int i = 0; i < 32; i++){
        for (int j = 0; j < 32; j++){
            vertices.push_back(i);
            vertices.push_back(j);
            vertices.push_back(rand()*5.0/RAND_MAX);
            for (int k = 0; k < 32; k++){
                colors.push_back(0);
            }
            offsets.push_back(rand()*10.0/RAND_MAX-5.0);
        }
    }
    pX = 0;
    pY = 0;
    time = 0;
}

FakeSolid::~FakeSolid(){
    vertices.clear();
    colors.clear();
    offsets.clear();
}

void FakeSolid::checkShader(GLShaders* gls){
    if (!gls->programExists("fakeSolid")){
        gls->createProgram("gameFiles/shaders/fakeSolid", "", "fakeSolid");
    }
}

void FakeSolid::update(double deltaTime, bool* keyPressed, bool* keyHeld, Instance* player){
    pX = player->x;
    pY = player->y;
    time += deltaTime;
}

void FakeSolid::draw(GLDraw* gld, GLShaders* gls){
    if (!loadedShader){
        checkShader(gls);
        loadedShader = true;
    }
    int program = gls->bindShader("fakeSolid");
    pointDouble xy = gld->vPoint(x, y);
    // Get our relative coordinates.
    gls->addUniform(program, "x", x);
    gls->addUniform(program, "y", y);
    gls->addUniform(program, "playerX", pX);
    gls->addUniform(program, "playerY", pY);
    // Get our view coordinates.
    gls->addUniform(program, "displayX", xy.x);
    gls->addUniform(program, "displayY", xy.y);
    gls->addUniform(program, "unitX", 2/gld->getWidth());
    gls->addUniform(program, "unitY", -2/gld->getHeight());
    // Get our other attributes.
    gls->addUniform(program, "time", time);
    gls->addUniform(program, "proximity", solid == swap ? 0 : 1);
    int att = gls->addAttribute(program, "offset", &offsets[0], 1);
    gld->drawArray(&vertices[0], &colors[0], nullptr, vertices.size()/3, 3, 3, "POINTS");
    gls->removeAttribute(program, att);
    gls->unbindShader();
}
