#include "flashlightCharger.h"

FlashlightCharger::FlashlightCharger(double X, double Y) : Instance(X, Y, 4, 1){
    immovable = true;
    solid = true;
    name = "Flashlight Charger";
}

std::vector<int> FlashlightCharger::initLayers(){
    std::vector<int> layers;
    layers.push_back(LAYER_NORMAL-1);
    return layers;
}

void FlashlightCharger::collided(Instance* o, double deltaTime){
    // Check if the object is a player standing on the charger.
    if (!(o->isPlayer()) || o->y > y-o->h) return;
    Player* p = (Player *)o;
    PlayerAbility* pA = p->getAbility();
    if (pA == nullptr || pA->getName() != "Flashlight") return;
    // Charge the batteries.
    Flashlight* f = (Flashlight *)f;
    f->chargeBatteries(deltaTime);
}