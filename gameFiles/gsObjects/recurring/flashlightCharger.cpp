#include "flashlightCharger.h"

FlashlightCharger::FlashlightCharger(double X, double Y, int area) : Instance(X, Y, 4, 1){
    immovable = true;
    solid = true;
    name = "Flashlight Charger";
    std::string textures[1] = {"junglecharger"};
    std::string backTex = "resources/chargers/"+textures[area]+"-back.png";
    std::string frontTex = "resources/chargers/"+textures[area]+".png";
    if (TexBook::hasTexture(frontTex)){
        frontTexture = TexBook::getTexture(frontTex);
        backTex = TexBook::getTexture(backTex);
    } else {
        frontTexture = TexBook::loadTexture(frontTex);
        backTexture = TexBook::loadTexture(backTex);
    }
}

std::vector<int> FlashlightCharger::initLayers(){
    std::vector<int> layers;
    layers.push_back(LAYER_NORMAL);
    return layers;
}

void FlashlightCharger::collided(Instance* o, double deltaTime){
    // Check if the object is a player standing on the charger.
    if (!(o->isPlayer()) || o->y > y-o->h) return;
    Player* p = (Player *)o;
    PlayerAbility* pA = p->getAbility();
    if (pA == nullptr || pA->getName() != "Flashlight") return;
    // Charge the batteries.
    Flashlight* f = (Flashlight *)pA;
    f->chargeBatteries(deltaTime);
}

void FlashlightCharger::draw(GLDraw* gld, GLShaders* gls, int layer){
    gld->color(1,1,1,1);
    gld->enableTextures();
    // Draw the background texture first...
    gld->bindTexture(backTexture);
    gld->begin("QUADS");
    gld->texCoords(0, 0);
    gld->vertW(x+6,y+12);
    gld->texCoords(0, 1);
    gld->vertW(x+6,y+28);
    gld->texCoords(1, 1);
    gld->vertW(x+w-6,y+28);
    gld->texCoords(1, 0);
    gld->vertW(x+w-6,y+12);
    gld->end();
    // Then draw the lighting in the tube where applicable...
    gld->bindTexture(0);
    // Finally, draw the main texture.
    gld->bindTexture(frontTexture);
    gld->begin("QUADS");
    gld->texCoords(0, 0);
    gld->vertW(x,y);
    gld->texCoords(0, 1);
    gld->vertW(x,y+h);
    gld->texCoords(1, 1);
    gld->vertW(x+w,y+h);
    gld->texCoords(1, 0);
    gld->vertW(x+w,y);
    gld->end();
    gld->bindTexture(0);
    gld->disableTextures();
}