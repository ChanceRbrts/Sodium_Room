#include "testHorizontalEnclosed.h"

TestHorizontalEnclosed::TestHorizontalEnclosed(int version){
    filePath = "testLevels/testHorizontalEnclosed";
    if (version > 1) filePath += std::to_string(version);
    ver = version;
    encLev = nullptr;
    // Make sure 
    prevX = 0;
}

std::vector<Instance *> TestHorizontalEnclosed::makeLevel(std::vector<Instance*> previous){
    previous.push_back(new Player(17, 13));
    prevX = 17*32;
    encLev = new EnclosedLevel(ver==2?w/64:4, ver==2?7:0, 0, ver==2?3:h/32, new TestHorizontalInner(ver));
    encLev->disconnect();
    previous.push_back(encLev);
    return previous;
}

std::vector<ShaderBox *> TestHorizontalEnclosed::createShaderBoxes(GLUtil* glu){
   std::vector<ShaderBox *> shadings;
   return shadings;
}

void TestHorizontalEnclosed::updateLevel(double deltaTime, Instance* player){
    if (player == nullptr) return;
    double openX = w/2+(ver == 2 ? 64 : 0);
    if (!encLev->open && prevX > openX && player->x <= openX) encLev->open = true;
    if (encLev->open && prevX < 2*32 && player->x <= 2*32) encLev->open = false;
    prevX = player->x-getXOff();
}

TestHorizontalInner::TestHorizontalInner(int version){
    filePath = "testLevels/testHorizontalInner";
    if (version > 1) filePath += std::to_string(version);
    r = 0.75;
    g = 0.75;
    b = 0.75;
    hasBackground = true;
}

std::vector<Instance *> TestHorizontalInner::makeLevel(std::vector<Instance*> previous){
    return previous;
}

