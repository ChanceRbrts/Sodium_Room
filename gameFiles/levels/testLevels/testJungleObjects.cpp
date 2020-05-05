#include "testJungleObjects.h"

TestJungleObjects::TestJungleObjects(){
    filePath = "testJungleObjects";
    sineWaveCounter = 0;
    colorPicker = 0;
    a1 = new Arc(10, 0, 15, M_PI*3/16, M_PI*5/16, 1, 0, 0, true);
}

std::vector<Instance *> TestJungleObjects::makeLevel(std::vector<Instance*> previous){
    previous.push_back(new Player(17, 13));
    previous.push_back(new HoneyPlatform(8, 14, 4, true));
    return previous;
}

std::vector<Arc *> TestJungleObjects::createArcs(){
    std::vector<Arc *> arcs;
    arcs.push_back(a1);
    return arcs;
}

void TestJungleObjects::updateLevel(double deltaTime, Instance* player){
    double prevCounter = sineWaveCounter;
    sineWaveCounter += deltaTime;
    while (sineWaveCounter > 4){
        sineWaveCounter -= 4;
        colorPicker = (colorPicker+1)%3;
    }
    double angle1 = M_PI/2-M_PI/4*cos(sineWaveCounter*M_PI/2);
    a1->setAngle(angle1-M_PI*1/16, angle1+M_PI*1/16);
    double red1 = colorPicker == 0 ? 1 : 0;
    double green1 = colorPicker == 1 ? 1 : 0;
    double blue1 = colorPicker == 2 ? 1 : 0;
    a1->setColor(red1, green1, blue1);
}
