#include "testHorizontalEnclosed.h"

TestHorizontalEnclosed::TestHorizontalEnclosed(){
    filePath = "testHorizontalEnclosed";
}

std::vector<Instance *> TestHorizontalEnclosed::makeLevel(std::vector<Instance*> previous){
    previous.push_back(new Player(17, 13));
    previous.push_back(new EnclosedLevel(5, 0, 0, h/32, new TestHorizontalInner()));
    return previous;
}

std::vector<ShaderBox *> TestHorizontalEnclosed::createShaderBoxes(GLUtil* glu){
   std::vector<ShaderBox *> shadings;
   return shadings;
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

