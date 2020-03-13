#include "fakeSolid.h"
#include <math.h>

FakeSolid::FakeSolid(float X, float Y) : Instance(X, Y, 1, 1){
    immovable = true;
    solid = true;
    swap = false;
    loadedShader = false;
    name = "FakeSolid";
    r = 0;
    g = 0;
    b = 0;
    lastR = r;
    lastG = g;
    lastB = b;
    for (int i = 0; i < 32; i++){
        for (int j = 0; j < 32; j++){
            vertices.push_back(i);
            vertices.push_back(j);
            vertices.push_back(rand()*5.0/RAND_MAX);
            for (int k = 0; k < 3; k++){
                colors.push_back(0);
            }
            offsets.push_back(rand()*10.0/RAND_MAX-5.0);
            texts.push_back(i/32.0);
            texts.push_back(j/32.0);
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
    texts.clear();
}

void FakeSolid::checkShader(GLShaders* gls){
    if (!gls->programExists("fakeSolid")){
        gls->createProgram("gameFiles/shaders/fakeSolid", "gameFiles/shaders/texturePoints", "fakeSolid");
    }
}

void FakeSolid::update(double deltaTime, bool* keyPressed, bool* keyHeld, Instance* player){
    pX = player->x;
    pY = player->y;
    time += deltaTime;
    if (abs(r-lastR) > 0.001 || abs(g-lastG) > 0.001 || abs(b-lastB) > 0.001){
        // Reset the colors of the fake solids.
        colors.clear();
        for (int i = 0; i < 32; i++){
            for (int j = 0; j < 32; j++){
                colors.push_back(r);
                colors.push_back(g);
                colors.push_back(b);
            }
        }
        lastR = r;
        lastG = g;
        lastB = b;
    }
}

void FakeSolid::draw(GLDraw* gld, GLShaders* gls){
    if (!loadedShader){
        checkShader(gls);
        loadedShader = true;
    }
    if (hasTexture){
        gld->enableTextures();
        gld->bindTexture(textureID);
        // Turns transparency on.
        gld->color(1, 1, 1, 1);
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
    int texs = gls->addAttribute(program, "texture", texts.data(), 2);
    gld->drawArray(&vertices[0], &colors[0], nullptr, vertices.size()/3, 3, 3, "POINTS");
    gls->removeAttribute(program, att);
    gls->removeAttribute(program, texs);
    gls->unbindShader();
    if (hasTexture){
      gld->bindTexture(0);
      gld->disableTextures();
   }
}

FakeSolids::FakeSolids(std::string textureMap) : InstanceLev(0, 0, 0, 0){
    // Initialize our level.
    Level* l = new Level();
    l->filePath = textureMap;
    l->createLevel();
    // Now, replace our solid map with Fake Solids!
    if (l->insts != nullptr){
        for (Instances* i = l->insts; i != nullptr; i = i->next){
            FakeSolid* fs = new FakeSolid(i->i->x/32, i->i->y/32);
            if (i->i->texID() != 0){
                fs->changeTexture(i->i->texID(), true);
            }
            toAdd.push_back(fs);
        }
    }
    // Finally, delete the old level, and this instance has served its purpose.
    delete l;
}

void FakeSolids::fUpdate(double deltaTime){
    remove = true;
}
