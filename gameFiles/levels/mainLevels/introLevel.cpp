#include "introLevel.h"

IntroLevel::IntroLevel(){
    filePath = "mainLevels/intro";
    iC = new InstCreate();
}

std::vector<Instance *> IntroLevel::makeLevel(std::vector<Instance*> previous){
    previous.push_back(new Player(5, 13));
    previous.push_back(iC);
    return previous;
}

void IntroLevel::updateLevel(double deltaTime, Instance* player){
    // As the player goes across the introduction, different cutscene elements will show up in the HUD.
    // Once you've gone past the grate, the rain will start falling.
    if (!GameState::getSaveB("startOutdoorRain") && player->x > w/2+getXOff()){
        GameState::setSaveB("startOutdoorRain", true);
        iC->addInstance(new Rain(0, 0, w, 0));
    }
    // This leads to the end where you go through a door and the Sodium Room logo pops up.
    
}
