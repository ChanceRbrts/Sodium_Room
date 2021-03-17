#include "flashlightCharger.h"

FlashlightCharger::FlashlightCharger(double X, double Y, int area) : Instance(X, Y, 4, 1){
    immovable = true;
    solid = true;
    name = "Flashlight Charger";
    std::string textures[1] = {"junglecharger"};
    std::string backTex = "resources/chargers/"+textures[area]+"-back.png";
    std::string frontTex = "resources/chargers/"+textures[area]+".png";
    frontTexture = TexBook::getTexture(frontTex);
    backTex = TexBook::getTexture(backTex);
    transitionTime = 0;
    maxTransitionTime = 0.5;
    cyclePoint = 0;
    visible = 0;
    visibleSpeed = 0.5;
    makeVisible = false;
    playerOnCharger = false;
    chargeColor = {0, 0, 0};
    prevChargeColor = {0, 0, 0};
}

std::vector<int> FlashlightCharger::initLayers(){
    std::vector<int> layers;
    layers.push_back(LAYER_NORMAL);
    return layers;
}

void FlashlightCharger::update(double deltaTime, bool* keyPressed, bool* keyHeld){
    if (!playerOnCharger){
        makeVisible = false;
    }
    // Decide the color based on transition points, and do the cycle code.
    if (transitionTime > 0){
        transitionTime -= deltaTime;
        if (transitionTime < 0) transitionTime = 0;
    } 
    if (!makeVisible && visible > 0){
        visible -= deltaTime/visibleSpeed;
        if (visible < 0) visible = 0;
    } else if (makeVisible && visible < 1){
        visible += deltaTime/visibleSpeed;
        if (visible > 1) visible = 1;
    }
    double perc = cos((M_PI/2)*(transitionTime/maxTransitionTime));
    r = chargeColor.x*perc+prevChargeColor.x*(1-perc);
    g = chargeColor.y*perc+prevChargeColor.y*(1-perc);
    b = chargeColor.z*perc+prevChargeColor.z*(1-perc);
    cyclePoint = fmod(cyclePoint+deltaTime*visible, 2);
    playerOnCharger = false;
}

void FlashlightCharger::collided(Instance* o, double deltaTime){
    // Check if the object is a player standing on the charger.
    if (!(o->isPlayer()) || o->y > y-o->h) return;
    Player* p = (Player *)o;
    PlayerAbility* pA = p->getAbility();
    if (pA == nullptr || pA->getName() != "Flashlight") return;
    // Charge the batteries.
    Flashlight* f = (Flashlight *)pA;
    std::vector<pointDouble> battColor = f->chargeBatteries(deltaTime);
    makeVisible = battColor.size() > 0;
    playerOnCharger = true;
    // If there's a transition, don't mess with that yet.
    if (transitionTime > 0 || !makeVisible) return;
    // Get the new floor coloring.
    double addedR = 0;
    double addedG = 0;
    double addedB = 0;
    for (int i = 0; i < battColor.size(); i++){
        addedR += battColor[i].x;
        addedG += battColor[i].y;
        addedB += battColor[i].z;
    }
    if (addedR > 1) addedR = 1;
    if (addedG > 1) addedG = 1;
    if (addedB > 1) addedB = 1;
    // Compare it to the old floor coloring and set up the transition!
    if (abs(addedR-chargeColor.x) > 0.01 || 
        abs(addedG-chargeColor.y) > 0.01 ||
        abs(addedB-chargeColor.z) > 0.01){
        transitionTime = maxTransitionTime;
        prevChargeColor = chargeColor;
        chargeColor = {addedR, addedG, addedB};
    }
}

void FlashlightCharger::draw(GLDraw* gld, GLShaders* gls, int layer){
    if (!gls->programExists("flashlightCharger")){
        gls->createProgram("", "gameFiles/shaders/flashlightCharger", "flashlightCharger");
    }
    gld->color(1, 1, 1, 1);
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
    int program = gls->bindShader("flashlightCharger");
    gls->addUniform(program, "visible", visible);
    gls->addUniform(program, "cyclePoint", cyclePoint);
    gld->begin("QUADS");
    gld->color(r, g, b, 1);
    gld->texCoords(0, 0);
    gld->vertW(x+6,y+12);
    gld->texCoords(0, 1);
    gld->vertW(x+6,y+28);
    gld->texCoords(1, 1);
    gld->vertW(x+w-6,y+28);
    gld->texCoords(1, 0);
    gld->vertW(x+w-6,y+12);
    gld->end();
    gls->unbindShader();
    // Finally, draw the main texture.
    gld->bindTexture(frontTexture);
    gld->begin("QUADS");
    gld->color(1, 1, 1, 1);
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
