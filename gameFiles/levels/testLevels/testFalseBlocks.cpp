/**
 * Something to test the rain effeect that I'll be doing.
 */

#include "testFalseBlocks.h"

TestFalseBlocks::TestFalseBlocks(){
   w = 20;
   h = 15;
   filePath = "testFalseBlocks";
}

std::vector<ShaderBox *> TestFalseBlocks::createShaderBoxes(GLUtil* glu){
   std::vector<ShaderBox *> shadings;
   return shadings;
}

std::vector<Instance *> TestFalseBlocks::makeLevel(std::vector<Instance*> previous){
   previous.push_back(new Player(10, 13));
   previous.push_back(new FakeSolids("testFalseBlocks2"));
   previous.push_back(new HoneyPlatform(13, 14, 4, true));
   /*for (int i = 9; i < 19; i++){
      for (int j = 7; j < 9; j++){
         previous.push_back(new FakeSolid(i, j));
      }
   }*/
   // previous.push_back(new FakeSolid(9, 8));
   // previous.push_back(new FakeSolid(10, 8));
   return previous;
}
