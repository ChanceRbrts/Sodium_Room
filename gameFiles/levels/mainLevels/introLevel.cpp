#include "introLevel.h"

IntroLevel::IntroLevel(){
    filePath = "mainLevels/intro";
    iC = nullptr;
}

IntroLevel::~IntroLevel(){
    delete iC;
}

std::vector<Instance *> IntroLevel::makeLevel(std::vector<Instance*> previous){
    previous.push_back(new Player(5, 13));
    previous.push_back(new Grate(27, 14, 2));
    iC = new InstCreate();
    previous.push_back(iC);
    return previous;
}

void IntroLevel::updateLevel(double deltaTime, Instance* player){
    h = 15;
    // As the player goes across the introduction, different cutscene elements will show up in the HUD.
    // Once you've gone past the grate, the rain will start falling.
    if (!GameState::getSaveB("int_startOutdoorRain") && player->x > w/2+getXOff()){
        GameState::setSaveB("int_startOutdoorRain", true);
        /// TODO: This is hard-coded to the level due to how rain currently works.
        /// Fix the rain so you don't have to do this.
        iC->addInstance(new Rain(0, 0, 20, 0));
        iC->addInstance(new Rain(20, 0, 1, 0));
        iC->addInstance(new Rain(21, 0, 6, 0));
        iC->addInstance(new Rain(27, 0, 2, 0));
        iC->addInstance(new Rain(29, 0, 23, 0));
        iC->addInstance(new Rain(52, 0, 1, 0));
        iC->addInstance(new Rain(53, 0, 1, 0));
        iC->addInstance(new Rain(54, 0, 34, 0));
    }
    // This leads to the end where you go through a door and the Sodium Room logo pops up.
}
