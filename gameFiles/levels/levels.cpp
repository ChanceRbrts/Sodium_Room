#include "levels.h"

Map::Map(){
   prevCX = 0;
   prevCY = 0;
}

std::vector<Level *> getLevelsInArea(double x, double y, double w, double h){

}

void Map::addLevel(Level* l, double X, double Y){
   l->moveRoom(X*32, Y*32, false);
   pointInt area = (pointInt){X/100, Y/100, 0};
   levels.push_back(l);
}

void Map::updateLoadedLevels(LevelList* l, GLUtil* glu){

}

Levels::Levels(){
   // Add Levels Here
   lev.push_back(new LevelExample());
   lev.push_back(new TestRain());
   lev.push_back(new TestFalseBlocks());
   lev.push_back(new TestHorizontalEnclosed());
   lev.push_back(new TestJungleObjects());
   lev.push_back(new IntroLevel());
   lev.push_back(new RainHallwayLevel());
   lev.push_back(new TestMultipleLights());
}