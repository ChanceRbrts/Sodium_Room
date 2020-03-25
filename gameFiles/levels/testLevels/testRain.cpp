/**
 * Something to test the rain effeect that I'll be doing.
 */

#include "testRain.h"

TestRain::TestRain(){
   w = 20*32;
   h = 15*32;
   filePath = "testRain";
   time = 0;
   maxTime = 4;
}

std::vector<ShaderBox *> TestRain::createShaderBoxes(GLUtil* glu){
   std::vector<ShaderBox *> shadings;
   return shadings;
}

std::vector<Instance *>  TestRain::makeLevel(std::vector<Instance*> previous){
   previous.push_back(new Player(10, 5));
   previous.push_back(new Grate(12, 6, 7));
   previous.push_back(new Rain(12, 1, 7, 1));
   // previous.push_back(new Rain(12, 1, 7, true));
   return previous;
}

std::vector<Arc *> TestRain::createArcs(){
   std::vector<Arc *> arcs;
   // arcs.push_back(new Arc(9.5, 7, 10, -M_PI/8, M_PI/8, 1, 0, 0));
   // arcs.push_back(new Arc(9.5, 7, 10, -M_PI/8, M_PI/8, 0.4, 0.4, 1));
   arcs.push_back(new Arc(9.5, 7, 10, -M_PI/8, M_PI/8, 0.1, 1, 0.1));
   return arcs;
}

void TestRain::updateLevel(double deltaTime, Instance* player){
   Arc* a = arcs[0];
   time += deltaTime;
   if (time > maxTime) time -= maxTime;
   // double dR = M_PI/4*cos(M_PI*2*time/maxTime)*deltaTime;
   // a->setAngle(a->getD1()+dR, a->getD2()+dR);
   a->setAngle(a->getD1()-M_PI/2*deltaTime, a->getD2()-M_PI/2*deltaTime);
}
