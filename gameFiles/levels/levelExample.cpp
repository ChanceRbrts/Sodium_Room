/**
 * Created by Chance on 08/10/19
 * Modified by Chance on 11/15/19
 * 
 */

#include "levelExample.h"

LevelExample::LevelExample(){
   w = 20;
   h = 15;
   filePath = "example";
}

std::vector<ShaderBox *> LevelExample::createShaderBoxes(GLUtil* glu){
   std::vector<ShaderBox *> shadings;
   // Put in ShaderBox
   shadings.push_back(new ShaderBox(0, 0, 10, 15, "", "testShader", glu));
   shadings.push_back(new GravityWell(40, 0, 100, glu));
   return shadings;
}

std::vector<Instance *> LevelExample::makeLevel(std::vector<Instance*> previous){
   previous.push_back(new Player(10, 5));
   return previous;
}
