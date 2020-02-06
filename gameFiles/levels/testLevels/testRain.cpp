/**
 * Something to test the rain effeect that I'll be doing.
 */

#include "testRain.h"

TestRain::TestRain(){
   w = 20;
   h = 15;
   filePath = "testRain";
}

std::vector<ShaderBox *> TestRain::createShaderBoxes(GLUtil* glu){
   std::vector<ShaderBox *> shadings;
   return shadings;
}

std::vector<Instance *>  TestRain::makeLevel(std::vector<Instance*> previous){
   previous.push_back(new Player(10, 5));
   previous.push_back(new Grate(12, 6, 7));
   previous.push_back(new Rain(12, 1, 7, false));
   // previous.push_back(new Rain(12, 1, 5, false));
   // previous.push_back(new Rain(17, 1, 2, true));
   return previous;
}
