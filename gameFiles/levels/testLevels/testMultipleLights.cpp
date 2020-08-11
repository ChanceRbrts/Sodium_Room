#include "testMultipleLights.h"

TestMultipleLights::TestMultipleLights(){
    filePath = "emptyLevel";
}

std::vector<Instance *> TestMultipleLights::makeLevel(std::vector<Instance*> previous){
    previous.push_back(new Player(10, 13));
    return previous;
}

std::vector<Arc *> TestMultipleLights::createArcs(){
    std::vector<Arc *> arcs;
    arcs.push_back(new Arc(10, 0, 15, M_PI*7/16, M_PI*9/16, 1, 0, 0, true));
    arcs.push_back(new Arc(3, 15, 20, -M_PI*5/16, -M_PI*3/16, 0, 1, 0, true));
    arcs.push_back(new Arc(17, 15, 20, -M_PI*13/16, -M_PI*11/16, 0, 0, 1, true));
    // a1 = new Arc(10, 0, 15, M_PI*3/16, M_PI*5/16, 1, 0, 0, true);
    // arcs.push_back(a1);
    /*for (int i = 0; i < pLight.size(); i++){
        arcs.push_back(pLight[i]->getLight());
    }*/
    return arcs;
}