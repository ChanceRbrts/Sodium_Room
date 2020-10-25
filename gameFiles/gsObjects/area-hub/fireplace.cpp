#include "fireplace.h"

Fireplace::Fireplace(double X, double Y, std::string litName) : Instance(X, Y, 2, 2){
    solid = false;   
    name = "fireplace";
    lName = litName;
    lit = GameState::getSaveB(lName);
}

std::vector<int> Fireplace::initLayers(){
    layers.push_back(LAYER_NORMAL-1);
    return layers;
}

void Fireplace::update(double deltaTime, bool* keyPressed, bool* keyHeld){
    if (lit || !keyPressed[BUTTON_UP]) return;
    for (int i = 0; i < arcList.size(); i++){
        ArcInfo a = arcList[i];
        // The player's lighter is the only thing with this default behavior and ID.
        if (a.defBehavior && a.id == -1){
            lit = true;
            GameState::setSaveB(lName, true);
        }
    }
}
