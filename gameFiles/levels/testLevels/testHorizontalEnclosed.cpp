#include "testHorizontalEnclosed.h"

TestHorizontalEnclosed::TestHorizontalEnclosed(){
    filePath = "testHorizontalEnclosed";
    encLev = nullptr;
    // Make sure 
    prevX = 0;
}

std::vector<Instance *> TestHorizontalEnclosed::makeLevel(std::vector<Instance*> previous){
    previous.push_back(new Player(17, 13));
    prevX = 17*32;
    encLev = new EnclosedLevel(5, 0, 0, h/32, new TestHorizontalInner());
    previous.push_back(encLev);
    return previous;
}

std::vector<ShaderBox *> TestHorizontalEnclosed::createShaderBoxes(GLUtil* glu){
   std::vector<ShaderBox *> shadings;
   return shadings;
}

void TestHorizontalEnclosed::updateLevel(double deltaTime, Instance* player){
    if (player == nullptr) return;
    if (!encLev->open && prevX > w/2&& player->x <= w/2) encLev->open = true;
    if (encLev->open && prevX < 3*32 && player->x >= 3*32) encLev->open = false;
    prevX = player->x-getXOff();
}

TestHorizontalInner::TestHorizontalInner(){
    filePath = "testHorizontalInner";
    r = 0.75;
    g = 0.75;
    b = 0.75;
    hasBackground = true;
}

std::vector<Instance *> TestHorizontalInner::makeLevel(std::vector<Instance*> previous){
    return previous;
}

