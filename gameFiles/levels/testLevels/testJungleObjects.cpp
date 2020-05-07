#include "testJungleObjects.h"

TestJungleObjects::TestJungleObjects(){
    filePath = "testJungleObjects";
    sineWaveCounter = 0;
    colorPicker = 0;
    a1 = nullptr;
}

void TestJungleObjects::createPointLights(){
    pLight.clear();
    Arc* a = new Arc(0, 0, 4, -M_PI, M_PI, 1, 0, 1, true);
    pLight.push_back(new PointLight(47, 10, a));
}

std::vector<Instance *> TestJungleObjects::makeLevel(std::vector<Instance*> previous){
    previous.push_back(new Player(23, 4));
    previous.push_back(new HoneyPlatform(8, 14, 4, true));
    previous.push_back(new HoneyPlatform(19, 7, 5, false));
    createPointLights();
    for (int i = 0; i < pLight.size(); i++){
        previous.push_back(pLight[i]);
    }
    return previous;
}

std::vector<Arc *> TestJungleObjects::createArcs(){
    std::vector<Arc *> arcs;
    a1 = new Arc(10, 0, 15, M_PI*3/16, M_PI*5/16, 1, 0, 0, true);
    arcs.push_back(a1);
    for (int i = 0; i < pLight.size(); i++){
        arcs.push_back(pLight[i]->getLight());
    }
    return arcs;
}

void TestJungleObjects::updateLevel(double deltaTime, Instance* player){
    sineWaveCounter += deltaTime;
    while (sineWaveCounter > 8){
        sineWaveCounter -= 8;
        colorPicker = (colorPicker+1)%3;
    }
    double angle1 = M_PI/2-M_PI/2*cos(sineWaveCounter*M_PI/4);
    a1->setAngle(angle1-M_PI*1/16, angle1+M_PI*1/16);
    double red1 = colorPicker == 0 ? 1 : 0;
    double green1 = colorPicker == 1 ? 1 : 0;
    double blue1 = colorPicker == 2 ? 1 : 0;
    a1->setColor(red1, green1, blue1);
}
